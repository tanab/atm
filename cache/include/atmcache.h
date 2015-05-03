#pragma once

#include <codecvt>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <vector>

#include <enums.h>
#include <rows.h>

using PrefixRows = std::list<PrefixRow>;
using SuffixRows = std::list<SuffixRow>;

using PrefixCategoryMap = std::multimap<uint64_t, PrefixCategoryRow>;
using PrefixCategoryMapRange = std::pair<PrefixCategoryMap::iterator, PrefixCategoryMap::iterator>;

using SuffixCategoryMap = std::multimap<uint64_t, SuffixCategoryRow>;

using CompatibilityRulesKey = std::pair<uint64_t, Rules>;
using CompatibilityRulesMap = std::multimap<CompatibilityRulesKey, CompatibilityRulesRow>;

///
/// \brief The AtmCache class defines common interface for all cache implementations.
/// \todo Prepare for error reporting.
///
class AtmCache {
  public:
    explicit AtmCache() {}
    virtual ~AtmCache() {}

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
    /// \brief findPrefixCategories returns prefix_category rows for given \code prefix_id.
    /// \param prefix_id id of the prefix.
    /// \return pair of iterators that mark first and last row.
    ///
    virtual const PrefixCategoryMapRange findPrefixCategories(uint64_t prefix_id) const = 0;

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
};
