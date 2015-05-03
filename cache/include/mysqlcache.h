#pragma once

#include <codecvt>
#include <list>
#include <map>
#include <memory>

#include <atmcache.h>
#include <rows.h>

namespace sql {
class Driver;
class Connection;
class PreparedStatement;
class ResultSet;
}

class MySqlCache : public AtmCache {
  public:
    explicit MySqlCache();
    virtual ~MySqlCache();

    virtual bool initCache() override;

    virtual const std::shared_ptr<PrefixRows> prefixTable() const override;
    virtual const std::shared_ptr<SuffixRows> suffixTable() const override;

    virtual const PrefixCategoryMapRange findPrefixCategories(uint64_t prefix_id) const override;

  private:
    sql::Driver *m_driver;
    std::unique_ptr<sql::Connection> m_connection;

    std::shared_ptr<PrefixRows> m_prefix_rows;  //!< The content of the prefix table.
    std::shared_ptr<SuffixRows> m_suffix_rows;  //!< The content of the suffix table.

    ///
    /// \brief m_prefix_category_rows The content of the prefix_category table. The key is
    /// prefix_id.
    ///
    std::shared_ptr<PrefixCategoryMap> m_prefix_category_rows;
    ///
    /// \brief m_suffix_category_rows The content of the suffix_category table. The key is
    /// suffix_id.
    ///
    std::shared_ptr<SuffixCategoryMap> m_suffix_category_rows;
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

    /// \todo Document the purpose of this method.
    virtual bool acceptsState(const ItemTypes &type, uint64_t category_id) const override;

    /// \todo Document the purpose of this method.
    virtual bool hasCompatibleAffixes(const ItemTypes &type, uint64_t category_id) const override;
};
