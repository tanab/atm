#pragma once

#include <codecvt>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <vector>

#include <enums.hpp>
#include <rows.h>

using CategoryRows = std::vector<CategoryRow>;
using PrefixRows = std::list<AffixRow>;
using SuffixRows = std::list<AffixRow>;
using StemRows = std::list<AffixRow>;

using PrefixCategoryMap = std::multimap<uint64_t, AffixCategoryRow>;
using PrefixCategoryMapRange = std::pair<PrefixCategoryMap::iterator, PrefixCategoryMap::iterator>;

using SuffixCategoryMap = std::multimap<uint64_t, AffixCategoryRow>;
using SuffixCategoryMapRange = std::pair<SuffixCategoryMap::iterator, SuffixCategoryMap::iterator>;

using CompatibilityRulesKey = std::pair<uint64_t, Rules>;
using CompatibilityRulesMap = std::multimap<CompatibilityRulesKey, CompatibilityRulesRow>;
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
    /// \return list of rows in prefix table.
    ///
    virtual const std::shared_ptr<PrefixRows> prefixTable() const = 0;
    ///
    /// \brief suffixTable returns all rows from the suffix table.
    /// \return list of rows in suffix table.
    ///
    virtual const std::shared_ptr<SuffixRows> suffixTable() const = 0;
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
    virtual const PrefixCategoryMapRange findPrefixCategories(uint64_t prefix_id) const = 0;

    ///
    /// \brief findSuffixCategories return suffix_category rows for given \code suffix_id.
    /// \param suffix_id id of the suffix.
    /// \return pair of iterators taht mark first and last found row.
    ///
    virtual const SuffixCategoryMapRange findSuffixCategories(uint64_t suffix_id) const = 0;

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
};
