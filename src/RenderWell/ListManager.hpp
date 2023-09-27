#include <string>

namespace RenderWell
{
class ListManager
{
public:
    // Declare Constructor and Destructor
    ListManager();
    ~ListManager();

    // Declare copy and move constructors

    void rename(unsigned long id, std::string name);
    void add(unsigned long listId, unsigned long ebookId);
    void remove(unsigned long listId, unsigned long ebookId);
}
}