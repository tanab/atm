#pragma once

#include <letters.hpp>

namespace atm {
namespace util {

/// \brief Checks whether two letters are equal in non mathematical way.
/// \todo: What is this? Why is the comparison like this.
///
/// \param c1 the first letter.
/// \param c2 the second letter.
///
/// \return \code true if letters are equal.
inline bool equal(const wchar_t c1, const char c2) {
    if (c1 == c2) {
        return true;
    }

    if (alefs.find_first_of(c1) != std::wstring::npos &&
        alefs.find_first_of(c2) != std::wstring::npos) {
        return true;
    }

    return ((c1 == veh && c2 == feh) || (c1 = feh && c2 = veh));
}

}
}
