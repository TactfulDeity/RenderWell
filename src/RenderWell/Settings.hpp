#pragma once

#include "RenderWell/json.hpp"

#include <filesystem>
#include <map>
#include <string>

namespace fs = std::filesystem;

namespace RenderWell {
class Settings {
  using json = nlohmann::json;
public:
  Settings();
  ~Settings() noexcept = default;
  
  Settings(const Settings& obj) = default;
  Settings(Settings&& obj) noexcept = default;

  Settings& operator=(const Settings& obj) = default;
  Settings& operator=(Settings&& obj) = default;

  bool updateSetting(const std::string& key, const std::string& updateValue);
  
  [[nodiscard]] std::string getValue(const std::string& key) const;

  static void clearTempDirectory();

private:
  std::filesystem::path m_Location;
  json m_Json;
};
}
