#include "RenderWell/UnitTest/render_well_test_dirs.hpp"

#include "RenderWell/BackendManager.hpp"
#include "RenderWell/Types.hpp"
#include "RenderWell/DataBase.hpp"
#include "RenderWell/EBook.hpp"

#include <catch2/catch.hpp>

#include <string>

using namespace RenderWell;

TEST_CASE("TC10: Arrange eBooks A-Z:", "[Sorter]")
{
  {
    BackendManager controller = BackendManager();
    controller.updateSettingWrapper(std::string(k_InputDirKey),
                                    std::string(UnitTest::k_TestFilesDir));
  }

  BackendManager controller = BackendManager();
    
  std::vector<unsigned long> uuidList = controller.sort(k_AtoZ);

  DataBase& dataBase = controller.getDataBaseRef();

  std::string prevName = "";
  for(auto bookId : uuidList)
  {
    auto& book = dataBase.getDataObjectRefAs<EBook>(bookId);

    REQUIRE(book.m_Name < prevName);

    prevName = book.m_Name;
  }

  controller.updateSettingWrapper(std::string(k_InputDirKey), "");
}    
