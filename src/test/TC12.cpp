#include "RenderWell/BackendManager.hpp"
#include "RenderWell/Types.hpp"
#include "RenderWell/DataBase.hpp"
#include "RenderWell/EBook.hpp"

#include <string>

TEST_CASE("TC12: Sort Most Recent:", "[Sorter]")
{
    BackendManager controller = BackendManager();
    
    std::vector<unsigned long> uuidList = controller.sort(k_Recent);

    DataBase& dataBase = controller.getDataBaseRef();

    RenderWell::AccessTime prevReadTime;

    for(auto bookId : uuidList)
    {
        auto& book = dataBase.getDataObjectRefAs<EBook>(bookId);

        REQUIRE(book.m_readTime < prevTime);
    }
    
}    
