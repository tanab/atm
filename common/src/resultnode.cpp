#include <resultnode.h>
#include <algorithm>

using namespace std;

ResultNode::ResultNode(int64_t affix_id, int64_t previous_category_id,
                       int64_t resulting_category_id, bool accepts_state,
                       const wstring &original_string, const wstring &inflected_string)
    : Node(),
      m_previous_category_id(previous_category_id),
      m_affix_id(affix_id),
      m_resulting_category_id(resulting_category_id),
      m_accepts_state(accepts_state) {
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

// TODO: Needs database or cache access implemented.
wstring ResultNode::toString(bool /*affix*/) const {
    return L"UNIMPLEMENTED";
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
    while(previous != nullptr && previous->letterNode()) {
        previous = previous->parent();
    }
    return dynamic_cast<ResultNode *>(previous);
}
