#include <minimaliteminfo.h>

using namespace std;

/// \todo Original uses cache to retrieve description if id is given. Do we really need this?
string MinimalItemInfo::description() const {
    if (!m_description.empty()) {
        return m_description;
    } else {
        return std::to_string(m_description_id);
    }
}
