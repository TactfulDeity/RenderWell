#include "RenderWell/BackendManager.hpp"
#include "RenderWell/Types.hpp"
#include "RenderWell/DataBase.hpp"
#include "RenderWell/EBook.hpp"

TEST_CASE("TC15: Create New List for Ebook:", "[ListManager]")
{
    BackendManager controller = BackendManager();

    controller.createNewList("Temp");
    
    const std::vector<unsigned long>* newList = controller.getList("Temp");
    
    REQUIRE(newList !=nullptr);
}