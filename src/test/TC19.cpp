TEST_CASE("TC19: Delete eBook List:, "[ListManager]")
{
    app.createNewList("Temp");
    const std::vector<unsigned long>* newList = app.getList("Temp");
    REQUIRE(newList!=nullptr);
    unsigned long uuid = newList->getId();
    app.deleteList(uuid);
    REQUIRE(app.getList(uuid) == nullptr);
}