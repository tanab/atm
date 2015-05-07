#pragma once

#include <string>

namespace atm {
namespace common {
namespace inflections {
const static std::string start_delimiter = "//";
const static std::string middle_delimiter = "||";
const static std::string end_delimiter = "\\\\";

/// \todo document this class.
class Inflections {
  public:
    explicit Inflections(bool shouldApplyPlusRules) : m_apply_plus_rules(shouldApplyPlusRules) {}

    void apply(std::wstring &inflection, std::wstring &field) {
        if (inflection.empty() || inflection.find_first_not_of(L' ') == std::wstring::npos) {
            return;
        }

    }

  protected:
    wchar_t m_start_letter;
    bool m_apply_plus_rules;

    virtual bool applyStripDiacriticChange() = 0;
    /// \todo Is it really safe to return a refernce?
    virtual std::wstring &nonDiacriticField() = 0;
};
}
}
}
