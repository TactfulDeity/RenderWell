namespace
{
    const std::string k_TempName = "Temp";
}
    
TEST_CASE("TC26: Clear Cache:, "[Settings]")
{
    app.createNewList(::k_TempName);
    const std::vector<unsigned long>* newList = app.getList(::k_TempName);
    REQUIRE(newList!=nullptr);
    const std::vector<unsigned long>* favList = app.getFavoritesList();
    REQUIRE(favoritesList!=nullptr);
    app.clearSettingsCache();
    app.getNumList()== 0;
    REQUIRE(app.favoritesList!=nullptr);
}