#include "RenderWell/BackendManager.hpp"
#include "RenderWell/Types.hpp"
#include "RenderWell/DataBase.hpp"
#include "RenderWell/EBook.hpp"

TEST_CASE("TC19: Delete eBook List:", "[ListManager]")
{
    BackendManager controller = BackendManager();

    controller.createNewList("Temp");
    
    const std::vector<unsigned long>* newList = controller.getList("Temp");
    
    REQUIRE(newList!=nullptr);
    
    unsigned long uuid = newList->getId();
    
    controller.deleteList(uuid);
    
    REQUIRE(controller.getList(uuid) == nullptr);
}