#include <mysqlcache.h>

#include <atomic>
#include <boost/locale.hpp>

#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>

using namespace std;
using namespace boost::locale::conv;

// const string DATABASE_URL = "tcp://127.0.0.1:3306";
const string DATABASE_URL = "unix:///opt/local/var/run/mysql56/mysqld.sock";
const string DATABASE_USER = "root";
const string DATABASE_PASSWORD = "root";
const string DATABASE_SCHEMA = "atm";

MySqlCache::MySqlCache() : AtmCache() {
    m_driver = get_driver_instance();
    m_connection.reset(m_driver->connect(DATABASE_URL, DATABASE_USER, DATABASE_PASSWORD));
    m_connection->setSchema(DATABASE_SCHEMA);
}

MySqlCache::~MySqlCache() { m_connection->close(); }

bool MySqlCache::initCache() {
    static once_flag once;
    call_once(once, [this] {
        // Load prefix table
        unique_ptr<sql::PreparedStatement> statement(
            m_connection->prepareStatement("SELECT id, name FROM prefix ORDER BY id ASC"));
        unique_ptr<sql::ResultSet> resultSet(statement->executeQuery());
        m_prefix_rows = make_shared<list<PrefixRow>>();
        while (resultSet->next()) {
            m_prefix_rows->emplace_back(
                resultSet->getUInt64(1),
                to_utf<wchar_t>(resultSet->getString(2).asStdString(), "Latin1"));
        }

        // Load suffix table
        statement.reset(
            m_connection->prepareStatement("SELECT id, name FROM suffix ORDER BY id ASC"));
        resultSet.reset(statement->executeQuery());

        m_suffix_rows = make_shared<list<SuffixRow>>();
        while (resultSet->next()) {
            m_suffix_rows->emplace_back(
                resultSet->getUInt64(1),
                to_utf<wchar_t>(resultSet->getString(2).asStdString(), "Latin1"));
        }

        // Load prefix category table
        statement.reset(m_connection->prepareStatement(
            "SELECT prefix_id, category_id, abstract_categories, sources, raw_data, POS, "
            "description_id, reverse_description FROM prefix_category ORDER BY prefix_id ASC"));
        resultSet.reset(statement->executeQuery());
        m_prefix_category_rows = make_shared<multimap<uint64_t, PrefixCategoryRow>>();
        while (resultSet->next()) {
            uint64_t key = resultSet->getUInt64(1);
            m_prefix_category_rows->insert(pair<uint64_t, PrefixCategoryRow>(
                key,
                PrefixCategoryRow(key, resultSet->getUInt64(2), resultSet->getString(3),
                                  to_utf<wchar_t>(resultSet->getString(4).asStdString(), "Latin1"),
                                  to_utf<wchar_t>(resultSet->getString(5).asStdString(), "Latin1"),
                                  to_utf<wchar_t>(resultSet->getString(6).asStdString(), "Latin1"),
                                  resultSet->getUInt64(7), resultSet->getBoolean(8))));
        }
    });

    return true;
}

const shared_ptr<list<PrefixRow>> MySqlCache::prefixTable() const { return m_prefix_rows; }

const shared_ptr<list<SuffixRow>> MySqlCache::suffixTable() const { return m_suffix_rows; }

const pair<PrefixCategoryMap::iterator, PrefixCategoryMap::iterator>
MySqlCache::findPrefixCategories(uint64_t prefix_id) const {
    return m_prefix_category_rows->equal_range(prefix_id);
}

bool MySqlCache::acceptsState(const ItemTypes &type, uint64_t category_id) const {
    // TODO: Stub method.
    return true;
}

bool MySqlCache::hasCompatibleAffixes(const ItemTypes &type, uint64_t category_id) const {
    // TODO: Stub method.
    return true;
}
