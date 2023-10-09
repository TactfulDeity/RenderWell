#include "RenderWell/UnitTest/render_well_test_dirs.hpp"

#include "RenderWell/BackendManager.hpp"
#include "RenderWell/Types.hpp"
#include "RenderWell/EBook.hpp"

#include <catch2/catch.hpp>

#include <string>

using namespace RenderWell;

TEST_CASE("TC03: Search eBooks:", "[BackendManager]")
{
  {
    BackendManager controller = BackendManager();
    controller.updateSettingWrapper(std::string(k_InputDirKey),
                                    std::string(UnitTest::k_TestFilesDir));
  }

  BackendManager controller = BackendManager();
    
  std::vector<unsigned long> uuidList = controller.search("a");

  controller.updateSettingWrapper(std::string(k_InputDirKey), "");

  REQUIRE(!uuidList.empty());
}
