#pragma once

#include "RenderWell/DataBase.hpp"
#include "RenderWell/EBook.hpp"
#include "RenderWell/List.hpp"
#include "RenderWell/Types.hpp"

#include <map>

namespace RenderWell {
template<typename Sort = SortFavorites>
class Sorter
{
public:
  explicit Sorter(const DataBase& dataBase)
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
    if constexpr(Sort::UsingFavorites)
    {
      // Grab favorites list directly
      return m_DataBase.getDataObjectRefAs<List>(RenderWell::DataBase::k_FavoritesId).m_Ebooks;
    }
    else {
      std::vector<unsigned long> ordering;

      // queries library list and sorts according to SortType
      if constexpr (Sort::UsingRecent) {
        // Load last access times from the DataBase into an ordered map to utilize BST
        std::vector<unsigned long> bookIds = m_DataBase.getBookIds();
        std::map<AccessTime, unsigned long> accessList = {};
        for (auto index : bookIds) {
          accessList.emplace(
              m_DataBase.getDataObjectAs<EBook>(index)->m_LastRead, index);
        }

        // Copy newly ordered ids into ordering
        ordering.reserve(accessList.size());
        for (const auto &[key, value] : accessList) {
          ordering.push_back(value);
        }
      }
      else
      {
        // Load strings from the DataBase into an ordered map to utilize BST
        std::vector<unsigned long> bookIds = m_DataBase.getBookIds();
        std::map<AccessTime, unsigned long> orderedList = {};
        for (auto index : bookIds) {
          orderedList.emplace(
              // Avoid dynamic cast since all DataObjects have a Name
              m_DataBase.getDataObject(index)->m_Name, index);
        }


        // Copy newly ordered ids into ordering
        ordering.reserve(orderedList.size());
        if constexpr (Sort::UsingAtoZ)
        {
          for (const auto &[key, value] : orderedList) {
            ordering.push_back(value);
          }
        }
        if constexpr (Sort::UsingZtoA)
        {
          for(auto revIt = orderedList.rbegin(); revIt != orderedList.rend(); revIt++)
          {
            ordering.push_back(revIt->second);
          }
        }
      }

      // returns a vector of the sorted id list
      return ordering;
    }
  }

private:
  const DataBase& m_DataBase;
};
}