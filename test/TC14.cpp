#include "RenderWell/UnitTest/render_well_test_dirs.hpp"

#include "RenderWell/BackendManager.hpp"
#include "RenderWell/Types.hpp"
#include "RenderWell/DataBase.hpp"
#include "RenderWell/EBook.hpp"
#include "RenderWell/List.hpp"

#include <catch2/catch.hpp>

#include <string>

using namespace RenderWell;

TEST_CASE("TC14: Show Favorites:", "[Sorter]")
{
  {
    BackendManager controller = BackendManager();
    controller.updateSettingWrapper(std::string(k_InputDirKey),
                                    std::string(UnitTest::k_TestFilesDir));
  }

  BackendManager controller = BackendManager();
  DataBase& dataBase = controller.getDataBaseRef();

  controller.addWrapper(0, dataBase.getBookIds()[0]);
    
  std::vector<unsigned long> uuidList = controller.sort(k_Favorites);

  for(auto bookId : uuidList)
  {
    auto& book = dataBase.getDataObjectRefAs<EBook>(bookId);

    REQUIRE(book.m_Lists[0] == 0);
  }

  REQUIRE(dataBase.getDataObjectAs<List>(0)->m_Ebooks.size() == uuidList.size());
}    
