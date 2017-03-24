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
#include <QDebug>
#include <QMouseEvent>

class PageLabel : public QLabel {
  //  Q_OBJECT
public:
  PageLabel(QWidget* parent=0);
  void mousePressEvent(QMouseEvent * ev);
};

PageLabel::PageLabel(QWidget* parent) : QLabel(parent) {
}

void PageLabel::mousePressEvent(QMouseEvent *ev)
{
  QString x = QString::number(ev->x());
  QString y = QString::number(ev->y());
  qDebug() << x << "," << y;
}

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
  qDebug() << dims.width() << " and " << dims.height();

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
      PageLabel* label = new PageLabel();
      label->setPixmap(QPixmap::fromImage(image));
      tabs->addTab(label,"tab");
      delete page;
    }
  }

  window->setCentralWidget(centralWidget);
  window->show();


  return app.exec();
}
