#include "RenderWell/BackendManager.hpp"
#include "RenderWell/Types.hpp"
#include "RenderWell/DataBase.hpp"
#include "RenderWell/EBook.hpp"

#include <string>

TEST_CASE("TC14: Show Favorites:", "[Sorter]")
{
    BackendManager controller = BackendManager();
    
    std::vector<unsigned long> uuidList = controller.sort(k_Favorites);

    DataBase& dataBase = controller.getDataBaseRef();

    for(auto bookId : uuidList)
    {
        auto& book = dataBase.getDataObjectRefAs<EBook>(bookId);

        REQUIRE(book.m_uuid == 0);
    }

    REQUIRE(dataBase.getDataObjectAs<List>(0)->m_EBooks.size() == uuidList.size());
}    
