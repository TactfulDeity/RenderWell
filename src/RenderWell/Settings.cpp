#include "Settings.hpp"

#include "RenderWell/render_well_directories.hpp"

#include <fstream>
#include <stdexcept>

using namespace RenderWell;

namespace
{
const std::string k_SettingsFileName = "settings.json";
}

Settings::Settings()
: m_Location(k_SysFilesDir.string() + ::k_SettingsFileName)
, m_Json({})
{
  std::ifstream fin (m_Location);
  if(!fin.is_open())
  {
    throw std::runtime_error("Unable to create settings file");
  }
  fin >> m_Json;
}

bool Settings::updateSetting(const std::string& key, const std::string& updateValue)
{
  // update the in memory settings map
  m_Json[key] = updateValue;

  // write the update value to the corresponding slot in the settings.json file
  return writeSettingsToDisk();
}

bool Settings::writeSettingsToDisk()
{
  // write the update value to the corresponding slot in the settings.json file
  std::ofstream fout(m_Location, std::ios_base::out | std::ios_base::binary);
  if(!fout.is_open())
  {
    throw std::runtime_error("Unable to load settings file");
  }

  fout << m_Json;

  return true;
}

std::string Settings::getValue(const std::string& key) const
{
  auto iter = m_Json.find(key);
  if(iter == m_Json.end())
  {
    return "";
  }

  return iter.value();
}

void Settings::clearTempDirectory()
{
  fs::remove_all(k_TempFilesDir);
}