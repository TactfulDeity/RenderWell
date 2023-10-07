#include "DataBase.hpp"

#include "RenderWell/EBook.hpp"
#include "RenderWell/List.hpp"

using namespace RenderWell;

//-----------------------------------------------------------
// Object Modifiers
//-----------------------------------------------------------
DataBase::DataBase()
: m_Objects({})
{
  createList("Favorites");

  //Read in cached files
}

//-----------------------------------------------------------
// Member Functions
//-----------------------------------------------------------
bool DataBase::createList(std::string&& name, std::vector<unsigned long>&& books)
{
    auto listPtr = std::make_shared<List>();
    listPtr->m_UUID = m_NextUUID;
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

const DataObject* DataBase::getDataObject(unsigned long index)
{
    auto iterator = m_Objects.find(index);
    if(iterator == m_Objects.end())
    {
      return nullptr;
    }
    return iterator->second.get();
}

const DataObject& DataBase::getDataObjectRef(unsigned long index)
{
    const DataObject* object = getDataObject(index);
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

    m_Objects[m_NextUUID] = object;
    m_NextUUID++;
    return true;
}