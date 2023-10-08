#include "DataBase.hpp"

#include "RenderWell/EBook.hpp"
#include "RenderWell/List.hpp"

#include <poppler/cpp/poppler-document.h>

using namespace RenderWell;

//-----------------------------------------------------------
// Object Modifiers
//-----------------------------------------------------------
DataBase::DataBase(const fs::path& inputDirectory)
: m_Objects({})
{
  createList("Favorites");

  // Read in book files
  loadBooks(inputDirectory);
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
