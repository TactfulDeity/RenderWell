#pragma once

#include "RenderWell/DataBase.hpp"

#include <string>

namespace RenderWell
{
class ListManager
{
public:
  // Declare Constructor and Destructor
  explicit ListManager(DataBase& dataBase);
  ~ListManager() noexcept = default;

  // Declare copy and move constructors
  ListManager(const ListManager& obj) = delete;
  ListManager(ListManager&& obj) noexcept = delete;
    
  ListManager& operator=(const ListManager& obj) = delete;
  ListManager& operator=(ListManager&& obj) = delete;

  void rename(unsigned long id, const std::string& name);
  void add(unsigned long listId, unsigned long ebookId);
  void remove(unsigned long listId, unsigned long ebookId);

private:
  DataBase& m_DataBase;
};
}