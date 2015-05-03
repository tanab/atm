#pragma once

#include <vector>
#include <map>
#include <triplet.h>
#include <minimaliteminfo.h>

class Node;

using AffixSolutionVector = std::vector<MinimalItemInfo>;

using ItemEntryKey = Triplet<int64_t, int64_t, std::wstring>;
using ItemEntryInfo = Triplet<dbitvec, int64_t, std::wstring>;
using ItemCategoryRaw2AbsDescPosMap = std::multimap<ItemEntryKey, ItemEntryInfo>;

// Used by tree class
using IdMap = std::map<Node *, int>;
using ReverseIdMap = std::map<Node *, int>;
