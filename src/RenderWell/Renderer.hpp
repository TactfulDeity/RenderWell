
namespace RenderWell
{
class Renderer
{
public:
    // Declare Constructor and Destructor
    Renderer();
    ~Renderer();

    // Declare copy and move constructors

    void render(path);

private: 
    unsigned long m_PageNumber;
}
}