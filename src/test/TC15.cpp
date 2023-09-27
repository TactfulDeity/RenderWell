TEST_CASE("TC15: Create New List for Ebook:, "[ListManager]")
{
    app.createNewList("Temp");
    const std::vector<unsigned long>* newList = app.getList("Temp");
    REQUIRE(newList !=nullptr);
}