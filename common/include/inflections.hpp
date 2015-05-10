#pragma once

#include <boost/locale.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <string>
#include <util.h>
#include <diacritics.hpp>

namespace atm {
namespace common {
namespace inflections {

/// \todo document this class.
class Inflections {
  public:
    explicit Inflections(bool shouldApplyPlusRules = true)
        : m_start_letter(L'\0'), m_apply_plus_rules(shouldApplyPlusRules) {}

    void apply(std::wstring &inflection, std::wstring &field) {
        if (inflection.empty() || inflection.find_first_not_of(L' ') == std::wstring::npos) {
            return;
        }
        auto parts = util::split(inflection, end_delimiter);
        for (auto &part : parts) {
            boost::algorithm::trim_left(part);
            if (part.empty()) {
                continue;
            }

            auto start_prefix = m_start_letter + start_delimiter;
            if (part.find_first_of(start_prefix)) {
                part = part.substr(start_prefix.size());
                auto change_list = util::split(part, middle_delimiter);
                if (change_list.size() != 2) {
                    throw std::logic_error("Cannot apply inflections to the string '" +
                                           boost::locale::conv::from_utf(part, std::locale()) +
                                           "'");
                }
                auto rule = change_list[0];
                auto replacement = change_list[1];
                auto replacement_without_diactitics = removeDiacritics(replacement);
//                auto &non_diacritic_field = nonDiacriticField();
                auto non_diacritic_field = nonDiacriticField();
                bool non_diacritic = applyStripDiacriticChange();
                if (m_apply_plus_rules && rule == L"(+1)") {
                    field = replacement + field;
                    if (non_diacritic) {
                        non_diacritic_field = replacement_without_diactitics + non_diacritic_field;
                    }
                } else if (m_apply_plus_rules && rule == L"(+2)") {
                    field = field + replacement;
                    if (non_diacritic) {
                        non_diacritic_field = non_diacritic_field + replacement_without_diactitics;
                    }
                } else {
                    boost::algorithm::replace_all(field, rule, replacement);
                    if (non_diacritic) {
                        auto rule_without_diacritics = removeDiacritics(rule);
                        boost::algorithm::replace_all(non_diacritic_field, rule_without_diacritics,
                                                      replacement_without_diactitics);
                    }
                }
            }
        }
    }

  protected:
    wchar_t m_start_letter;
    bool m_apply_plus_rules;

    virtual bool applyStripDiacriticChange() = 0;
    /// \todo Is it really safe to return a refernce?
    virtual std::wstring &nonDiacriticField() = 0;

  private:
    const static std::wstring start_delimiter;// = L"//";
    const static std::wstring middle_delimiter;// = L"||";
    // const static std::wstring end_delimiter;// = L"\\\\";
    const static std::wstring end_delimiter;// = L"\\";
};

const std::wstring Inflections::start_delimiter = L"//";
const std::wstring Inflections::middle_delimiter = L"||";
// const std::wstring Inflections::end_delimiter = L"\\\\";
const std::wstring Inflections::end_delimiter = L"\\\\";


class RawDataInflections : protected Inflections {
  public:
    explicit RawDataInflections() : Inflections() { m_start_letter = L'r'; }
    void apply(std::wstring &inflection, std::wstring &affix, std::wstring &rawData) {
        m_affix = affix;
        Inflections::apply(inflection, rawData);
        affix = m_affix;
    }

  protected:
    virtual bool applyStripDiacriticChange() override { return true; }
    virtual std::wstring &nonDiacriticField() override { return m_affix; }

  private:
    std::wstring m_affix;
};

inline void applyRawDataInflections(std::wstring &inflection, std::wstring &affix,
                                    std::wstring &rawData) {
    RawDataInflections r;
    r.apply(inflection, affix, rawData);
}
}
}
}
