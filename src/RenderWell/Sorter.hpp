#pragma once

#include "DataBase.hpp"
#include "Types.hpp"

namespace RenderWell {
template<typename Sort = UsingFavorites>
class Sorter
{
public:
    Sorter(const DataBase& dataBase)
    : m_DataBase(dataBase)
    {
    }
    ~Sorter() noexcept = default;

    Sorter(const Sorter& obj) = delete;
    Sorter(Sorter&& obj) noexcept = delete;

    Sorter& operator=(const Sorter& obj) = delete;
    Sorter& operator=(Sorter&& obj) = delete;

    std::vector<unsigned long> operator()()
    {
        std::vector<unsigned long> ordering;

        // queries library list and sorts according to SortType
        if constexpr(Sort::UsingAtoZ)
        {

        }
        if constexpr(Sort::UsingZtoA)
        {

        }
        if constexpr(Sort::UsingRecent)
        {

        }
        if constexpr(Sort::UsingFavorites)
        {
            ordering =
        }

        // returns a vector of the sorted id list
        return ordering;
    }

private:
    const DataBase& m_DataBase;
    constexpr unsigned long k_FavoritesUUID = 0;
};
}