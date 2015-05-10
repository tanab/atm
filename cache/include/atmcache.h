#pragma once

#include <list>
#include <locale>
#include <map>
#include <memory>
#include <vector>

#include <enums.hpp>
#include <rows.h>

namespace atm {
namespace cache {

using CategoryRows = std::vector<const CategoryRow>;
using AffixRows = std::vector<const AffixRow>;

using AffixCategoryMap = std::multimap<uint64_t, const AffixCategoryRow>;
using AffixCategoryMapRange = std::pair<AffixCategoryMap::iterator, AffixCategoryMap::iterator>;

using CompatibilityRulesKey = std::pair<uint64_t, Rules>;
using CompatibilityRulesMap = std::multimap<CompatibilityRulesKey, const CompatibilityRulesRow>;
using CompatibilityRulesMapRange =
    std::pair<CompatibilityRulesMap::iterator, CompatibilityRulesMap::iterator>;

///
/// \brief The AtmCache class defines common interface for all cache implementations.
/// \todo Prepare for error reporting.
///
class AtmCache {
  public:
    explicit AtmCache() {}
    virtual ~AtmCache() {}

    ///
    /// \brief itemTypesForRule returns apropriate item types for requested rule.
    /// \param rule the rule.
    /// \param type1 first item type.
    /// \param type2 second item type.
    /// \return \code true if item types pair exists for given rule.
    ///
    inline static bool itemTypesForRule(const Rules &rule, ItemTypes &type1, ItemTypes &type2) {
        switch (rule) {
            case Rules::AA:
                type1 = ItemTypes::PREFIX;
                type2 = ItemTypes::PREFIX;
                break;
            case Rules::AB:
                type1 = ItemTypes::PREFIX;
                type2 = ItemTypes::STEM;
                break;
            case Rules::AC:
                type1 = ItemTypes::PREFIX;
                type2 = ItemTypes::SUFFIX;
                break;
            case Rules::BC:
                type1 = ItemTypes::STEM;
                type2 = ItemTypes::SUFFIX;
                break;
            case Rules::CC:
                type1 = ItemTypes::SUFFIX;
                type2 = ItemTypes::SUFFIX;
                break;
            default:
                return false;
        }
        return true;
    }

    ///
    /// \brief initCache initializes cache.
    /// \return \code true if cache was initialized properly.
    ///
    virtual bool initCache() = 0;

    ///
    /// \brief prefixTable returns all rows from the prefix table.
    /// \return vector of rows in the prefix table.
    ///
    virtual const std::shared_ptr<AffixRows> prefixTable() const = 0;

    ///
    /// \brief suffixTable returns all rows from the suffix table.
    /// \return vector of rows in the suffix table.
    ///
    virtual const std::shared_ptr<AffixRows> suffixTable() const = 0;

    ///
    /// \brief stemTable returns all rows from the stem table.
    /// \return vector of rows in the stem table.
    ///
    virtual const std::shared_ptr<AffixRows> stemTable() const = 0;

    ///
    /// \brief categoriesTable returns all rows from the category table.
    /// \return vector of rows in category table.
    ///
    virtual const std::shared_ptr<CategoryRows> categoriesTable() const = 0;

    ///
    /// \brief findPrefixCategories returns prefix_category rows for given \code prefix_id.
    /// \param prefix_id id of the prefix.
    /// \return pair of iterators that mark first and last found row.
    ///
    virtual const AffixCategoryMapRange findPrefixCategories(uint64_t prefix_id) const = 0;

    ///
    /// \brief findSuffixCategories return suffix_category rows for given \code suffix_id.
    /// \param suffix_id id of the suffix.
    /// \return pair of iterators that mark first and last found row.
    ///
    virtual const AffixCategoryMapRange findSuffixCategories(uint64_t suffix_id) const = 0;

    ///
    /// \brief findStemCategories returns stem_category rows for given \code stem_id.
    /// \param stem_id id of the stem
    /// \return pair of iterators that mark first and last found row.
    ///
    virtual const AffixCategoryMapRange findStemCategories(uint64_t stem_id) const = 0;

