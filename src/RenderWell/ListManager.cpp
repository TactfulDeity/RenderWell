


using namespace RenderWell;

class ListManager
{
public:
    ListManager::ListManager()
    {
    }
    ListManager::~ListManager()
    {
    }

    void ListManager::rename(unsigned long id, std::string name)
    {
        // Determines whether it is an ebook or list by searching Ids

        // rename respective object

        // write out updates to the Library.json and List.json (if applicable)
    } 

    void ListManager::add(unsigned long listId, unsigned long ebookId)
    {
        // add listId from the EBook (defined by ebookId) member variable m_Lists

        // add ebookId from the List (defined by listId) member variable m_EBook

        // write out updates to the Library.json and List.json
    }

    void ListManager::remove(unsigned long listId, unsigned long ebookId)
    {
        // remove listId from the EBook (defined by ebookId) member variable m_Lists

        // remove ebookId from the List (defined by listId) member variable m_EBook

        // write out updates to the Library.json and List.json
    }
}
