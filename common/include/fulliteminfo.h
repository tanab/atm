#pragma once

#include <minimaliteminfo.h>

class FullItemInfo : public MinimalItemInfo {
  public:
    //    FullItemInfo() : MinimalItemInfo(), m_sources(MAX_SOURCES) {}
    FullItemInfo() : MinimalItemInfo(), m_sources() {}

    virtual ~FullItemInfo() { m_sources.clear(); }

    ///
    /// \brief updateFrom Updates this instance with values from given \ref AffixCategoryRow
    /// \param row The row to take data from.
    ///
    void updateFrom(const atm::cache::AffixCategoryRow &row) {
        MinimalItemInfo::updateFrom(row);
        m_item_id = row.affix_id;
        m_sources.clear();
        m_sources = row.sources;
        m_lemma_id = row.lemma_id;
    }

    inline uint64_t itemId() const { return m_item_id; }

    inline void setItemId(uint64_t item_id) { m_item_id = item_id; }

    inline dbitvec sources() const { return m_sources; }

    inline dbitvec &sources() { return m_sources; }

    inline void setSources(const dbitvec &sources) { m_sources = sources; }

    inline std::wstring lemmaId() const { return m_lemma_id; }

    inline void setLemmaId(const std::wstring &lemma_id) { m_lemma_id = lemma_id; }

  private:
    uint64_t m_item_id;       //!< An item id.
    dbitvec m_sources;        //!< Sources flags.
    std::wstring m_lemma_id;  //!< The lemma id. Used only for stems.
};
