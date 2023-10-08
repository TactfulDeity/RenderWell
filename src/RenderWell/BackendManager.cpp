#include "BackendManager.hpp"

#include "RenderWell/ListManager.hpp"
#include "RenderWell/Sorter.hpp"
#include "RenderWell/Types.hpp"

#include <stdexcept>

using namespace RenderWell;

BackendManager::BackendManager()
: m_Settings({})
, m_DataBase({})
{
  m_DataBase = DataBase(m_Settings.getValue(std::string(k_InputDirKey)));
}
BackendManager::~BackendManager() noexcept
{
  writeOut();
}

void BackendManager::removeWrapper(unsigned long listId, unsigned long bookId)
{
  // Wrapper function for creating temp ListManager to remove ebook from list
  ListManager(m_DataBase).remove(listId, bookId);
}

void BackendManager::addWrapper(unsigned long listId, unsigned long bookId)
{
  // Wrapper function for creating temp ListManager to add ebook to list
  ListManager(m_DataBase).add(listId, bookId);
}

void BackendManager::renameWrapper(unsigned long index, const std::string& name)
{
  // Wrapper function for creating temp ListManager to rename ebook or list
  ListManager(m_DataBase).rename(index, name);
}

void BackendManager::updateSettingWrapper(const std::string& key, const std::string& value)
{
  // Wrapper function for creating temp ListManager to add ebook to list
}

void BackendManager::reload()
{
  // add ebook the member variable m_EBooks
}

std::vector<unsigned long> BackendManager::sort(unsigned char sortKey)
{
  // create temp Sorter instance to sort List
  switch(sortKey)
  {
  case k_AtoZ:
  {
    return Sorter<SortAtoZ>(m_DataBase).operator()();
  }
  case k_ZtoA:
  {
    return Sorter<SortZtoA>(m_DataBase).operator()();
  }
  case k_Recent:
  {
    return Sorter<SortRecent>(m_DataBase).operator()();
  }
  case k_Favorites:
  {
    return Sorter<SortFavorites>(m_DataBase).operator()();
  }
  default:
  {
    throw std::runtime_error("Unhandled Sort type");
  }
  }
}

std::vector<unsigned long> BackendManager::search(const std::string& key)
{
  // searches m_EBooks for a matching title and returns uuid of EBook object
  const std::vector<unsigned long>& bookIds = m_DataBase.getBookIds();

  std::vector<unsigned long> foundIds = {};
  foundIds.reserve(bookIds.size());
  for(const auto id : bookIds)
  {
    if(m_DataBase.getDataObject(id)->m_Name.find(key) != std::string::npos)
    {
      foundIds.push_back(id);
    }
  }
  foundIds.shrink_to_fit();
  return foundIds;
}

void BackendManager::writeOut()
{
  // write state (all member variables to disk)
}
