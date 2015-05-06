#pragma once

#include <iostream>
#include <string>
#include <vector>

#include <conversions.h>
#include <enums.hpp>

///
/// \brief The CategoryRow struct represents a row of the category table.
///
struct CategoryRow {
    CategoryRow() : id(0), name(), type(ItemTypes::PREFIX), sources(), abstract(false) {}
    CategoryRow(uint64_t anId, const std::wstring& aName, const ItemTypes& aType,
                const std::string& theSources, bool anAbstract)
        : id(anId),
          name(aName),
          type(aType),
          sources(atm::conversions::to_bool_vector(theSources)),
          abstract(anAbstract) {}
    CategoryRow(const CategoryRow& other)
        : id(other.id),
          name(other.name),
          type(other.type),
          sources(other.sources),
          abstract(other.abstract) {}

    uint64_t id;
    std::wstring name;
    ItemTypes type;
    std::vector<bool> sources;
    bool abstract;
};

///
/// \brief The AffixRow struct represents common columns of rows for prefix, stem and suffix tables.
///
struct AffixRow {
    AffixRow() : affix_type(ItemTypes::PREFIX), id(0), name(), grammar_stem_id(0), sources() {}
    AffixRow(const ItemTypes& anAffixType, uint64_t anId, const std::wstring& aName,
             uint64_t aGrammarStemId = 0, const std::string& theSources = "")
        : affix_type(anAffixType),
          id(anId),
          name(aName),
          grammar_stem_id(aGrammarStemId),
          sources(atm::conversions::to_bool_vector(theSources)) {}
    AffixRow(const AffixRow& other)
        : affix_type(other.affix_type),
          id(other.id),
          name(other.name),
          grammar_stem_id(other.grammar_stem_id),
          sources(other.sources) {}
    AffixRow(AffixRow&& other)
        : affix_type(std::move(other.affix_type)),
          id(std::move(other.id)),
          name(std::move(other.name)),
          grammar_stem_id(std::move(other.grammar_stem_id)),
          sources(std::move(other.sources)) {}

    ItemTypes affix_type;
    uint64_t id;
    std::wstring name;
    uint64_t grammar_stem_id;   //!< Used only for stems.
    std::vector<bool> sources;  //!< Used only for stems.
};

///
/// \brief The AffixCategoryRow struct represents common columns of rows for prefix_category,
/// stem_category and suffix_category tables.
///
struct AffixCategoryRow {
    AffixCategoryRow()
        : affix_type(ItemTypes::PREFIX),
          affix_id(0),
          category_id(0),
          abstract_categories(),
          sources(),
          raw_data(),
          part_of_speech(),
          description_id(0),
          reverse_description(false) {}
    AffixCategoryRow(const ItemTypes& anAffixType, uint64_t anAffixId, uint64_t aCategoryId,
                     const std::string& theAbstractCategories, const std::wstring& theSources,
                     const std::wstring& theRawData, const std::wstring& aPartOfSpeech,
                     uint64_t aDescriptionId, bool aReverseDescription)
        : affix_type(anAffixType),
          affix_id(anAffixId),
          category_id(aCategoryId),
          abstract_categories(atm::conversions::to_bool_vector(theAbstractCategories)),
          sources(theSources),
          raw_data(theRawData),
          part_of_speech(aPartOfSpeech),
          description_id(aDescriptionId),
          reverse_description(aReverseDescription) {}
    AffixCategoryRow(const AffixCategoryRow& other)
        : affix_type(other.affix_type),
          affix_id(other.affix_id),
          category_id(other.category_id),
          abstract_categories(other.abstract_categories),
          sources(other.sources),
          raw_data(other.raw_data),
          part_of_speech(other.part_of_speech),
          description_id(other.description_id),
          reverse_description(other.reverse_description) {}

    ItemTypes affix_type;
    uint64_t affix_id;
    uint64_t category_id;
    std::vector<bool> abstract_categories;
    std::wstring sources;
    std::wstring raw_data;
    std::wstring part_of_speech;
    uint64_t description_id;
    bool reverse_description;
};

///
/// \brief The CompatibilityRulesRow struct represents a row of the compatibility_rules table.
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
