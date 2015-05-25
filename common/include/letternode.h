#pragma once

#include <node.h>

class LetterNode : public Node {
  public:
    ///
    /// \brief LetterNode The constructor.
    /// \param letter The letter to set upon construction.
    ///
    explicit LetterNode(wchar_t letter) : Node(), m_letter(letter) {}

    ///
    /// \brief LetterNode The copy constructor.
    /// \param other The node to copy from.
    ///
    LetterNode(const LetterNode &other) : Node(other), m_letter(other.m_letter) {}

    ///
    /// \brief ~LetterNode The destructor.
    ///
    virtual ~LetterNode() {}

    /// \copydoc Node::letterNode
    virtual bool letterNode() const override { return true; }

    /// \copydoc Node::toString
    virtual std::wstring toString(bool, std::shared_ptr<atm::cache::AtmCache>) const override {
        std::wstring retVal = L"--->(";
        retVal += ((m_letter == L'\0' ? L'$' : m_letter));
        retVal.append(L")");
        return retVal;
    }

    /// \copydoc Node::letter
    virtual wchar_t letter() const override { return m_letter; }

  private:
    wchar_t m_letter;  //!< The letter that this node represents.
};
