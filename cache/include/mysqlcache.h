#pragma once

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

namespace atm {
namespace cache {
class MySqlCache : public AtmCache {
  public:
    explicit MySqlCache();
    virtual ~MySqlCache();

    virtual bool initCache() override;

    virtual const std::shared_ptr<AffixRows> prefixTable() const override;
    virtual const std::shared_ptr<AffixRows> suffixTable() const override;
    virtual const std::shared_ptr<AffixRows> stemTable() const override;

    virtual const std::shared_ptr<CategoryRows> categoriesTable() const override;

    /// \todo Document the purpose of this method.
    virtual bool acceptsState(const ItemTypes &type, uint64_t category_id) const override;

    /// \todo Document the purpose of this method.
    virtual bool hasCompatibleAffixes(const ItemTypes &type, uint64_t category_id) const override;

    virtual const AffixCategoryMapRange findPrefixCategories(uint64_t prefix_id) const override;

    virtual const AffixCategoryMapRange findSuffixCategories(uint64_t suffix_id) const override;

    virtual const AffixCategoryMapRange findStemCategories(uint64_t stem_id) const override;

    virtual const AffixCategoryMapRange findAffixCategories(uint64_t category_id) const override;

    virtual std::wstring findAffixName(const ItemTypes &type, uint64_t affix_id) const override;

    virtual CompatibilityRulesMapRange findCompatibilityRules(const Rules &rule,
                                                              uint64_t category_id,
                                                              bool first = true) const override;

  private:
    sql::Driver *m_driver;
    std::unique_ptr<sql::Connection> m_connection;
};
}
}
