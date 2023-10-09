#include "RenderWell/BackendManager.hpp"
#include "RenderWell/Types.hpp"
#include "RenderWell/DataBase.hpp"
#include "RenderWell/EBook.hpp"

namespace
{
    const std::string k_TempName = "Temp";
}
    
TEST_CASE("TC26: Clear Cache:", "[Settings]")
{
    BackendManager controller = BackendManager();

    controller.createNewList(::k_TempName);
    
    const std::vector<unsigned long>* newList = controller.getList(::k_TempName);
    
    REQUIRE(newList!=nullptr);
    
    const std::vector<unsigned long>* favList = controller.getFavoritesList();
    
    REQUIRE(favoritesList!=nullptr);
    
    controller.clearSettingsCache();
    
    controller.getNumList()== 0;
    
    REQUIRE(controller.favoritesList!=nullptr);
}