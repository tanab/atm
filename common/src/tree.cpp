#include <tree.h>
#include <letternode.h>
#include <resultnode.h>
#include <constants.h>
#include <atmcache.h>
#include <inflections.hpp>
#include <diacritics.hpp>
#include <fulliteminfo.h>
#include <fstream>
#include <iostream>

#include <assert.h>

using namespace std;

namespace atm {
namespace common {

using namespace util;

Tree::Tree(cache::AtmCache *cache)
    : m_cache(cache),
      m_affix(false),
      m_last_id(-1),
      m_letter_nodes(1),
      m_result_nodes(0),
      m_base(new LetterNode(L'\0')) {
    std::wcout.imbue(std::locale(""));
}

Tree::~Tree() { delete m_base; }

bool Tree::setupForItemType(const ItemTypes &type) {
    reset();
    m_affix = true;
    m_last_id = -1;
    m_base = new LetterNode(L'\0');
    return buildAffixTree(type);
}

bool Tree::affixType(ItemTypes &type) {
    if (m_affix) {
        type = m_type;
        return true;
    }
    return false;
}

void Tree::reset() {
    m_base->removeAllChildren();
    m_letter_nodes = 1;
    m_result_nodes = 0;
    m_affix = false;
}

bool Tree::buildAffixTree(const ItemTypes &type) {
    reset();
    m_affix = true;
    m_type = type;
    m_last_id = 1;
    m_id_map.clear();
    switch (m_type) {
        case ItemTypes::PREFIX:
            return buildAffixTreeHelper(m_cache->prefixTable());
        case ItemTypes::SUFFIX:
            return buildAffixTreeHelper(m_cache->suffixTable());
        default:
            return buildAffixTreeHelper(m_cache->stemTable());
    }
}

bool Tree::buildAffixTreeHelper(const std::shared_ptr<cache::AffixRows> &rows) {
    wstring name;
    for (const auto &row : *rows) {
        name = removeDiacritics(row.name);
        auto affix_id = row.id;
        cache::AffixCategoryMapRange prefix_categories = m_cache->findPrefixCategories(affix_id);
        for (auto it = prefix_categories.first; it != prefix_categories.second; it++) {
            bool acceptsState =
                m_cache->acceptsState(it->second.affix_type, it->second.category_id);
            if (acceptsState ||
                m_cache->hasCompatibleAffixes(it->second.affix_type, it->second.category_id)) {
                Node *next =
                    addElement(name, affix_id, it->second.category_id, it->second.category_id,
                               acceptsState, it->second.raw_data, it->second.raw_data, L"", m_base);
                // TODO: Clarify why 6 - name.length()
                buildHelper(m_type, it->second.category_id, 6 - name.length(), next);
            }
        }
    }
    return true;
}

Node *Tree::addElement(const wstring &letters, uint64_t affix_id, uint64_t category_id,
                       uint64_t resulting_category_id, bool accepts_state, const wstring &raw_data,
                       const wstring &inflected_raw_data,
                       const wstring &inflection_rule_description, Node *current_node) {
    wcout << L"letters: '" << letters << L"' affix_id: " << affix_id << L" category_id: "
          << category_id << L" resulting_category_id: " << resulting_category_id
          << L" accepts_state: " << accepts_state << L" raw_data: '" << raw_data
          << L"' inflected_raw_data: '" << inflected_raw_data << L"' inflection_rule_description: '"
          << inflection_rule_description << L"'" << std::endl;
    if (current_node->letterNode() && current_node != m_base) {
        cerr << "Provided node is a letter node or it is not a base node." << endl;
        return nullptr;
    }
    LetterNode *matching_letter_node = nullptr;
    wchar_t current_letter;
    wstring::size_type i = 0;

    if (letters.size() == 0) {
        current_letter = L'\0';
        if (current_node == m_base) {
            goto result;
        }
    } else {
        current_letter = letters[0];
    }

    do {
        matching_letter_node =
            dynamic_cast<LetterNode *>(current_node->letterChild(current_letter));
        if (matching_letter_node != nullptr) {
            current_node = matching_letter_node;
            current_letter = letters[++i];
        } else {
            break;
        }
    } while (i < letters.size());

    if (letters.size() == 0 && i == 0) {
        // Add a null letter
        // TODO: Why do we add null letter?
        auto new_node = new LetterNode(L'\0');
        current_node->addChild(new_node);
        current_node = new_node;
        m_letter_nodes++;
    }

    while (i < letters.size()) {
        // Add necessary letters
        auto new_node = new LetterNode(letters[i]);
        current_node->addChild(new_node);
        current_node = new_node;
        m_letter_nodes++;
        i++;
    }

// The original implementation used ugly coditions with goto.
//    if (letters.size() != 0) {
//        current_letter = letters[0];
//    } else {
//        current_letter = L'\0';
//    }

//    if (letters.size() != 0 && current_node != m_base) {
//        do {
//            matching_letter_node =
//                dynamic_cast<LetterNode *>(current_node->letterChild(current_letter));
//            if (matching_letter_node != nullptr) {
//                current_node = matching_letter_node;
//                current_letter = letters[++i];
//            } else {
//                break;
//            }
//        } while (i < letters.size());

//        if (letters.size() == 0 && i == 0) {
//            // Add a null letter
//            // TODO: Why do we add null letter?
//            auto new_node = new LetterNode(L'\0');
//            current_node->addChild(new_node);
//            current_node = new_node;
//            m_letter_nodes++;
//        }

//        while (i < letters.size()) {
//            // Add necessary letters
//            //            std::wcout << L"LETTERS: " << letters << L" " << (unsigned
//            int)letters[i]
//            //            << std::endl;
//            auto new_node = new LetterNode(letters[i]);
//            current_node->addChild(new_node);
//            current_node = new_node;
//            m_letter_nodes++;
//            i++;
//        }
//    }

result:
    for (const auto tmp : current_node->resultChildren()) {
        ResultNode *old_result = static_cast<ResultNode *>(tmp);
        if (old_result->previousCategoryId() == category_id &&
            old_result->resultingCategoryId() == resulting_category_id &&
            old_result->affixId() == affix_id) {
            old_result->addRawData(raw_data, inflected_raw_data);
            old_result->setInflectionRule(inflection_rule_description);
            return old_result;
        }
    }

    ResultNode *result = new ResultNode(affix_id, category_id, resulting_category_id, accepts_state,
                                        raw_data, inflected_raw_data, inflection_rule_description);
    // TODO: Check whether commented lines are needed because of the side effects.
    current_node->addChild(result);
    current_node = result;
    m_result_nodes++;
    return current_node;
    //    return result;
}

void Tree::buildHelper(const ItemTypes &type, uint64_t category_id, int size, Node *current) {
    if (size <= 0) {
        return;
    }

    // TODO: Are sure that we treat STEM and SUFFIX the same way?
    auto compatibility_rules = m_cache->findCompatibilityRules(
        (type == ItemTypes::PREFIX ? Rules::AA : Rules::CC), category_id);

    for (auto it_comp_rules = compatibility_rules.first;
         it_comp_rules != compatibility_rules.second; it_comp_rules++) {
        uint64_t category_id2 = it_comp_rules->second.category_id_2;
        uint64_t resulting_category_id = it_comp_rules->second.resulting_category;
        std::wstring inflections = it_comp_rules->second.inflections;
        bool acceptsState = m_cache->acceptsState(type, resulting_category_id);
        if (acceptsState || m_cache->hasCompatibleAffixes(type, resulting_category_id)) {
            auto affix_categories = m_cache->findAffixCategories(category_id2);
            for (auto it_affix_cat = affix_categories.first;
                 it_affix_cat != affix_categories.second; it_affix_cat++) {
                std::wstring name = m_cache->findAffixName(it_affix_cat->second.affix_type,
                                                           it_affix_cat->second.affix_id);
                name = removeDiacritics(name);
                auto inflected_raw_data = it_affix_cat->second.raw_data;
                inflections::applyRawDataInflections(inflections, name, inflected_raw_data);
                Node *next =
                    addElement(name, it_affix_cat->second.affix_id, category_id2,
                               resulting_category_id, acceptsState, it_affix_cat->second.raw_data,
                               inflected_raw_data, inflections, current);
                buildHelper(type, resulting_category_id, size - name.length(), next);
            }
        }
    }
}

void Tree::printTreeHelper(Node *current_node, int level, wfstream &fs) {
    fs << std::wstring(level * 7, L' ') << current_node->toString(true, m_cache) << std::endl;
    for (auto node : current_node->letterChildren()) {
        if (node != nullptr) {
            printTreeHelper(node, level + 1, fs);
        }
    }
    for (auto node : current_node->resultChildren()) {
        if (node != nullptr) {
            printTreeHelper(node, level + 1, fs);
        }
    }
}

void Tree::printTree() {
    std::wcout.imbue(std::locale(""));
    wfstream fs;
    fs.imbue(std::locale(""));
    fs.open("/tmp/prefix_tree.txt", fstream::out);
    fs << "----------------------------------------" << std::endl;
    fs << "\t prefix Tree" << std::endl;
    fs << "----------------------------------------" << std::endl;
    printTreeHelper(m_base, 0, fs);
    fs << "----------------------------------------" << std::endl;
    fs << "letter nodes count = " << m_letter_nodes << std::endl;
    fs << "result nodes count = " << m_result_nodes << std::endl;
    fs << "----------------------------------------" << std::endl;
    fs.flush();
    fs.close();
}
}
}
