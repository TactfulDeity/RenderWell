#include "RenderWell/UnitTest/render_well_test_dirs.hpp"

#include "RenderWell/BackendManager.hpp"
#include "RenderWell/Types.hpp"
#include "RenderWell/DataBase.hpp"
#include "RenderWell/EBook.hpp"

#include <catch2/catch.hpp>

#include <chrono>
#include <string>

using namespace RenderWell;

TEST_CASE("TC12: Sort Most Recent:", "[Sorter]")
{
  {
    BackendManager controller = BackendManager();
    controller.updateSettingWrapper(std::string(k_InputDirKey),
                                    std::string(UnitTest::k_TestFilesDir));
  }

  BackendManager controller = BackendManager();
    
  std::vector<unsigned long> uuidList = controller.sort(k_Recent);

  DataBase& dataBase = controller.getDataBaseRef();

  AccessTime prevReadTime = static_cast<AccessTime >(std::chrono::steady_clock::now() - std::chrono::steady_clock::now());
  for(auto bookId : uuidList)
  {
    auto& book = dataBase.getDataObjectRefAs<EBook>(bookId);

    REQUIRE(book.m_LastRead < prevReadTime);

    prevReadTime = book.m_LastRead;
  }

  controller.updateSettingWrapper(std::string(k_InputDirKey), "");
}    
