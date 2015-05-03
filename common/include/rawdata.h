#pragma once

#include <string>

///
/// \brief The RawData class
/// \todo Describe and document this class.
///
class RawData final {
  public:
    RawData(const std::wstring &original, const std::wstring &inflected = L"*")
        : m_original(original), m_inflected(inflected) {}

    bool operator==(const RawData &other) const {
        return m_original == other.m_original && m_inflected == other.m_inflected;
    }

    const std::wstring &actual() const { return (m_inflected == L"*") ? m_original : m_inflected; }

    const std::wstring &original() const { return m_original; }

  private:
    std::wstring m_original;   //!< Original string.
    std::wstring m_inflected;  //!< Inflected string.
};
