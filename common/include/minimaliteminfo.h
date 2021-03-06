#pragma once

#include <string>
#include <vector>
#include <enums.hpp>
#include <constants.h>
#include <rows.h>

using dbitvec = std::vector<bool>;

///
/// \brief The MinimalItemInfo class contains minimal information on a match
/// which could be stem or an affix.
///
class MinimalItemInfo {
  public:
    ///
    /// \brief MinimalItemInfo The default constructor.
    ///
    //    MinimalItemInfo() : m_description_id(0), m_category_id(0),
    //    m_abstract_categories(MAX_SOURCES) {}
    MinimalItemInfo()
        : m_description(),
          m_description_id(0),
          m_category_id(0),
          m_abstract_categories(),
          m_raw_data(),
          m_part_of_speech() {}

    ///
    /// \brief ~MinimalItemInfo The destructor.
    ///
    virtual ~MinimalItemInfo() { m_abstract_categories.clear(); }

    ///
    /// \brief updateFrom Updates this instance with values from given \ref AffixCategoryRow
    /// \param row The row to take data from.
    ///
    void updateFrom(const atm::cache::AffixCategoryRow &row) {
        m_type = row.affix_type;
        m_category_id = row.category_id;
        m_raw_data = row.raw_data;
        m_part_of_speech = row.part_of_speech;
        m_description_id = row.description_id;
        m_abstract_categories.clear();
    }

    ///
    /// \brief setDescription sets the description text and resets description id to -1.
    /// \param description the description to set.
    ///
    inline void setDescription(const std::string &description) {
        m_description_id = 0;
        m_description = description;
    }

    std::string description() const;

    ///
    /// \brief setDescriptionId sets description id and clears description text.
    /// \param description_id the description id to set.
    ///
    inline void setDescriptionId(uint64_t description_id) {
        m_description_id = description_id;
        m_description.clear();
    }

    inline uint64_t descriptionId() const { return m_description_id; }

    inline void setType(const ItemTypes &type) { m_type = type; }

    inline ItemTypes type() const { return m_type; }

    inline void setCategoryId(uint64_t categoryId) { m_category_id = categoryId; }

    inline uint64_t categoryId() const { return m_category_id; }

    inline void setAbstractCategories(const dbitvec &abstract_categories) {
        m_abstract_categories = abstract_categories;
    }

    inline dbitvec abstractCategories() const { return m_abstract_categories; }

    inline dbitvec &abstractCategories() { return m_abstract_categories; }

    inline void setRawData(const std::wstring &raw_data) { m_raw_data = raw_data; }

    inline std::wstring rawData() const { return m_raw_data; }

    inline void setPartOfSpeech(const std::wstring &part_of_speech) {
        m_part_of_speech = part_of_speech;
    }

    inline std::wstring partOfSpeech() const { return m_part_of_speech; }

  private:
    std::string m_description;      //!< This is description of a matching prefix/stem/suffix.
    uint64_t m_description_id;      //!< An id of a description of a matching prefix/stem/suffix.
    ItemTypes m_type;               //!< The type of the item.
    uint64_t m_category_id;         //!< The category id.
    dbitvec m_abstract_categories;  //!< Abstract categories flags. Used only for stems.
    std::wstring m_raw_data;        //!< The root or stem of the input string.
    std::wstring m_part_of_speech;  //!< The part of speech of the match.
};
