#pragma once

#include <iostream>
#include <letters.hpp>
#include <string>

#include <boost/regex.hpp>

namespace atm {
namespace util {

enum class Diacritic {
    FATHA = fatha,
    KASRA = kasra,
    DAMMA = damma,
    SHADDE = shadde,
    SUKUN = sukun,
    FATHATAYN = fathatayn,
    KASRATAYN = kasratayn,
    DAMMATAYN = dammatayn,
    ALEF_SUPERSCRIPT = alef_superscript,
    UNDEFINED_DIACRITIC = L'\0'
};

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
                                                        .append(1, alef_superscript)
                                                        .append(L"]");

/// \brief Removes diacritics from the given string.
///
/// \param s the string to remove diacritics from.
///
/// \return the string without diacritics.
inline std::wstring removeDiacritics(const std::wstring &s) {
    static boost::wregex diacritics(regex_remove_diacritics);
    return boost::regex_replace(s, diacritics, L"", boost::regex_constants::format_default);
}

/// \brief Returns appropriate character for given diacritic, or null character if appropriate
/// character for given diacritic does not exist.
///
/// \param diacritic the diacritic.
///
/// \return appropriate character for given diacritic.
inline wchar_t interpret(const Diacritic &diacritic) { return (wchar_t)diacritic; }

/// \brief Returns appropriate diacritic for given character.
///
/// \param character the character.
///
/// \return appropriate diacritic.
inline Diacritic interpret(const wchar_t character) {
    switch (character) {
        case fatha:
            return Diacritic::FATHA;
        case kasra:
            return Diacritic::KASRA;
        case damma:
            return Diacritic::DAMMA;
        case shadde:
            return Diacritic::SHADDE;
        case sukun:
            return Diacritic::SUKUN;
        case fathatayn:
            return Diacritic::FATHATAYN;
        case kasratayn:
            return Diacritic::KASRATAYN;
        case dammatayn:
            return Diacritic::DAMMATAYN;
        case alef_superscript:
            return Diacritic::ALEF_SUPERSCRIPT;
        default:
            return Diacritic::UNDEFINED_DIACRITIC;
    }
}

/// \brief Counts the number of diacritics in given string.
///
/// \param s a string to count diacritics in.
///
/// \return number of diacritics in given string.
inline std::wstring::size_type countDiactitics(const std::wstring &s) {
    auto tmp = removeDiacritics(s);
    return s.length() - tmp.length();
}

/// \brief Returns the index of the last non-diacritic letter in the given word. If all letters are
/// diacritics then -1 is returned.
///
/// \param word a word to look for the last non-diacritic letter index.
///
/// \return index of the last non-diacritic letter.
inline int lastLetterIndex(const std::wstring &word) {
    auto pos = word.find_last_not_of(diacritics);
    return pos != std::wstring::npos ? pos : -1;
}

/// \brief Returns the last non-diacritic letter in the given word. If all letters are diacritics
/// then null character is returned.
///
/// \param word a word to look for the last non-diacritic letter.
///
/// \return last non-diacritic letter.
inline wchar_t lastLetter(const std::wstring &word) {
    auto pos = lastLetterIndex(word);
    return pos != static_cast<int>(std::wstring::npos) ? word[pos] : L'\0';
}

/// \brief Removes last non-diacritical letter.
///
/// \param word a word from which to remove last non-diacritical letter.
///
/// \return word with last non-diacritical letter removed.
inline std::wstring removeLastLetter(const std::wstring &word) {
    auto letter_pos = lastLetterIndex(word);
    return letter_pos != -1 ? word.substr(0, letter_pos) : word;
}

/// \brief Removes consecutive trailing diacritics until a normal letter is reached.
///
/// \param word a word from which to remove trailing diacritics.
///
/// \return word without trailing diacritics.
inline std::wstring removeTrailingDiacritics(const std::wstring &word) {
    auto letter_pos = lastLetterIndex(word);
    return word.substr(0, letter_pos + 1);
}

}
}
