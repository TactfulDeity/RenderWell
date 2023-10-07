#pragma once

#include "RenderWell/DataObject.hpp"

#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace RenderWell
{
class DataBase
{
  //-----------------------------------------------------------
  // static Member Constants
  //-----------------------------------------------------------
public:
  static constexpr unsigned long k_FavoritesId = 0;

  //-----------------------------------------------------------
  // Object Modifiers
  //-----------------------------------------------------------
  DataBase();
  ~DataBase() noexcept = default;

  DataBase(const DataBase& obj) = default;
  DataBase(DataBase&& obj) noexcept = default;

  DataBase& operator=(const DataBase& obj) = default;
  DataBase& operator=(DataBase&& obj) = default;

  //-----------------------------------------------------------
  // Member Functions
  //-----------------------------------------------------------
  bool createList(std::string&& name, std::vector<unsigned long>&& books = {});

  //-----------------------------------------------------------
  // Getters and Setters
  //-----------------------------------------------------------
  [[nodiscard]] unsigned long getLastUUID() const;
  [[nodiscard]] const std::vector<unsigned long>& getListIds() const;
  [[nodiscard]] const std::vector<unsigned long>& getBookIds() const;

  [[nodiscard]] const DataObject* getDataObject(unsigned long index);
  [[nodiscard]] const DataObject& getDataObjectRef(unsigned long index);
  [[nodiscard]] const DataObject* getDataObject(unsigned long index) const;
  [[nodiscard]] const DataObject& getDataObjectRef(unsigned long index) const;

  template <class T, class = std::enable_if_t<std::is_base_of_v<DataObject, T>>>
  T* getDataObjectAs(unsigned long index)
  {
    return dynamic_cast<T*>(getDataObject(index));
  }

  template <class T, class = std::enable_if_t<std::is_base_of_v<DataObject, T>>>
  T& getDataObjectRefAs(unsigned long index)
  {
    return dynamic_cast<T&>(getDataObjectRef(index));
  }

  template <class T, class = std::enable_if_t<std::is_base_of_v<DataObject, T>>>
  const T* getDataObjectAs(unsigned long index) const
  {
    return dynamic_cast<const T*>(getDataObject(index));
  }

  template <class T, class = std::enable_if_t<std::is_base_of_v<DataObject, T>>>
  const T& getDataObjectRefAs(unsigned long index) const
  {
    return dynamic_cast<const T&>(getDataObjectRef(index));
  }

  //-----------------------------------------------------------
  // Private Member Variables
  //-----------------------------------------------------------
private:
  std::map<unsigned long, std::shared_ptr<DataObject>> m_Objects;
  unsigned long m_NextUUID = 0;
  std::vector<unsigned long> m_BookIds = {};
  std::vector<unsigned long> m_ListIds = {};

  //-----------------------------------------------------------
  // Private Member Functions
  //-----------------------------------------------------------
  bool insert(const std::shared_ptr<DataObject>& object);
};
}
