#pragma once

#include "RenderWell/DataBase.hpp"
#include "RenderWell/EBook.hpp"

#include <poppler/cpp/poppler-document.h>

#include <filesystem>

namespace fs = std::filesystem;

namespace RenderWell
{
class Renderer
{
public:
    // Declare Constructor and Destructor
    Renderer(DataBase& dataBase, unsigned long index);
    ~Renderer();

    // Declare copy and move constructors
    Renderer(const Renderer& obj) = delete;
    Renderer(Renderer&& obj) noexcept = delete;
    
    Renderer& operator=(const Renderer& obj) = delete;
    Renderer& operator=(Renderer&& obj) = delete;

    void renderPage(int pageNum);

    [[nodiscard]] int getMaxPage() const;

private:
    poppler::document* m_Document;
    EBook& m_ActiveEBook;
};
}