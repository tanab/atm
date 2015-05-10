#pragma once

#include <string>

namespace atm {
namespace common {

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
static const wchar_t aleft_superscript = 0x0670;
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
static const wchar_t paragraph_separator = 0x2029;

static const std::wstring punctuations = std::wstring(L":!_\\.,=-'\n\r\"")
                                             .append(1, fasila)
                                             .append(1, question_mark)
                                             .append(1, semicolon_ar)
                                             .append(1, full_stop1)
                                             .append(1, full_stop2)
                                             .append(1, full_stop3)
                                             .append(1, paragraph_separator);

inline bool punctuationMark(const wchar_t letter) {
    return punctuations.find_first_of(letter) != std::wstring::npos;
}
}
}
