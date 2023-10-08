#include "ListManager.hpp"

#include "RenderWell/DataObject.hpp"
#include "RenderWell/EBook.hpp"
#include "RenderWell/List.hpp"

using namespace RenderWell;

ListManager::ListManager(DataBase& dataBase)
: m_DataBase(dataBase)
{
}

void ListManager::rename(unsigned long id, const std::string& name)
{
  // rename respective object
  m_DataBase.getDataObject(id)->m_Name = name;
}

void ListManager::add(unsigned long listId, unsigned long ebookId)
{
  // add listId from the EBook (defined by ebookId) member variable m_Lists
  m_DataBase.getDataObjectAs<EBook>(ebookId)->m_Lists.push_back(listId);

  // add ebookId from the List (defined by listId) member variable m_EBook
  m_DataBase.getDataObjectAs<List>(listId)->m_Ebooks.push_back(ebookId);
}

void ListManager::remove(unsigned long listId, unsigned long ebookId)
{
  // remove listId from the EBook (defined by ebookId) member variable m_Lists
  {
    auto &book = m_DataBase.getDataObjectRefAs<EBook>(ebookId);

    std::vector<unsigned long> temp = {};
    temp.reserve(book.m_Lists.size());
    for (auto index : book.m_Lists) {
      if (index == listId) {
        continue;
      }
      temp.push_back(index);
    }
    book.m_Lists = temp;
  }

  // remove ebookId from the List (defined by listId) member variable m_EBook
  {
    auto &list = m_DataBase.getDataObjectRefAs<List>(ebookId);

    std::vector<unsigned long> temp = {};
    temp.reserve(list.m_Ebooks.size());
    for (auto index : list.m_Ebooks) {
      if (index == listId) {
        continue;
      }
      temp.push_back(index);
    }
    list.m_Ebooks = temp;
  }
}

void ListManager::removeListFromAll(unsigned long listId)
{
  const std::vector<unsigned long>& bookList = m_DataBase.getDataObjectAs<List>(listId)->m_Ebooks;

  for(auto id : bookList)
  {
    auto &book = m_DataBase.getDataObjectRefAs<EBook>(id);

    std::vector<unsigned long> temp = {};
    temp.reserve(book.m_Lists.size());
    for (auto index : book.m_Lists) {
      if (index == listId) {
        continue;
      }
      temp.push_back(index);
    }
    book.m_Lists = temp;
  }
}