#pragma once

#include "RenderWell/render_well_export.hpp"

#include <string>

namespace RenderWell
{
struct RENDERWELL_EXPORT DataObject
{
  DataObject() = default;
  virtual ~DataObject() = default;
  unsigned long m_UUID;
  std::string m_Name;
};
}
