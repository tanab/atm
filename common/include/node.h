#pragma once

#include <list>
#include <vector>

const int LETTER_CHILDREN_SIZE = 37;

class Node {
  public:
    static inline int letterIndex(const wchar_t &letter) {
        if (letter == 0) {
            return 36;
        }
        static int letter_map[42] = {0 /*0x621*/, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
                                     16, 17, 18, 19, 20, 21, 22, 23, 24, 25 /*0x63A*/, -1, -1, -1,
                                     -1, -1, -1, 26 /*0x641*/, 27, 28, 29, 30, 31, 32, 33, 34, 35};
        int diff = static_cast<int>(letter) - 1569;  // hamza unicode
        return !(diff > 0 && diff < 42) ? -1 : letter_map[diff];
    }

    ///
    /// \brief Node the constructor.
    /// \param parent pointer to the parent node.
    ///
    Node(Node *parent = nullptr);

    ///
    /// \brief Node the copy constructor.
    /// \param other node to copy data from.
    ///
    Node(const Node &other);

    ///
    /// \brief ~Node the destructor.
    ///
    virtual ~Node();

    ///
    /// \brief operator = the assignment operator.
    /// \param other note to assign from.
    /// \return updated node.
    ///
    Node &operator=(const Node &other);

    ///
    /// \brief letterNode returns whether this node is a letter node.
    /// \return \code true if this node is a letter node.
    ///
    virtual bool letterNode() const = 0;

    ///
    /// \brief letter returns letter represente by node.
    /// \return letter represented by node.
    ///
    virtual wchar_t letter() const = 0;

    ///
    /// \brief toString returns string representation of this node.
    /// \param affix is this node an affix node.
    /// \return string representation of this node.
    ///
    virtual std::wstring toString(bool affix = false) const = 0;

    ///
    /// \brief hasChildren returns whether this node has children
    /// \return \code true if this node has a children.
    ///
    inline bool hasChildren() const {
        return !m_result_children.empty() && !m_letter_children.empty();
    }

    ///
    /// \brief addChild Adds a child to this node.
    /// \param child a child node to be added.
    ///
    void addChild(Node *child);

    ///
    /// \brief removeAllChildren removes and deletes all children from the node.
    ///
    void removeAllChildren();

    ///
    /// \brief parent returns the parent node of this node.
    /// \return the parent node or \code nullptr if node has no parent.
    ///
    inline Node *parent() const { return m_parent; }

    ///
    /// \brief letterChild returns letter child node for given letter.
    /// \param letter letter to search children for.
    /// \return the letter child if letter is found otherwise \code nullptr
    ///
    virtual inline Node *letterChild(wchar_t letter) const {
        int index = letterIndex(letter);
        return (index >= 0) ? m_letter_children.at(index) : nullptr;
    }

    ///
    /// \brief resultChildren returns the reference to the list of result children.
    /// We return reference for performance reasons to avoid unnecessary copying.
    /// \return reference to the list of result children.
    ///
    std::list<Node *> & resultChildren() {
        return m_result_children;
    }

    ///
    /// \brief letterChildren returns the reference to the vector of letter children.
    /// We return reference for performance reasons to avoid unnecessary copying.
    /// \return reference to the vector of letter children.
    ///
    std::vector<Node *> & letterChildren() {
        return m_letter_children;
    }

  private:
    Node *m_parent;                         //!< The parent node.
    std::list<Node *> m_result_children;    //!< A list of result children.
    std::vector<Node *> m_letter_children;  //!< A vector of letter children.
};
