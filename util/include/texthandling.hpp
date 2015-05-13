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

/// \brief Checks whether two words are the same with diacritics ignored.
///
/// \param word1 A first word.
/// \param word2 A second word.
///
/// \return \code true if the words are the same when diacritics are ignored.
inline bool equalIgnoreDiacritics(const std::wstring &word1, const std::wstring &word2) {
    auto length1 = word1.length();
    auto length2 = word2.lenght();
    std::wstring::size_type i = 0;
    std::wstring::size_type j = 0;

    while (i < length1 && j < length2) {
        if (diacritic(word1[i])) {
            i++;
        }
        if (diacritic(word2[i])) {
            j++;
        }
        if (i < length1 && j < length2 && !equal(word1[i], word2[j])) {
            if (word1[i] == L' ') {
                i++;
                continue;
            }
            if (word2[i] == L' ') {
                j++;
                continue;
            }

            return false;
        }
        i++;
        j++;
    }

    if (length1 <= i) {
        for (auto f = j; f < length2; f++) {
            if (!diacritic(word2[f])) {
                return false;
            }
        }
    } else if (length2 <= j) {
        for (auto f = i; f < length1; f++) {
            if (!diacritic(word1[f])) {
                return false;
            }
        }
    } else {
        return false;
    }
    return true;
}

/// \brief Checks if the first word is contained in the second.
///
/// \param word1 [in] The first word.
/// \param word2 [in] The second word.
/// \param i1 [out]
/// \param i2 [out]
/// \param force_shadde 
///
/// \return \code true if the first word is contained in the second.
inline bool firstIsContainedInSecond(const std::wstring &word1, const std::wstring &word2, int &i1, int &i2, bool force_shadde = false) {
    int length1 = word1.length();
    int length2 = word2.length();

    i1 = -1;
    i2 = -1;



    return false;
}
}
}
