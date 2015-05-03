#pragma once

///
/// \brief The MultiplyParams class defines the different parameter settings for
/// the solution extracted.
///
class MultiplyParams {
  public:
    MultiplyParams()
        : m_raw_data(true),
          m_description(true),
          m_abstract_category(true),
          m_part_of_speech(true) {}

    inline bool rawDataOnly() {
        return m_raw_data && !m_description && !m_abstract_category &&
               !m_part_of_speech;
    }

    inline bool none() {
        return !m_raw_data && !m_description && !m_abstract_category &&
               !m_part_of_speech;
    }

    inline bool all() {
        return m_raw_data && m_description && m_abstract_category &&
               m_part_of_speech;
    }

    inline void setRawData(bool raw_data) { m_raw_data = raw_data; }

    inline bool rawData() const { return m_raw_data; }

    inline void setDescription(bool description) {
        m_description = description;
    }

    inline bool description() const { return m_description; }

    inline void setAbstractCategory(bool abstract_category) {
        m_abstract_category = abstract_category;
    }

    inline bool abstractCategory() const { return m_abstract_category; }

    inline void setPartOfSpeech(bool pos) { m_part_of_speech = pos; }

    inline bool partOfSpeech() const { return m_part_of_speech; }

  private:
    bool m_raw_data;
    bool m_description;
    bool m_abstract_category;
    bool m_part_of_speech;
};
