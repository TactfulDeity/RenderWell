#include "RenderWell/UnitTest/render_well_test_dirs.hpp"

#include "RenderWell/BackendManager.hpp"
#include "RenderWell/Types.hpp"
#include "RenderWell/DataBase.hpp"
#include "RenderWell/List.hpp"

#include <catch2/catch.hpp>

#include <string>

using namespace RenderWell;

TEST_CASE("TC16: Add Ebook To Existing List:", "[ListManager]")
{
  {
    BackendManager controller = BackendManager();
    controller.updateSettingWrapper(std::string(k_InputDirKey),
                                    std::string(UnitTest::k_TestFilesDir));
  }
  BackendManager controller = BackendManager();
  DataBase& dataBase = controller.getDataBaseRef();

  controller.addWrapper(0, dataBase.getBookIds()[0]);

  const std::vector<unsigned long>& favList = dataBase.getDataObjectRefAs<List>(0).m_Ebooks;

  REQUIRE(std::find(favList.begin(), favList.end(), dataBase.getBookIds()[0]) != favList.end());

  controller.updateSettingWrapper(std::string(k_InputDirKey), "");
}