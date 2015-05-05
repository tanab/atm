#include <tree.h>
#include <letternode.h>
#include <resultnode.h>
#include <constants.h>
#include <atmcache.h>
#include <diacritics.h>

using namespace std;

Tree::Tree(AtmCache *cache)
    : m_cache(cache),
      m_affix(false),
      m_last_id(-1),
      m_letter_nodes(1),
      m_result_nodes(0),
      m_base(new LetterNode(L'\0')) {}

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
    if (type != ItemTypes::PREFIX || type != ItemTypes::SUFFIX) {
        return false;
    }
    reset();
    m_affix = true;
    m_type = type;
    m_last_id = 1;
    m_id_map.clear();
    switch (m_type) {
        case ItemTypes::PREFIX:
            return buildAffixTreeFromPrefix();
        case ItemTypes::SUFFIX:
            return buildAffixTreeFromSuffix();
        default:
            return false;
    }
}

bool Tree::buildAffixTreeFromPrefix() {
    auto rows = m_cache->prefixTable();
    wstring name;
    for (const auto &row : *rows) {
        name = removeDiacritics(row.name);
        auto affix_id = row.id;
        auto prefix_categories = m_cache->findPrefixCategories(row.id);
        MinimalItemInfo info;
        for (auto &it = prefix_categories.first; it != prefix_categories.second; it++) {
            info.updateFrom(it->second);
            bool acceptsState = m_cache->acceptsState(info.type(), info.categoryId());
            if (acceptsState || m_cache->hasCompatibleAffixes(info.type(), info.categoryId())) {
                Node *next = addElement(name, affix_id, info.categoryId(), info.categoryId(),
                                        acceptsState, info.rawData(), info.rawData(), L"", m_base);
                // TODO: Clarify why 6 - name.length()
                buildHelper(m_type, info.categoryId(), 6 - name.length(), next);
            }
        }
    }
    return true;
}

bool Tree::buildAffixTreeFromSuffix() { return true; }

Node *Tree::addElement(const wstring &letters, uint64_t affix_id, uint64_t category_id,
                       uint64_t resulting_category_id, bool accepts_state, const wstring &raw_data,
                       const wstring &inflected_raw_data,
                       const wstring &inflection_rule_description, Node *current_node) {
    if (current_node->letterNode() && current_node != m_base) {
        cerr << "Provided node is a letter node or it is not a base node." << endl;
        return nullptr;
    }
    LetterNode *matching_letter_node = nullptr;
    wchar_t current_letter;
    wstring::size_type i = 0;

    // Original code with goto. Ugly and nasty...
    //    if (letters.size() == 0) {
    //        current_letter = L'\0';
    //        if (current_node == m_base) {
    //            // BAD BAD BAD UGLY UGLY UGLY
    //            goto result;
    //        }
    //    } else {
    //        current_letter = letters[0];
    //    }

    if (letters.size() != 0) {
        current_letter = letters[0];
    } else {
        current_letter = L'\0';
    }

    // This condition replaces original ugly coditions with goto.
    if (letters.size() != 0 && current_node != m_base) {
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
        }
    }

    // See the comment above the original code with goto.
    // result:
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
    //    current_node = result;
    m_result_nodes++;
    //    return current_node;
    return result;
}

int Tree::buildHelper(const ItemTypes &type, uint64_t category_id, int size, Node *current) {
    if (size <= 0) {
        return 0;
    }

    uint64_t category_id2;
    uint64_t resulting_category_id;

    // TODO: Are sure that we treat STEM and SUFFIX the same way?
    auto compatibility_rules = m_cache->findCompatibilityRules(
        (type == ItemTypes::PREFIX ? Rules::AA : Rules::CC), category_id);
    for (auto &it = compatibility_rules.first; it != compatibility_rules.second; it++) {
        category_id2 = it->second.category_id_2;
        resulting_category_id = it->second.resulting_category;
        auto inflections = it->second.inflections;
        bool acceptsState = m_cache->acceptsState(type, resulting_category_id);
        if (acceptsState || m_cache->hasCompatibleAffixes(type, resulting_category_id)) {

        }

    }
}
