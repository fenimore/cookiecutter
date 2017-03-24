//     CookieCutter
#include <iostream>

#include <poppler-qt5.h>
#include <poppler-document.h>
#include <poppler-page.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtGui/QImage>
#include <QPixmap>

//#include <QGraphicsScene>

int main(int argc, char **argv) {
  // Must have!
  QApplication app (argc, argv);

  // Load the document into a poppler:document
  Poppler::Document* document = Poppler::Document::load(argv[1]);
  //poppler::document* doc = poppler::document::load_from_file(argv[1]);
  if (!document) {
    std::cout << "No Load" << std::endl;
  }

  document->setRenderHint(Poppler::Document::Antialiasing, true);

  for (int i = 0; i < document->numPages(); ++i) {
    Poppler::Page *page = document->page(i);
    if (page) {
      QImage image = page->renderToImage();
      // image.save();
      // sets parent of label to main window
      QLabel *label = new QLabel("Image");
      label->setPixmap(QPixmap::fromImage(image));
      // label->show();
      delete page;
    }
  }

  return app.exec();
}
