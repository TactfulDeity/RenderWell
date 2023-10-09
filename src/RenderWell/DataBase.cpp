#include "DataBase.hpp"

#include "RenderWell/render_well_directories.hpp"

#include "RenderWell/EBook.hpp"
#include "RenderWell/List.hpp"

#include "RenderWell/json.hpp"
#include <poppler/cpp/poppler-document.h>

#include <algorithm>
#include <fstream>

using namespace RenderWell;

namespace
{
const std::string k_ListsFileName = "lists.json";
inline constexpr std::string_view k_FavoritesName = "Favorites";
}

//-----------------------------------------------------------
// Object Modifiers
//-----------------------------------------------------------
DataBase::DataBase(const fs::path& inputDirectory)
: m_Objects({})
{
  createList(std::string(k_FavoritesName));

  // Read in book files
  loadBooks(inputDirectory);

  // Load Lists
  loadLists();
}

//-----------------------------------------------------------
// Member Functions
//-----------------------------------------------------------
bool DataBase::createList(std::string&& name, std::vector<unsigned long>&& books)
{
    auto listPtr = std::make_shared<List>();
    listPtr->m_Ebooks = std::move(books);
    listPtr->m_Name = std::move(name);
    if(!this->insert(listPtr))
    {
      return false;
    }
    m_ListIds.push_back(m_NextUUID - 1);
    return true;
}

bool DataBase::deleteList(unsigned long listId)
{
    // Assumes object is a list and has already been cleared from EBooks
    std::vector<unsigned long> temp = {};
    temp.reserve(m_ListIds.size());
    for (auto index : m_ListIds) {
      if (index == listId) {
        continue;
      }
      temp.push_back(index);
    }
    m_ListIds = temp;

    m_Objects.erase(listId);
    writeListsToDisk();
    return true;
}

void DataBase::writeListsToDisk()
{
    using json = nlohmann::json;
    json listsCache = {};
    for(auto listId : m_ListIds)
    {
      auto& list = getDataObjectRefAs<List>(listId);

      std::vector<std::string> paths = {};
      paths.reserve(list.m_Ebooks.size());
      for(auto bookId : list.m_Ebooks)
      {
        paths.push_back(getDataObjectAs<EBook>(bookId)->m_Location.string());
      }

      listsCache[list.m_Name] = paths;
    }

    std::ofstream fout(k_DataFilesDir.string() + ::k_ListsFileName, std::ios_base::out | std::ios_base::binary);
    fout << listsCache;
}

//-----------------------------------------------------------
// Getters and Setters
//-----------------------------------------------------------
unsigned long DataBase::getLastUUID() const
{
    return m_NextUUID - 1;
}

const std::vector<unsigned long>& DataBase::getListIds() const
{
    return m_ListIds;
}

const std::vector<unsigned long>& DataBase::getBookIds() const
{
    return m_BookIds;
}

DataObject* DataBase::getDataObject(unsigned long index)
{
    auto iterator = m_Objects.find(index);
    if(iterator == m_Objects.end())
    {
      return nullptr;
    }
    return iterator->second.get();
}

DataObject& DataBase::getDataObjectRef(unsigned long index)
{
    DataObject* object = getDataObject(index);
    if(object == nullptr)
    {
      throw std::out_of_range("Index out of bounds!");
    }
    return *object;
}

const DataObject* DataBase::getDataObject(unsigned long index) const
{
    auto constIterator = m_Objects.find(index);
    if(constIterator == m_Objects.end())
    {
      return nullptr;
    }
    return constIterator->second.get();
}

const DataObject& DataBase::getDataObjectRef(unsigned long index) const
{
    const DataObject* object = getDataObject(index);
    if(object == nullptr)
    {
      throw std::out_of_range("Index out of bounds!");
    }
    return *object;
}

//-----------------------------------------------------------
// Private Member Functions
//-----------------------------------------------------------
bool DataBase::insert(const std::shared_ptr<DataObject>& object)
{
    if(object == nullptr)
    {
      return false;
    }

    object->m_UUID = m_NextUUID;
    m_Objects[m_NextUUID] = object;
    m_NextUUID++;
    return true;
}

void DataBase::loadBooks(const fs::path& inputDirectory)
{
    if(!exists(inputDirectory))
    {
      return;
    }

    for(const auto& entry : fs::directory_iterator(inputDirectory))
    {
      const auto filenameStr = entry.path().filename().string();
      if (entry.is_directory()) {
        continue;
      }
      else if (entry.is_regular_file()) {
        if(entry.path().extension() == ".pdf")
        {
          // Create EBook
          auto book = std::make_shared<EBook>();
          book->m_LastRead = std::chrono::steady_clock::now();

          // Load document from path
          std::unique_ptr<poppler::document> doc(poppler::document::load_from_file(entry.path()));
          if (!doc) {
            throw std::runtime_error("loading error");
          }
          if (doc->is_locked()) {
            throw std::runtime_error ("encrypted document");
          }

          // Fill in EBook
          book->m_Name = doc->get_title().to_latin1();
          book->m_Author = doc->get_author().to_latin1();
          book->m_PageNumber = 0;
          book->m_Location = entry.path();

          insert(book);
        }
      }
    }
}

void DataBase::loadLists()
{
    if(exists(fs::path(k_DataFilesDir.string() + ::k_ListsFileName)))
    {
      return;
    }

    using json = nlohmann::json;
    json listsCache = {};

    std::ifstream fin(k_DataFilesDir.string() + ::k_ListsFileName, std::ios_base::in | std::ios_base::binary);
    fin >> listsCache;
    for(auto& [key, value] : listsCache.items())
    {
      std::vector<unsigned long> foundBookIds = {};
      for(auto iter = value.begin(); iter != value.end(); iter++)
      {
        for(auto id : m_BookIds)
        {
          if(iter.value() == getDataObjectAs<EBook>(id)->m_Location.string())
          {
            foundBookIds.push_back(getDataObject(id)->m_UUID);
            break;
          }
        }
      }

      if(key == k_FavoritesName)
      {
        getDataObjectAs<List>(k_FavoritesId)->m_Ebooks = foundBookIds;
      }
      else
      {
        std::string name = key;
        createList(std::move(name), std::move(foundBookIds));
      }
    }
}
