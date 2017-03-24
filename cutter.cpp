//     CookieCutter
#include <iostream>

#include <poppler-qt5.h>
#include <poppler-document.h>
#include <poppler-page.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QLabel>
#include <QtGui/QImage>
#include <QPixmap>
#include <QSize>

//#include <QGraphicsScene>

int main(int argc, char **argv) {
  // Must have!
  QApplication app (argc, argv);
  QMainWindow *window = new QMainWindow();
  window->setWindowTitle(QString::fromUtf8("CookieCutter"));
  QWidget *centralWidget = new QWidget(window);
  QTabWidget *tabs = new QTabWidget(centralWidget);

  //tabs->setFixedSize(495, 495);
  //tabs->addTab(new QWidget(),"TAB 1");
  //
  // Load the document into a poppler:document
  Poppler::Document* document = Poppler::Document::load(argv[1]);
  Poppler::Page *page = document->page(0);
  QSize dims = page->pageSize();

  window->resize(dims.width(),dims.height());



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
      tabs->addTab(label,"tab");
      delete page;
    }
  }

  window->setCentralWidget(centralWidget);
  window->show();


  return app.exec();
}
