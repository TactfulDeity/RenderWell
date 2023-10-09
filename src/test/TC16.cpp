#include "RenderWell/BackendManager.hpp"
#include "RenderWell/Types.hpp"
#include "RenderWell/DataBase.hpp"
#include "RenderWell/EBook.hpp"

TEST_CASE("TC16: Add Ebook To Existing List:", "[ListManager]")
{
    BackendManager controller = BackendManager();

    
    controller.createNewList("Temp");
    
    const std::vector<unsigned long>* newList = controller.getList("Temp");
    
    REQUIRE(newList!=nullptr);
    
    unsigned long uuid = newList->getId();
    
    controller.addEBookToList(657,"path_to_exemplar_ebook",uuid);
    
    REQUIRE(st::find(newList.begin(), newList.end(),657)!= newList.end());
}