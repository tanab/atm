#pragma once

#include <list>
#include <map>
#include <memory>
#include <minimaliteminfo.h>
#include <multiplyparams.h>
#include <resultnode.h>
#include <tree.h>
#include <triplet.h>
#include <types.h>
#include <vector>

namespace atm {
namespace core {

///
/// \brief The TreeSearch class implements the structure and functions used for affix matching.
///
class TreeSearch {
  public:
    /// \brief The constructor of the class.
    ///
    /// \param type Specifies type of the solution required, can be prefix or suffix.
    /// \param text The input text.
    /// \param start The starting index.
    /// \param reduce_thru_diacritics Specifies whether solution reduced using diacritics is
    /// required or not.
    explicit TreeSearch(const ItemTypes &type, const std::wstring &text,
                        std::wstring::size_type start, bool reduce_thru_diacritics = true);

    /// \brief The destructor.
    virtual ~TreeSearch();

  private:
    bool m_reduce_thru_diacritics; //!< Is solution reducet using diacritics required or not.
    bool m_details_filled;    //!< \todo Find od what is this. Original name is filled_details.
    MultiplyParams m_params;  //!< Settings for the final result.
    std::list<int> m_sub_positions_of_current_match;  //!< End of the last split.
    AffixSolutionVector m_affix_info;        //!< Vector containing the affix solutions found.
    std::list<ResultNode *> m_result_nodes;  //!< List of found result nodes as affix solution.
    ///
    /// \brief m_map Hashmap that takes id/category/raw data and returns abstract/descriptin/part of
    /// speech of an affix solution.
    ///
    ItemCategoryRaw2AbsDescPosMap m_map;

    int64_t m_resulting_category_id_of_current_match;  //!< Category id of the current affix match.

    std::list<std::list<RawData>> m_possible_raw_data_of_current_match;

    std::shared_ptr<atm::common::Tree> m_tree;
};
}
}
