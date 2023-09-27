TEST_CASE("TC13: Add EBook To Favorites:, "[ListManager]")
{
    const std::vector<unsigned long>& favList = app.getFavoritesList();
    app.addEBookToFavorites(1098, "path_to_exemplar_ebook");
    REQUIRE(std::find(favList.begin(), favList.end(), 1098) != favList.end()); (edited)
}