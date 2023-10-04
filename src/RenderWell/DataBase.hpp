#pragma once

#include "DataObject.hpp"

#include <map>
#include <string>
#include <vector>

namespace RenderWell
{
class DataBase
{
    DataBase();
    ~DataBase() noexcept = default;

    DataBase(const DataBase& obj) = default;
    DataBase(DataBase&& obj) noexcept = default;

    DataBase& operator=(const DataBase& obj) = default;
    DataBase& operator=(DataBase&& obj) = default;

    unsigned long createList(const std::string& name);
    unsigned long createList(const std::string& name, const std::vector<unsigned long>& books);



private:
    std::map<unsigned long, DataObject> m_Objects;
    unsigned long m_NextUUID = 0;
};
}
