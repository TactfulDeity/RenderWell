#pragma once

#include "RenderWell/render_well_export.hpp"

#include "RenderWell/DataBase.hpp"
#include "RenderWell/Settings.hpp"

#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace RenderWell
{
class RENDERWELL_EXPORT BackendManager
{
  //-----------------------------------------------------------
  // Object Modifiers
  //-----------------------------------------------------------
public:
  BackendManager();
  ~BackendManager() noexcept;

  BackendManager(const BackendManager& obj) = default;
  BackendManager(BackendManager&& obj) noexcept = default;

  BackendManager& operator=(const BackendManager& obj) = default;
  BackendManager& operator=(BackendManager&& obj) = default;

  //-----------------------------------------------------------
  // Member Functions
  //-----------------------------------------------------------
  void removeWrapper(unsigned long listId, unsigned long bookId);
  void addWrapper(unsigned long listId, unsigned long bookId);
  void renameWrapper(unsigned long index, const std::string& name);
  void updateSettingWrapper(const std::string& key, const std::string& value);
  std::vector<unsigned long> sort(unsigned char sortKey);
  std::vector<unsigned long> search(const std::string& key);
  fs::path renderPages(unsigned long bookId, int pageStart = -1, int renderCount = 30);

  //-----------------------------------------------------------
  // Private Member Variables
  //-----------------------------------------------------------
private:
  DataBase m_DataBase;
  Settings m_Settings;

  //-----------------------------------------------------------
  // Private Member Functions
  //-----------------------------------------------------------
  void writeOut();
  void reload();
};
}
