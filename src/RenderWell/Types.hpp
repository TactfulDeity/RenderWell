#pragma once

#include <chrono>

namespace RenderWell
{
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