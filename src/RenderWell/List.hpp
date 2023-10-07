#pragma once

#include "RenderWell/DataObject.hpp"

#include <vector>

namespace RenderWell {
struct List : DataObject
{
    std::vector<unsigned long> m_Ebooks;
};
}