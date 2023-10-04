#pragma once

#include "DataObject.hpp"

#include <string>
#include <vector>

namespace RenderWell {
struct List : DataObject
{
    std::vector<unsigned long> m_Ebooks;
    std::string m_Name;
};
}