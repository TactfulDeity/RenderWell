#pragma once

#include "RenderWell/render_well_export.hpp"

#include <chrono>

namespace RenderWell
{
RENDERWELL_EXPORT inline constexpr unsigned char k_AtoZ = 1;
RENDERWELL_EXPORT inline constexpr unsigned char k_ZtoA = 2;
RENDERWELL_EXPORT inline constexpr unsigned char k_Recent = 3;
RENDERWELL_EXPORT inline constexpr unsigned char k_Favorites = 4;

RENDERWELL_EXPORT inline constexpr std::string_view k_InputDirKey = "LibraryDir";

using AccessTime = std::chrono::steady_clock::time_point;

template<bool UseAtoZ, bool UseZtoA, bool UseRecent, bool UseFavorites>
struct Sort
{
    static inline constexpr bool UsingAtoZ = UseAtoZ;
    static inline constexpr bool UsingZtoA = UseZtoA;
    static inline constexpr bool UsingRecent = UseRecent;
    static inline constexpr bool UsingFavorites = UseFavorites;
};

using SortAtoZ = Sort<true, false, false, false>;
using SortZtoA = Sort<false, true, false, false>;
using SortRecent = Sort<false, false, true, false>;
using SortFavorites = Sort<false, false, false, true>;
}