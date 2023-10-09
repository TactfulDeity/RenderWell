#include "RenderWell/BackendManager.hpp"
#include "RenderWell/Types.hpp"
#include "RenderWell/DataBase.hpp"
#include "RenderWell/EBook.hpp"

TEST_CASE("TC18: Renaming an Existing List:", "[ListManager]")
{
    BackendManager controller = BackendManager();

    
    controller.createNewList("Temp");
    
    const std::vector<unsigned long>* newList = controller.getList("Temp");
    
    REQUIRE(newList!=nullptr);
    
    unsigned long uuid = newList->getId();
    
    controller.renameList(uuid,"NewTemp");
    
    REQUIRE(newList->getName() == "NewTemp");
}