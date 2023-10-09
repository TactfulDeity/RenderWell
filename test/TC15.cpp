#include "RenderWell/UnitTest/render_well_test_dirs.hpp"

#include "RenderWell/BackendManager.hpp"
#include "RenderWell/Types.hpp"
#include "RenderWell/DataBase.hpp"
#include "RenderWell/List.hpp"

#include <catch2/catch.hpp>

#include <string>

using namespace RenderWell;

TEST_CASE("TC15: Create New List for Ebook:", "[ListManager]")
{
  {
    BackendManager controller = BackendManager();
    controller.updateSettingWrapper(std::string(k_InputDirKey),
                                    std::string(UnitTest::k_TestFilesDir));
  }

  BackendManager controller = BackendManager();
  DataBase& dataBase = controller.getDataBaseRef();

  controller.createListWrapper("Temp");

  unsigned long listId = 0;
  for(auto id : dataBase.getListIds())
  {
    if(dataBase.getDataObjectAs<List>(id)->m_Name == "Temp")
    {
      listId = id;
    }
  }

  const List* newList = dataBase.getDataObjectAs<List>(listId);

  REQUIRE(newList != nullptr);

  controller.deleteListWrapper(listId);
}