#include <treesearch.h>

using namespace std;

namespace atm {
namespace core {
using namespace common;

TreeSearch::TreeSearch(const ItemTypes &type, const wstring &text, wstring::size_type start,
                       bool reduce_thru_diacritics)
    : m_reduceThruDiacritics(reduce_thru_diacritics),
      m_textInfo(text, start, start),
      m_type(type) {
    if (m_type == ItemTypes::PREFIX) {
    }
}

TreeSearch::~TreeSearch() {}
}
}
