#pragma once

#include "DataObject.hpp"

#include <string>
#include <vector>

namespace RenderWell {
struct Ebook : DataObject
{
    std::string m_Title;
    std::string m_Author;
    std::vector<unsigned long> m_Lists;
    std::path m_Location;
};
}