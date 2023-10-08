#pragma once

#include "RenderWell/render_well_export.hpp"

#include "RenderWell/DataObject.hpp"

#include <vector>

namespace RenderWell {
struct RENDERWELL_EXPORT List : DataObject
{
  std::vector<unsigned long> m_Ebooks;
};
}