#include <resultnode.h>
#include <algorithm>

using namespace std;

ResultNode::ResultNode(uint64_t affix_id, uint64_t previous_category_id,
                       uint64_t resulting_category_id, bool accepts_state,
                       const wstring &original_string, const wstring &inflected_string,
                       const wstring &inflection_rule)
    : Node(),
      m_previous_category_id(previous_category_id),
      m_affix_id(affix_id),
      m_resulting_category_id(resulting_category_id),
      m_accepts_state(accepts_state),
      m_inflection_rule(inflection_rule) {
    addRawData(original_string, inflected_string);
}

ResultNode::ResultNode(const ResultNode &other)
    : Node(other),
      m_previous_category_id(other.m_previous_category_id),
      m_affix_id(other.m_affix_id),
      m_resulting_category_id(other.m_resulting_category_id),
      m_accepts_state(other.m_accepts_state),
      m_raw_data(other.m_raw_data) {}

ResultNode::~ResultNode() {}

bool ResultNode::letterNode() const { return false; }

wchar_t ResultNode::letter() const { return 0; }

wstring ResultNode::toString(bool affix, std::shared_ptr<atm::cache::AtmCache> cache) const {
    wstring retVal = L"-";
    wstring tmp = affix && cache != nullptr ? cache->categoriesTable()->at(m_previous_category_id - 1).name
                        : to_wstring(m_previous_category_id);
    retVal.append(tmp).append(L">[");
    tmp = affix && cache != nullptr ? cache->categoriesTable()->at(m_resulting_category_id - 1).name
                : to_wstring(m_resulting_category_id);
    retVal.append(tmp).append(L"]");
    return retVal;
}

void ResultNode::addRawData(const wstring &original_string, const wstring &inflected_string) {
    RawData r(original_string, inflected_string);
    auto it = find(m_raw_data.begin(), m_raw_data.end(), r);
    if (it != m_raw_data.end()) {
        m_raw_data.push_back(r);
    }
}

ResultNode *ResultNode::previousResultNode() const {
    Node *previous = this->parent();
    while (previous != nullptr && previous->letterNode()) {
        previous = previous->parent();
    }
    return dynamic_cast<ResultNode *>(previous);
}
