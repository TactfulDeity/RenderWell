#pragma once

#include <string>

namespace RenderWell
{
struct DataObject
{
  DataObject() = default;
  virtual ~DataObject() = default;
  unsigned long m_UUID;
  std::string m_Name;
};
}
