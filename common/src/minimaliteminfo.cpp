#include <minimaliteminfo.h>

using namespace std;

/// \todo Use cache for this.
string MinimalItemInfo::description() const {
    if (!m_description.empty()) {
        return m_description;
    } else {
        return std::to_string(m_description_id);
    }
}
