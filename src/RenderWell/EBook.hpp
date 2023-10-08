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
  AccessTime m_LastRead;
  fs::path m_Location;
  int m_PageNumber;
};
}