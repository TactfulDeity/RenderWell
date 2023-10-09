#include "RenderWell/UnitTest/render_well_test_dirs.hpp"

#include "RenderWell/BackendManager.hpp"
#include "RenderWell/Types.hpp"
#include "RenderWell/DataBase.hpp"
#include "RenderWell/EBook.hpp"
#include "RenderWell/render_well_directories.hpp"

#include <catch2/catch.hpp>

#include <string>

using namespace RenderWell;

namespace
{
    const std::string k_TempName = "Temp";
}
    
TEST_CASE("TC23: Set Directory:", "[Settings]")
{
  BackendManager controller = BackendManager();
  controller.updateSettingWrapper(std::string(k_InputDirKey),
                                  std::string(UnitTest::k_TestFilesDir));

  REQUIRE(controller.getSetting(std::string(k_InputDirKey)) == std::string(UnitTest::k_TestFilesDir));

  controller.updateSettingWrapper(std::string(k_InputDirKey), "");

  REQUIRE(controller.getSetting(std::string(k_InputDirKey)).empty());
}