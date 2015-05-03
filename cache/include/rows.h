#pragma once

#include <iostream>
#include <string>
#include <vector>

#include <conversions.h>
#include <enums.h>

///
/// \brief The AffixRow struct represents common columns of rows for prefix, stem and suffix tables.
///
struct AffixRow {
    AffixRow() : id(0), name() {}
    AffixRow(uint64_t anId, const std::wstring& aName) : id(anId), name(aName) {}
    AffixRow(const AffixRow& other) : id(other.id), name(other.name) {}
    AffixRow(AffixRow&& other) : id(std::move(other.id)), name(std::move(other.name)) {}

    uint64_t id;
    std::wstring name;
};

///
/// \brief The PrefixRow struct represents row of the prefix table.
///
struct PrefixRow : public AffixRow {
    PrefixRow() : AffixRow() {}
    PrefixRow(uint64_t anId, const std::wstring& aName) : AffixRow(anId, aName) {}
    PrefixRow(const PrefixRow& other) : AffixRow(other) {}
    PrefixRow(PrefixRow&& other) : AffixRow(other) {}
};

///
/// \brief The SuffixRow struct represents row of the suffix table.
///
struct SuffixRow : public AffixRow {
    SuffixRow() : AffixRow() {}
    SuffixRow(uint64_t anId, const std::wstring& aName) : AffixRow(anId, aName) {}
    SuffixRow(const SuffixRow& other) : AffixRow(other) {}
    SuffixRow(SuffixRow&& other) : AffixRow(other) {}
};

///
/// \brief The AffixCategoryRow struct represents common columns of rows for prefix_category,
/// stem_category and suffix_category tables.
///
struct AffixCategoryRow {
    AffixCategoryRow()
        : category_id(0),
          abstract_categories(),
          sources(),
          raw_data(),
          part_of_speech(),
          description_id(0),
          reverse_description(false) {}
    AffixCategoryRow(uint64_t aCategoryId, const std::string& theAbstractCategories,
                     const std::wstring& theSources, const std::wstring& theRawData,
                     const std::wstring& aPartOfSpeech, uint64_t aDescriptionId,
                     bool aReverseDescription)
        : category_id(aCategoryId),
          abstract_categories(atm::conversions::to_bool_vector(theAbstractCategories)),
          sources(theSources),
          raw_data(theRawData),
          part_of_speech(aPartOfSpeech),
          description_id(aDescriptionId),
          reverse_description(aReverseDescription) {}
    AffixCategoryRow(const AffixCategoryRow& other)
        : category_id(other.category_id),
          abstract_categories(other.abstract_categories),
          sources(other.sources),
          raw_data(other.raw_data),
          part_of_speech(other.part_of_speech),
          description_id(other.description_id),
          reverse_description(other.reverse_description) {}

    uint64_t category_id;
    std::vector<bool> abstract_categories;
    std::wstring sources;
    std::wstring raw_data;
    std::wstring part_of_speech;
    uint64_t description_id;
    bool reverse_description;
};

///
/// \brief The PrefixCategoryRow struct represents row of the prefix_category table.
///
struct PrefixCategoryRow : public AffixCategoryRow {
    PrefixCategoryRow() : AffixCategoryRow(), prefix_id(0) {}
    PrefixCategoryRow(uint64_t aPrefixId, uint64_t aCategoryId,
                      const std::string& theAbstractCategories, const std::wstring& theSources,
                      const std::wstring& theRawData, const std::wstring& aPartOfSpeech,
                      uint64_t aDescriptionId, bool aReverseDescription)
        : AffixCategoryRow(aCategoryId, theAbstractCategories, theSources, theRawData,
                           aPartOfSpeech, aDescriptionId, aReverseDescription),
          prefix_id(aPrefixId) {}
    PrefixCategoryRow(const PrefixCategoryRow& other)
        : AffixCategoryRow(other), prefix_id(other.prefix_id) {}

    uint64_t prefix_id;
};

///
/// \brief The SuffixCategoryRow struct represents row of the suffix_category table.
///
struct SuffixCategoryRow : public AffixCategoryRow {
    SuffixCategoryRow() : AffixCategoryRow(), suffix_id(0) {}
    SuffixCategoryRow(uint64_t aSuffixId, uint64_t aCategoryId,
                      const std::string& theAbstractCategories, const std::wstring& theSources,
                      const std::wstring& theRawData, const std::wstring& aPartOfSpeech,
                      uint64_t aDescriptionId, bool aReverseDescription)
        : AffixCategoryRow(aCategoryId, theAbstractCategories, theSources, theRawData,
                           aPartOfSpeech, aDescriptionId, aReverseDescription),
          suffix_id(aSuffixId) {}
    SuffixCategoryRow(const SuffixCategoryRow& other)
        : AffixCategoryRow(other), suffix_id(other.suffix_id) {}

    uint64_t suffix_id;
};

///
/// \brief The CompatibilityRulesRow struct represents row of the compatibility_rules table.
///
struct CompatibilityRulesRow {
    CompatibilityRulesRow()
        : category_id_1(0),
          category_id_2(0),
          type(),
          sources(),
          resulting_category(0),
          inflections() {}
    CompatibilityRulesRow(uint64_t aCategoryId1, uint64_t aCategoryId2, Rules aType,
                          const std::string& theSources, uint64_t aResultingCategory,
                          const std::wstring& theInflections)
        : category_id_1(aCategoryId1),
          category_id_2(aCategoryId2),
          type(aType),
          sources(atm::conversions::to_bool_vector(theSources)),
          resulting_category(aResultingCategory),
          inflections(theInflections) {}
    CompatibilityRulesRow(const CompatibilityRulesRow& other)
        : category_id_1(other.category_id_1),
          category_id_2(other.category_id_2),
          type(other.type),
          sources(other.sources),
          resulting_category(other.resulting_category),
          inflections(other.inflections) {}

    uint64_t category_id_1;
    uint64_t category_id_2;
    Rules type;
    std::vector<bool> sources;
    uint64_t resulting_category;
    std::wstring inflections;
};
