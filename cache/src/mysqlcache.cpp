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
        m_prefix_rows = make_shared<list<PrefixRow> >();
        while (resultSet->next()) {
            m_prefix_rows->emplace_back(
                resultSet->getUInt64(1),
                to_utf<wchar_t>(resultSet->getString(2).asStdString(), "Latin1"));
        }

        // Load suffix table
        statement.reset(
            m_connection->prepareStatement("SELECT id, name FROM suffix ORDER BY id ASC"));
        resultSet.reset(statement->executeQuery());

        m_suffix_rows = make_shared<list<SuffixRow> >();
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
        m_prefix_category_rows = make_shared<PrefixCategoryMap>();
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

        // Load suffix category table
        statement.reset(m_connection->prepareStatement(
            "SELECT suffix_id, category_id, abstract_categories, sources, raw_data, POS, "
            "description_id, reverse_description FROM suffix_category ORDER BY suffix_id ASC"));
        resultSet.reset(statement->executeQuery());
        m_suffix_category_rows = make_shared<SuffixCategoryMap>();
        while (resultSet->next()) {
            uint64_t key = resultSet->getUInt64(1);
            m_suffix_category_rows->insert(pair<uint64_t, SuffixCategoryRow>(
                key,
                SuffixCategoryRow(key, resultSet->getUInt64(2), resultSet->getString(3),
                                  to_utf<wchar_t>(resultSet->getString(4).asStdString(), "Latin1"),
                                  to_utf<wchar_t>(resultSet->getString(5).asStdString(), "Latin1"),
                                  to_utf<wchar_t>(resultSet->getString(6).asStdString(), "Latin1"),
                                  resultSet->getUInt64(7), resultSet->getBoolean(8))));
        }

        // Load compatibility rules
        statement.reset(m_connection->prepareStatement(
            "SELECT category_id1, category_id2, type, sources, resulting_category, inflections FROM "
            "compatibility_rules ORDER BY type, category_id1, category_id2 ASC"));
        resultSet.reset(statement->executeQuery());
        m_compatibility_rules_rows_1 = make_shared<CompatibilityRulesMap>();
        m_compatibility_rules_rows_2 = make_shared<CompatibilityRulesMap>();
        while (resultSet->next()) {
            uint64_t category_id_1 = resultSet->getUInt64(1);
            uint64_t category_id_2 = resultSet->getUInt64(2);
            m_compatibility_rules_rows_1->insert(pair<CompatibilityRulesKey, CompatibilityRulesRow>(
                CompatibilityRulesKey(category_id_1, static_cast<Rules>(resultSet->getUInt(3))),
                CompatibilityRulesRow(
                    category_id_1, category_id_2, static_cast<Rules>(resultSet->getUInt(3)),
                    resultSet->getString(4), resultSet->getUInt64(5),
                    to_utf<wchar_t>(resultSet->getString(6).asStdString(), "Latin1"))));
            m_compatibility_rules_rows_2->insert(pair<CompatibilityRulesKey, CompatibilityRulesRow>(
                CompatibilityRulesKey(category_id_2, static_cast<Rules>(resultSet->getUInt(3))),
                CompatibilityRulesRow(
                    category_id_1, category_id_2, static_cast<Rules>(resultSet->getUInt(3)),
                    resultSet->getString(4), resultSet->getUInt64(5),
                    to_utf<wchar_t>(resultSet->getString(6).asStdString(), "Latin1"))));
        }

        // Load categories
        statement.reset(m_connection->prepareStatement(
            "SELECT id, name, type, sources, abstract FROM category ORDER BY id ASC"));
        resultSet.reset(statement->executeQuery());
        m_category_rows = make_shared<CategoryRows>();
        while (resultSet->next()) {
            m_category_rows->emplace_back(
                resultSet->getUInt64(1),
                to_utf<wchar_t>(resultSet->getString(2).asStdString(), "Latin1"),
                static_cast<ItemTypes>(resultSet->getUInt(3)), resultSet->getString(4),
                resultSet->getBoolean(5));
        }
    });

    return true;
}

const shared_ptr<PrefixRows> MySqlCache::prefixTable() const { return m_prefix_rows; }

const shared_ptr<SuffixRows> MySqlCache::suffixTable() const { return m_suffix_rows; }

const shared_ptr<CategoryRows> MySqlCache::categoriesTable() const { return m_category_rows; }

const PrefixCategoryMapRange MySqlCache::findPrefixCategories(uint64_t prefix_id) const {
    return m_prefix_category_rows->equal_range(prefix_id);
}

const SuffixCategoryMapRange MySqlCache::findSuffixCategories(uint64_t suffix_id) const {
    return m_suffix_category_rows->equal_range(suffix_id);
}

bool MySqlCache::acceptsState(const ItemTypes &type, uint64_t category_id) const {
    bool retVal = false;
    // TODO: Are we sure that STEM and SUFFIX are treated the same!?
    if (type == ItemTypes::PREFIX) {
        auto abCheck = m_compatibility_rules_rows_1->find(CompatibilityRulesKey(
                           category_id, Rules::AB)) != m_compatibility_rules_rows_1->end();
        auto acCheck = m_compatibility_rules_rows_1->find(CompatibilityRulesKey(
                           category_id, Rules::AC)) != m_compatibility_rules_rows_1->end();
        retVal = abCheck && acCheck;
    } else {
        auto acCheck = m_compatibility_rules_rows_2->find(CompatibilityRulesKey(
                           category_id, Rules::AC)) != m_compatibility_rules_rows_2->end();

        auto bcCheck = m_compatibility_rules_rows_2->find(CompatibilityRulesKey(
                           category_id, Rules::BC)) != m_compatibility_rules_rows_2->end();
        retVal = acCheck && bcCheck;
    }
    return retVal;
}

bool MySqlCache::hasCompatibleAffixes(const ItemTypes &type, uint64_t category_id) const {
    // TODO: Are we sure that STEM and SUFFIX are treated the same!?
    return m_compatibility_rules_rows_1->find(CompatibilityRulesKey(
               category_id, type == ItemTypes::PREFIX ? Rules::AA : Rules::CC)) !=
           m_compatibility_rules_rows_1->end();
    return true;
}

CompatibilityRulesMapRange MySqlCache::findCompatibilityRules(const Rules &rule,
                                                              uint64_t category_id,
                                                              bool first) const {
    ItemTypes type1;
    ItemTypes type2;

    if (!AtmCache::itemTypesForRule(rule, type1, type2)) {
        return CompatibilityRulesMapRange();
    }

    ItemTypes type_of_category = m_category_rows->at(category_id).type;
    if ((first ? type1 : type2) != type_of_category) {
        return CompatibilityRulesMapRange();
    }

    CompatibilityRulesKey key(category_id, rule);
    if (first) {
        return m_compatibility_rules_rows_1->equal_range(key);
    } else {
        return m_compatibility_rules_rows_2->equal_range(key);
    }
}
