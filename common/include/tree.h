#pragma once

#include <atmcache.h>
#include <enums.hpp>
#include <types.h>

///
/// \brief The Tree class
/// \todo Describe and document this class.
///
class Tree {
  public:
    ///
    /// \brief Tree the constructor.
    ///
    explicit Tree(AtmCache *cache);

    ///
    /// \brief Tree deleted copy constructor.
    ///
    Tree(const Tree &) = delete;

    ///
    /// \brief ~Tree the destructor.
    ///
    virtual ~Tree();

    ///
    /// \brief operator = deleted assignment operator.
    ///
    Tree &operator=(const Tree &) = delete;

    ///
    /// \brief setupForItemType Sets up this instance for item type given by \code type
    /// \param type The type to setup tree for.
    /// \return \code true if the tree was set up successfuly.
    ///
    bool setupForItemType(const ItemTypes &type);

    ///
    /// \brief affixType returns \code true for affixes and sets type to the type of this tree,
    /// otherwise \code false is returned.
    /// \param type type to be set.
    /// \return \code true if this is affix tree
    ///
    bool affixType(ItemTypes &type);

    ///
    /// \brief firstNode Returns first or root node of the tree.
    /// \return first or root node.
    ///
    inline Node *firstNode() const { return m_base; }

    ///
    /// \brief reset Resets the tree.
    ///
    void reset();

    ///
    /// \brief buildAffixTree
    /// \param type
    /// \return
    /// \todo Document this method and algorithms used in it.
    ///
    bool buildAffixTree(const ItemTypes &type);

    ///
    /// \brief addElement Adds new element (node) from given input parameters.
    /// \param letters
    /// \param affix_id
    /// \param category_id
    /// \param resulting_category_id
    /// \param accepts_state
    /// \param raw_data
    /// \param inflected_raw_data
    /// \param inflection_rule_description
    /// \param current_node
    /// \return new node.
    ///
    Node *addElement(const std::wstring &letters, uint64_t affix_id, uint64_t category_id,
                     uint64_t resulting_category_id, bool accepts_state,
                     const std::wstring &raw_data, const std::wstring &inflected_raw_data,
                     const std::wstring &inflection_rule_description, Node *current_node);

    ///
    /// \todo Document purpose of this method.
    /// \brief buildHelper
    /// \param type
    /// \param category_id
    /// \param size
    /// \param current
    /// \return
    ///
    int buildHelper(const ItemTypes &type, uint64_t category_id, int size, Node *current);

  private:
    AtmCache *m_cache;
    bool m_affix;
    int m_last_id;
    int m_letter_nodes;
    int m_result_nodes;
    ItemTypes m_type;
    IdMap m_id_map;
    ReverseIdMap m_reverse_id_map;
    Node *m_base;

    bool buildAffixTreeFromPrefix();

    bool buildAffixTreeFromSuffix();
};