    ///
    /// \brief findAffixCategories returns affix categories for given \code category_id.
    /// \param category_id id of the category.
    /// \return pair of iterators that mark first and last found row.
    ///
    virtual const AffixCategoryMapRange findAffixCategories(uint64_t category_id) const = 0;

    ///
    /// \brief findAffixName returns affix name for given \code affix_id.
    /// \param type an affix type.
    /// \param affix_id an affix id.
    /// \return affix name.
    ///
    virtual std::wstring findAffixName(const ItemTypes &type, uint64_t affix_id) const = 0;

    ///
    /// \todo document the purpose and meaning. Original is isAcceptState from common/tree.h
    /// \brief acceptsState
    /// \param type
    /// \param category_id
    /// \return
    ///
    virtual bool acceptsState(const ItemTypes &type, uint64_t category_id) const = 0;

    ///
    /// \todo document the purpose and meaning. Original is hasCompatibleAffixes from common/tree.h
    /// \brief hasCompatibleAffixes
    /// \param type
    /// \param category_id
    /// \return
    ///
    virtual bool hasCompatibleAffixes(const ItemTypes &type, uint64_t category_id) const = 0;

    ///
    /// \brief findCompatibilityRules finds all compatibility rules for given \code rule and \code
    /// category_id.
    /// \param rule the rule to search for.
    /// \param category_id the category id for which compatibility rules are searched.
    /// \param first \code true if \code category_id param is \code category_id1 from the database,
    /// otherwise \code it considered to be \code category_id2.
    /// \return pair of iterators that mark first and last found row.
    ///
    virtual CompatibilityRulesMapRange findCompatibilityRules(const Rules &rule,
                                                              uint64_t category_id,
                                                              bool first = true) const = 0;

  protected:
    std::shared_ptr<AffixRows> m_prefix_rows;       //!< The content of the \code prefix table.
    std::shared_ptr<AffixRows> m_stem_rows;         //!< The content of the \code stem table.
    std::shared_ptr<AffixRows> m_suffix_rows;       //!< The content of the \code suffix table.
    std::shared_ptr<CategoryRows> m_category_rows;  //!< The content of the \code category table.
    ///
    /// \brief m_prefix_category_rows The content of the prefix_category table. The key is
    /// prefix_id.
    ///
    std::shared_ptr<AffixCategoryMap> m_prefix_category_rows;
    ///
    /// \brief m_prefix_category_rows_by_category_id The content of the prefix_category table. The
    /// key is category_id.
    ///
    std::shared_ptr<AffixCategoryMap> m_prefix_category_rows_by_category_id;
    ///
    /// \brief m_suffix_category_rows The content of the suffix_category table. The key is
    /// suffix_id.
    ///
    std::shared_ptr<AffixCategoryMap> m_suffix_category_rows;
    ///
    /// \brief m_suffix_category_rows_by_category_id The contents of the suffix_category table. The
    /// key is category_id.
    ///
    std::shared_ptr<AffixCategoryMap> m_suffix_category_rows_by_category_id;
    ///
    /// \brief m_stem_category_rows The content of the stem_category table. The key is stem_id.
    ///
    std::shared_ptr<AffixCategoryMap> m_stem_category_rows;
    ///
    /// \brief m_stem_category_rows_by_category_id The content of the stem_category table. The key
    /// is category_id.
    ///
    std::shared_ptr<AffixCategoryMap> m_stem_category_rows_by_category_id;
    ///
    /// \brief m_compatibility_rules_rows_1 The content of compatibility_rules table. The key is
    /// pair category_id1 and type.
    ///
    std::shared_ptr<CompatibilityRulesMap> m_compatibility_rules_rows_1;
    ///
    /// \brief m_compatibility_rules_rows_2 The content of compatibility_rules table. The key is
    /// pair category_id2 and type.
    ///
    std::shared_ptr<CompatibilityRulesMap> m_compatibility_rules_rows_2;
};
}
}
