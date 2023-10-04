#include "DataBase.hpp"

#include "Ebook.hpp"
#include "List.hpp"

using namespace RenderWell;

DataBase::DataBase()
: m_Lists(std::make_pair("Favorites", {}))
: m_EBooks({{}})
{
    //Read in cached files
}

unsigned long DataBase::createList(const std::string& name)
{
    List list;
    list.m_UUID = m_NextUUID + 1;
    list.m_Ebooks = {};
    list.m_Name = std::move(name);
    m_Objects.emplace(m_NextUUID + 1, std::move(list));

    return m_NextUUID++;
}

unsigned long DataBase::createList(const std::string& name, const std::vector<unsigned long>& books)
{
    List list;
    list.m_UUID = m_NextUUID + 1;
    list.m_Ebooks = std::move(books);
    list.m_Name = std::move(name);
    m_Objects.emplace(m_NextUUID + 1, std::move(list));

    return m_NextUUID++;
}
