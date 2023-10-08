#pragma once

#include "RenderWell/DataObject.hpp"
#include "RenderWell/Types.hpp"

#include <chrono>
#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace RenderWell {
struct EBook : DataObject
{
  std::string m_Author;
  std::vector<unsigned long> m_Lists;
  fs::path m_Location;
  AccessTime m_LastRead;
  unsigned long m_PageNumber;
};
}