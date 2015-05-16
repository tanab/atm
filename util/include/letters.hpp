#pragma once

#include <string>

namespace atm {
namespace util {

static const wchar_t hamza = 0x0621;
static const wchar_t ya2 = 0x064A;
static const wchar_t ya2_hamza_above = 0x0626;
static const wchar_t alef = 0x0627;
static const wchar_t alef_madda_above = 0x0622;
static const wchar_t alef_hamza_above = 0x0623;
static const wchar_t alef_hamza_below = 0x0625;
static const wchar_t alef_wasla = 0x0671;
static const wchar_t ta2_marbouta = 0x0629;
static const wchar_t waw = 0x0648;
static const wchar_t waw_hamza_above = 0x0624;
static const wchar_t shadde = 0x0651;
static const wchar_t shadde_alef_above = 0xFC63;
static const wchar_t fatha = 0x064E;
static const wchar_t damma = 0x064F;
static const wchar_t kasra = 0x0650;
static const wchar_t sukun = 0x0652;
static const wchar_t lam = 0x0644;
static const wchar_t kasratayn = 0x064D;
static const wchar_t dammatayn = 0x064C;
static const wchar_t fathatayn = 0x064B;
static const wchar_t kha2 = 0x062E;
static const wchar_t ba2 = 0x0628;
static const wchar_t ra2 = 0x0631;
static const wchar_t noon = 0x0646;
static const wchar_t seen = 0x0633;
static const wchar_t sheen = 0x0634;
static const wchar_t meem = 0x0645;
static const wchar_t _3yn = 0x0639;
static const wchar_t ta2 = 0x062A;
static const wchar_t qaf = 0x0642;
static const wchar_t _7a2 = 0x062D;
static const wchar_t dal = 0x062F;
static const wchar_t tha2 = 0x062B;
static const wchar_t alef_superscript = 0x0670;
static const wchar_t ha2 = 0x0647;
static const wchar_t veh = 0x06A4;
static const wchar_t feh = 0x0641;
static const wchar_t madda = 0x0653;
static const wchar_t zain = 0x0632;
static const wchar_t thal = 0x0630;
static const wchar_t sad = 0x0635;
static const wchar_t dad = 0x0636;
static const wchar_t tah = 0x0637;
static const wchar_t zah = 0x0638;
static const wchar_t alef_maksoura = 0x0649;

static const wchar_t fasila = 0x060C;
static const wchar_t question_mark = 0x061F;
static const wchar_t semicolon_ar = 0x061B;
static const wchar_t full_stop1 = 0x06D4;
static const wchar_t full_stop2 = 0x200F;
static const wchar_t full_stop3 = 0x002E;
static const wchar_t double_quotation1 = 0x00BB;  //!< Right-pointing double angle quotation mark
static const wchar_t double_quotation2 = 0x00AB;  //!< Left-pointing double angle quotation mark
static const wchar_t double_quotation3 = 0x02DD;  //!< Double acute accent
static const wchar_t double_quotation4 = 0x02EE;  //!< Modifier letter double apostrophe
static const wchar_t double_quotation5 = 0x02F5;  //!< Modifier letter middle double grave accent
static const wchar_t double_quotation6 = 0x02F6;  //!< Modifier letter middle double acute accent:u
static const wchar_t single_quotation1 = 0x02BB;  //!< Modifier letter turned comma
static const wchar_t single_quotation2 = 0x02BC;  //!< Modifier letter apostrophe
static const wchar_t single_quotation3 = 0x02BD;  //!< Modifier letter reversed comma
static const wchar_t single_quotation4 = 0x02CA;  //!< Modifier letter acute accent
static const wchar_t single_quotation5 = 0x02CB;  //!< Modifier letter grave accent

static const wchar_t paragraph_separator = 0x2029;  //!< Paragraph separator
static const wchar_t zero_width_space = 0xFEFF;     //!< Zero width no-break space

static const std::wstring punctuations = std::wstring(L":!_\\.,=-'\n\r\"")
                                             .append(1, fasila)
                                             .append(1, full_stop1)
                                             .append(1, full_stop2)
                                             .append(1, full_stop3)
                                             .append(1, paragraph_separator)
                                             .append(1, question_mark)
                                             .append(1, semicolon_ar);

static const std::wstring alefs = std::wstring(1, alef)
                                      .append(1, alef_hamza_above)
                                      .append(1, alef_hamza_below)
                                      .append(1, alef_madda_above)
                                      .append(1, alef_wasla);

static const std::wstring delimiters = std::wstring(L"[!_ :\\.,()-><{}=*+\\/|'\"\n\t\r")
                                           .append(1, double_quotation1)
                                           .append(1, double_quotation2)
                                           .append(1, double_quotation3)
                                           .append(1, double_quotation4)
                                           .append(1, double_quotation5)
                                           .append(1, double_quotation6)
                                           .append(1, fasila)
                                           .append(1, full_stop1)
                                           .append(1, full_stop2)
                                           .append(1, full_stop3)
                                           .append(1, question_mark)
                                           .append(1, semicolon_ar)
                                           .append(1, single_quotation1)
                                           .append(1, single_quotation2)
                                           .append(1, single_quotation3)
                                           .append(1, single_quotation4)
                                           .append(1, single_quotation5)
                                           .append(1, zero_width_space)
                                           .append(L"\\[\\]]");

static const std::wstring non_connecting_letters = std::wstring(1, alef)
                                                       .append(1, alef_hamza_above)
                                                       .append(1, alef_hamza_below)
                                                       .append(1, alef_madda_above)
                                                       .append(1, alef_maksoura)
                                                       .append(1, alef_superscript)
                                                       .append(1, alef_wasla)
                                                       .append(1, dal)
                                                       .append(1, hamza)
                                                       .append(1, ra2)
                                                       .append(1, ta2_marbouta)
                                                       .append(1, thal)
                                                       .append(1, waw)
                                                       .append(1, waw_hamza_above)
                                                       .append(1, zain);

static const std::wstring diacritics = std::wstring(1, alef_superscript)
                                           .append(1, damma)
                                           .append(1, dammatayn)
                                           .append(1, fatha)
                                           .append(1, fathatayn)
                                           .append(1, kasra)
                                           .append(1, kasratayn)
                                           .append(1, madda)
                                           .append(1, shadde)
                                           .append(1, shadde_alef_above)
                                           .append(1, sukun);

/// \brief Checks whether given letter is a delimiter.
///
/// \param letter a letter to check.
///
/// \return \code true if the letter is a punctuation mark.
inline bool delimiter(const wchar_t letter) {
    if (letter == 0) {
        return false;
    }
    if (letter < 0x0020) {
        return true;
    }
    return delimiters.find_first_of(letter) != std::wstring::npos;
}

/// \brief Checks whether given letter is a punctuation mark.
///
/// \param letter a letter to check.
///
/// \return \code true if the letter is a punctuation mark.
inline bool punctuationMark(const wchar_t letter) {
    return punctuations.find_first_of(letter) != std::wstring::npos;
}

/// \brief Checks whether given letter is a non connecting letter.
///
/// \param letter a letter to check.
///
/// \return \code true if the letter is a non connecting letter.
inline bool nonConnectingLetter(const wchar_t letter) {
    return non_connecting_letters.find_first_of(letter) != std::wstring::npos;
}

/// \brief Checks whether given letter is a number.
///
/// \param letter a letter to check.
///
/// \return \code true if the letter is a number.
inline bool number(const wchar_t letter) { return letter >= L'0' && letter <= L'9'; }

/// \brief Checks whether given letter is a number or delimiter.
///
/// \param letter a letter to check.
///
/// \return \code true if the letter is a number or delimiter.
inline bool delimiterOrNumber(const wchar_t letter) { return number(letter) || delimiter(letter); }

/// \brief Checks whether given letter is a long vowel.
///
/// \param letter a letter to check.
///
/// \return \code true if the letter is a long vowel.
inline bool longVowel(const wchar_t letter) {
    return letter == ya2 || letter == waw || alefs.find_first_of(letter) != std::string::npos;
}

/// \brief Checks whether given letter is a shamsi letter.
///
/// \param letter a letter to check.
///
/// \return \code true if the letter is a shamsi letter.
inline bool shamsi(const wchar_t letter) {
    return letter == ta2 || letter == tha2 || letter == dal || letter == thal || letter == ra2 ||
           letter == zain || letter == sheen || letter == seen || letter == sad || letter == dad ||
           letter == tah || letter == zah || letter == lam || letter == noon;
}

/// \brief Checks whether given letter is a diacritic.
///
/// \param letter a letter to check.
///
/// \return \code true if the letter is diacritic.
inline bool diacritic(const wchar_t letter) {
    return diacritics.find_first_of(letter) != std::string::npos;
}
}
}
