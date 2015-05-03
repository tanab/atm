#pragma once

#include <vector>
#include <multiplyparams.h>
#include <minimaliteminfo.h>
#include <enums.h>

class Stemmer {
  private:
    MultiplyParams m_multiply_params;  //!< Holds settings that specify the details of the solution.
    ItemTypes m_type;    //!< The type of data to be extracted. Prefix, stem or suffix.
    bool m_all_details;  //!< Indicates whether a detailed solution if the input is required or not.
    bool m_call_everything;  //!< Idicates whether all machines are to be called based on user inpu.

    /// Vector containing the final result of prefixes of a word and their details based on a single
    /// interpretation of the input word.
    std::vector<MinimalItemInfo> m_prefix_infos;
    /// Contans the stem info for a corresponding interpretation of the input word.
    MinimalItemInfo m_stem_info;
    /// Vector containing the final result of suffexes of a word and their details base on a single
    /// interpretation of the input word.
    std::vector<MinimalItemInfo> m_suffix_infos;

};
