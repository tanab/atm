#pragma once

#include <string>

/// \todo This configuration variables should be replaced with configuration manager.
const bool LOAD_FROM_FILE = true;
const std::string CACHE_TYPE = "REDUCE_THRU_DIACRITICS";


// General constants
const int MAX_SOURCES = 256;
const std::string DATA_PATH = "/tmp/";
const std::string PREFIX_TREE_FILE = "prefix_tree.dat";
const std::string SUFFIX_TREE_FILE = "suffix_tree.dat";
