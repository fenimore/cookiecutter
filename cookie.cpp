//     CookieCutter
// toy program for dealing with PDFs
// g++ this.cpp -lpoppler-cpp -lpoppler-qt4
//              ^ link poppler located in /lib
//     Questions:
// why don't spaces print out after crop
// what's with the ->
//     Roadmap:
// Get a page up with QT and maybe some tabs up.
// Have the user select a color, and then drag for rectangles.
// Each color will be a column, and each document/page will be a row.
// Then it's basically done.

#include <iostream>

#include <poppler/cpp/poppler-document.h>
#include <poppler/cpp/poppler-page.h>
#include <poppler/cpp/poppler-rectangle.h>
// #include <poppler/qt4/poppler-qt4.h> // FOR GUI

int main(int argc, char **argv)
{
  // Load the document into a poppler:document
  poppler::document* doc = poppler::document::load_from_file(argv[1]);

  // Print count of pages
  //std::cout << doc->pages() << std::endl;

  // Create poppler::page from index
  // In cpp -> means a method from a pointer...?
  poppler::page* page = doc->create_page(1);

  // Create a poppler::rectangle with floats (hence f)
  // capture these coordinates from some sort of QT mouse event
  // then store the rectangles and associated pages/documents
  poppler::rectf rec = poppler::rectangle<double>(0.0, 0.0, 100.0, 350.0);

  // Get the page crop_box (that is it's coordinates?)
  // For Example, if printed:
  // [0,0 566.929+708.661]
  poppler::rectf p = page->page_rect(poppler::page_box_enum::crop_box);
  // std::cout << p << std::endl;

  // Crops the page with `rec`, but doesn't print out spaces (why not?)
  //poppler::ustring str = page->text(rec, poppler::page::raw_order_layout);
  QString str = page->text( QRectF(), Poppler::Page::RawOrderLayout ).toUtf8()
  std::cout << str.to_latin1() << std::endl;

  // Prints the text from the page... das it.
  poppler::ustring test = page->text();
  std::cout << test.to_latin1() << std::endl;

  // return without error
  return 0;
}
