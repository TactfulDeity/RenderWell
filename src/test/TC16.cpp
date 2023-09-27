TEST_CASE("TC16: Add Ebook To Existing List:, "[ListManager]")
{
    app.createNewList("Temp");
    const std::vector<unsigned long>* newList = app.getList("Temp");
    REQUIRE(newList!=nullptr);
    unsigned long uuid = newList->getId();
    app.addEBookToList(657,"path_to_exemplar_ebook",uuid);
    REQUIRE(st::find(newList.begin(), newList.end(),657)!= newList.end());
}