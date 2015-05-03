#pragma once

#include <codecvt>
#include <list>
#include <locale>
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

    virtual const std::shared_ptr<std::list<PrefixRow>> prefixTable() const override;
    virtual const std::shared_ptr<std::list<SuffixRow>> suffixTable() const override;

    virtual const std::pair<std::multimap<uint64_t, PrefixCategoryRow>::iterator,
                            std::multimap<uint64_t, PrefixCategoryRow>::iterator>
    findPrefixCategories(uint64_t prefix_id) const override;

  private:
    std::wstring_convert<std::codecvt_utf8<wchar_t>> m_converter;
    sql::Driver *m_driver;
    std::unique_ptr<sql::Connection> m_connection;

    std::shared_ptr<std::list<PrefixRow>> m_prefix_rows;  //!< The content of the prefix table.
    std::shared_ptr<std::list<SuffixRow>> m_suffix_rows;  //!< The content of the suffix table.
    std::shared_ptr<PrefixCategoryMap>
        m_prefix_category_rows;  //!< The content of the prefix_category table. The key is
    // prefix_id.
    std::shared_ptr<std::multimap<uint64_t, SuffixCategoryRow>>
        m_suffix_category_row;  //!< The content of the suffix_category table. The key is suffix_id.

    virtual bool acceptsState(const ItemTypes &type, uint64_t category_id) const override;

    virtual bool hasCompatibleAffixes(const ItemTypes &type, uint64_t category_id) const override;
};
