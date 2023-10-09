#include "RenderWell/BackendManager.hpp"
#include "RenderWell/Types.hpp"
#include "RenderWell/DataBase.hpp"
#include "RenderWell/EBook.hpp"

TEST_CASE("TC13: Add EBook To Favorites:", "[ListManager]")
{
    BackendManager controller = BackendManager();

    const std::vector<unsigned long>& favList = controller.getFavoritesList();

    controller.addEBookToFavorites(1098, "path_to_exemplar_ebook");

    REQUIRE(std::find(favList.begin(), favList.end(), 1098) != favList.end()); (edited)
}