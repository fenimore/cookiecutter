//     CookieCutter
#include <iostream>

#include <poppler-qt4.h> // FOR GUI
//#include <poppler/qt5/poppler-qt5.h> // FOR GUI
#include <poppler-document.h>
//#include <poppler/cpp/poppler-document.h>
//#include <poppler/cpp/poppler-page.h>


int main(int argc, char **argv)
{
  // Load the document into a poppler:document
  Poppler::Document* document = Poppler::Document::load(argv[1]);
  //poppler::document* doc = poppler::document::load_from_file(argv[1]);

  // Access page of the PDF file
  //poppler::page* page = document->page(0);  // Document starts at page 0

  //QImage image = page->renderToImage(
  // return without error
  //poppler::rectf p = page->page_rect(poppler::page_box_enum::crop_box);
  //std::cout << p << std::endl;
  return 0;
}
