#include <treesearch.h>

using namespace std;
namespace atm {
namespace core {
using namespace common;

TreeSearch::TreeSearch(const ItemTypes &type, const wstring &text, wstring::size_type start,
                       bool reduce_thru_diacritics)
    : m_reduce_thru_diacritics(reduce_thru_diacritics) {}

TreeSearch::~TreeSearch() {}
}
}
