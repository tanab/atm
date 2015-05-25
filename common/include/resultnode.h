#pragma once

#include <list>
#include <rawdata.h>
#include <node.h>

class ResultNode : public Node {
  public:
    ///
    /// \brief ResultNode The constructor.
    /// \param affix_id The affix id.
    /// \param previous_category_id The previous category id.
    /// \param resulting_category_id The resulting category id.
    /// \param accepts_state Whether to accept state.
    /// \param original_string The original string.
    /// \param inflected_string The inflected string.
    /// \param inflection_rule The inflection rule.
    ///
    explicit ResultNode(uint64_t affix_id, uint64_t previous_category_id,
                        uint64_t resulting_category_id, bool accepts_state,
                        const std::wstring& original_string, const std::wstring& inflected_string,
                        const std::wstring& inflection_rule);

    ///
    /// \brief ResultNode The copy constructor.
    /// \param other The node to copy from.
    ///
    ResultNode(const ResultNode& other);

    ///
    /// \brief ~ResultNode The destructor.
    ///
    virtual ~ResultNode();

    ///
    /// \brief operator = The assignment operator.
    /// \param other The node to copy from.
    /// \return Updated node.
    ///
    ResultNode& operator=(const ResultNode& other);

    /// \copydoc Node::letterNode
    virtual bool letterNode() const override;

    /// \copydoc Node::letter
    virtual wchar_t letter() const override;

    /// \copydoc Node::toString
    virtual std::wstring toString(
        bool affix = true, std::shared_ptr<atm::cache::AtmCache> cache = nullptr) const override;

    ///
    /// \brief addRawData Adds another raw data item if such doesn't already exist.
    /// \param original_string The original string.
    /// \param inflected_string The inflected string.
    ///
    void addRawData(const std::wstring& original_string, const std::wstring& inflected_string);

    ///
    /// \brief previousResultNode returns previous result node by looking up the hierarchy.
    /// \return previous result node or \code nullptr if such does not exist.
    ///
    ResultNode* previousResultNode() const;

    inline void setPreviousCategoryId(int64_t previous_category_id) {
        m_previous_category_id = previous_category_id;
    }

    inline uint64_t previousCategoryId() const { return m_previous_category_id; }

    inline void setAffixId(uint64_t affix_id) { m_affix_id = affix_id; }

    inline uint64_t affixId() const { return m_affix_id; }

    inline void setResultingCategoryId(uint64_t resulting_category_id) {
        m_resulting_category_id = resulting_category_id;
    }

    inline uint64_t resultingCategoryId() const { return m_resulting_category_id; }

    inline void setAcceptsState(bool accepts_state) { m_accepts_state = accepts_state; }

    inline bool acceptsState() const { return m_accepts_state; }

    inline void setInflectionRule(const std::wstring& inflection_rule) {
        m_inflection_rule = inflection_rule;
    }

    inline const std::wstring& inflectionRule() const { return m_inflection_rule; }

    inline const std::list<RawData>& rawData() const { return m_raw_data; }

  private:
    uint64_t m_previous_category_id;   //!< The previous category id.
    uint64_t m_affix_id;               //!< The affix id.
    uint64_t m_resulting_category_id;  //!< The resulting category id;
    bool m_accepts_state;              //!< Whether to accept state.
    std::wstring m_inflection_rule;    //!< The inflection rule.
    std::list<RawData> m_raw_data;     //!< The raw data.
};
