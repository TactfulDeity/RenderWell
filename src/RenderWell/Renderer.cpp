#include "Renderer.hpp"

#include "RenderWell/render_well_directories.hpp"

#include <poppler/cpp/poppler-page-renderer.h>

#include <memory>
#include <stdexcept>

using namespace RenderWell;

// Declare Constructor and Destructor
Renderer::Renderer(DataBase& dataBase, unsigned long index)
: m_ActiveEBook(dataBase.getDataObjectRefAs<EBook>(index))
{
  if(!poppler::page_renderer::can_render())
  {
    throw std::runtime_error("Poppler library is incapable of rendering at the current time");
  }

  // Call to Poppler library to render the document at supplied path
  m_Document = poppler::document::load_from_file(m_ActiveEBook.m_Location);
  if (m_Document == nullptr) {
    throw std::runtime_error("loading error");
  }
  if (m_Document->is_locked()) {
    throw std::runtime_error("encrypted document");
  }
}

Renderer::~Renderer()
{
  delete m_Document;
}

void Renderer::renderPage(int pageNum)
{
  poppler::page_renderer renderer = poppler::page_renderer();

  if(pageNum < 0 || pageNum >= m_Document->pages()) {
    throw std::runtime_error("Page is out of bounds");
  }

  poppler::page* page =m_Document->create_page(pageNum);
  if(page == nullptr) {
    throw std::runtime_error("Page does not exist");
  }

  poppler::page_renderer pr;
  pr.set_render_hint(poppler::page_renderer::antialiasing, true);
  pr.set_render_hint(poppler::page_renderer::text_antialiasing, true);

  poppler::image img = pr.render_page(page);
  if (!img.is_valid()) {
    throw std::runtime_error("Rendering failed");
  }

  if(!img.save(k_TempFilesDir.string() + "/" + std::to_string(pageNum) + ".png", "png")) {
    throw std::runtime_error("Saving to file failed");
  }
}

int Renderer::getMaxPage() const
{
  return m_Document->pages() - 1;
}
