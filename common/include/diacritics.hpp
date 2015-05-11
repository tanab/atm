#pragma once

#include <iostream>
#include <letters.hpp>
#include <string>

#include <boost/regex.hpp>

namespace atm {
namespace common {
using namespace util;

const static std::wstring regex_remove_diacritics = std::wstring()
                                                        .append(L"[")
                                                        .append(1, shadde)
                                                        .append(1, fatha)
                                                        .append(1, damma)
                                                        .append(1, sukun)
                                                        .append(1, kasra)
                                                        .append(1, kasratayn)
                                                        .append(1, fathatayn)
                                                        .append(1, dammatayn)
                                                        .append(1, aleft_superscript)
                                                        .append(L"]");
///
/// \brief removeDiacritics Removes diacritics from the string.
/// \param s a string to strip diacritics from.
/// \return string without diacritics.
///
inline std::wstring removeDiacritics(const std::wstring &s) {
    static boost::wregex diacritics(regex_remove_diacritics);
    return boost::regex_replace(s, diacritics, L"", boost::regex_constants::format_default);
}
}
}
