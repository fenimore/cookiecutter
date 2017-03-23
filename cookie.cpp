// toy program for dealing with PDFs
// g++ this.cpp -lpoppler-cpp -lpoppler-qt4
//              ^ link poppler from /lib?.. I forget where it is
// commented, a little while after writing (ehem, bad idea)


// Questions:
// why don't spaces print out after crop
// what's with the ->

// TODO:
// get a page up with qt and maybe some tabs up
// then it's basicaly open

#include <iostream>

#include <poppler/cpp/poppler-document.h>
#include <poppler/cpp/poppler-page.h>
#include <poppler/cpp/poppler-rectangle.h>
// #include <poppler/qt4/poppler-qt4.h> // FOR GUI

int main(int argc, char **argv)
{
  // Load the document into a poppler:document
  poppler::document* doc = poppler::document::load_from_file(argv[1]);

  // Print count of pages?
  //std::cout << doc->pages() << std::endl;

  // Create poppler::page from index
  // cpp -> means a method from a pointer?
  poppler::page* page = doc->create_page(1);

  // Create a poppler::rectangle with floats
  poppler::rectf rec = poppler::rectangle<double>(0.0, 0.0, 100.0, 350.0);
  // Crop the page with the rectangle? Not sure what p is doing here.
  // UNUSED
  poppler::rectf p = page->page_rect(poppler::page_box_enum::crop_box);

  // Get coordinates? Example:
  // [0,0 566.929+708.661]
  // std::cout << p<< std::endl;

  // Crops the page with `rec`, but doesn't print out spaces (why not?)
  poppler::ustring str = page->text(rec, poppler::page::raw_order_layout);
  std::cout << str.to_latin1() << std::endl;

  // Prints the text from the page... das it.
  poppler::ustring test = page->text();
  std::cout << test.to_latin1() << std::endl;

  // return without errorr
  return 0;
}
