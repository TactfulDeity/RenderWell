#include "RenderWell/BackendManager.hpp"
#include "RenderWell/Types.hpp"
#include "RenderWell/DataBase.hpp"
#include "RenderWell/EBook.hpp"

#include <string>

TEST_CASE("TC03: Search eBooks:", "[BackendManager]")
{
    BackendManager controller = BackendManager();
    
    std::vector<unsigned long> uuidList = controller.search("a");

    REQUIRE (uuidList.size() > 0); 
    
}  