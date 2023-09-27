TEST_CASE("TC18: Add Ebook To Existing List:, "[ListManager]")
{
    app.createNewList("Temp");
    const std::vector<unsigned long>* newList = app.getList("Temp");
    REQUIRE(newList!=nullptr);
    unsigned long uuid = newList->getId();
    app.renameList(uuid,"NewTemp");
    REQUIRE(newList->getName() == "NewTemp");
}