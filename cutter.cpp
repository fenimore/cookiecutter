//     CookieCutter
#include <iostream>
#include <vector>
#include <cmath>

#include <poppler-qt5.h>
#include <poppler-document.h>
#include <poppler-page.h>
#include <poppler/cpp/poppler-rectangle.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QLabel>
#include <QtGui/QImage>
#include <QPixmap>
#include <QPainter>
#include <QSize>
#include <QDebug>
#include <QMouseEvent>
#include <QRectF>



using namespace std;

struct Point {
  double x, y;
  //Point();
  Point New(double, double);
};

vector<double> NewBox(Point orig, Point dest) {
  double x = orig.x;
  double y = orig.y;
  double w = std::abs(orig.x - dest.x);
  double h = std::abs(orig.y - dest.y);
  return vector<double>{x, y, w, h};
}

class PageLabel : public QLabel {
  //Q_OBJECT
public:
  PageLabel(QWidget* parent=0);
  void mousePressEvent(QMouseEvent * ev);
  void mouseReleaseEvent(QMouseEvent * ev);
  // void paintEvent(QPaintEvent * e);
  Point pressVec;
  Point liftVec;
  Poppler::Page *page;
};

PageLabel::PageLabel(QWidget* parent) : QLabel(parent) {
}

void PageLabel::mousePressEvent(QMouseEvent *ev) {
  qDebug() << "Press:   " << pressVec.x << ", " << pressVec.y;
  double x = ev->x();
  double y = ev->y();
  pressVec.x = x;
  pressVec.y = y;
}

void PageLabel::mouseReleaseEvent(QMouseEvent *ev) {
  qDebug() << "Release: " << liftVec.x << ", " << liftVec.y;
  double x = ev->x();
  double y = ev->y();
  liftVec.x = x;
  liftVec.y = y;

  // Get rectangle
  vector<double> rec = NewBox(pressVec, liftVec);
  QRectF crop = QRectF(rec[0], rec[1], rec[2], rec[3]);
  QString str = page->text(crop, Poppler::Page::RawOrderLayout);
  qDebug() << "Extract:"  << "\n"<< str;
}

// void PageLabel::paintEvent(QPaintEvent *e) {
//   QPainter painter(this);
//   QRectF rectangle(10.0, 20.0, 80.0, 60.0);
//   int startAngle = 30 * 16;
//   int spanAngle = 120 * 16;
//   painter.drawArc(rectangle, startAngle, spanAngle);
// }


int main(int argc, char **argv) {
  // Must have!
  QApplication app (argc, argv);
  QMainWindow *window = new QMainWindow();
  window->setWindowTitle(QString::fromUtf8("CookieCutter"));
  QWidget *centralWidget = new QWidget(window);
  QTabWidget *tabs = new QTabWidget(centralWidget);
  tabs->setTabsClosable(true);
  // Load the document into a poppler:document
  Poppler::Document* document = Poppler::Document::load(argv[1]);
  Poppler::Page *page = document->page(0);
  QSize dims = page->pageSize();
  qDebug() << dims.width() << " and " << dims.height();
  window->resize(dims.width(),dims.height());

  if (!document) {
    std::cout << "Failure Loading" << std::endl;
  }

  document->setRenderHint(Poppler::Document::Antialiasing, true);

  for (int i = 0; i < document->numPages(); ++i) {
    Poppler::Page *page = document->page(i);
    cout << page << endl;
    PageLabel *label = new PageLabel();
    if (page) {
      QImage image = page->renderToImage();
      // image.save();
      // sets parent of label to main window
      label->page = page;
      label->setPixmap(QPixmap::fromImage(image));
      tabs->addTab(label,argv[1]);
      //delete page;
    }
  }

  window->setCentralWidget(centralWidget);
  window->show();


  return app.exec();
}
