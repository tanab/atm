#include <tree.h>
#include <letternode.h>
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
                       const wstring &inflection_rule_description, Node *curent_node) {
    return nullptr;
}

int Tree::buildHelper(const ItemTypes &type, uint64_t category_id, int size, Node *current) {
    return -1;
}
