#ifndef PAGETAB_H
#define PAGETAB_H

#include <QTabWidget>

class PageTab: public QTabWidget
{
  Q_OBJECT
 public:
  PageTab(QWidget* parent)
    {
      this->setParent(parent);
      connect(this,SIGNAL(tabCloseRequested(int)),this,SLOT(closeTab(int)));
    };
  ~ PageTab(){};



  public slots:
    void closeTab(int index)
    {
      //Handle tabCloseRequested Signal and Close the Tab
      this->removeTab(index);
    };
};

#endif
