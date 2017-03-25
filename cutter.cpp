//     CookieCutter
#include <iostream>

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

#include <vector>

using namespace std;

struct Point {
  int x, y;
  //Point();
  Point New(int, int);
};

Point NewPoint(int a, int b) {
  Point result = Point();
  result.x = a;
  result.y = b;
  return result;
}

vector<Point> NewBox(Point a, Point z) {
  Point x = a;
  Point y = z;
  Point w = NewPoint(z.x, a.y);
  Point h = NewPoint(a.x, z.y);
  return vector<Point>{x, y, w, h};
}

class PageLabel : public QLabel {
  //Q_OBJECT
public:
  PageLabel(QWidget* parent=0);
  void mousePressEvent(QMouseEvent * ev);
  // void paintEvent(QPaintEvent * e);
  Point lastVec;
};

PageLabel::PageLabel(QWidget* parent) : QLabel(parent) {
}

void PageLabel::mousePressEvent(QMouseEvent *ev) {
  qDebug() << lastVec.x << "," << lastVec.y;
  int x = ev->x();
  int y = ev->y();
  Point nextVec = NewPoint(x, y);
  vector<Point> rec = NewBox(lastVec, nextVec);
  // cout << rec[0].x << " " << rec[1].y << " "  << " " << endl;
  lastVec.x = x;
  lastVec.y = y;
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
