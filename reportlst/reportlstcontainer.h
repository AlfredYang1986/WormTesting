#ifndef REPORTLSTCONTAINER_H
#define REPORTLSTCONTAINER_H

#include <QFrame>

class QHBoxLayout;
class resourcetreewidget;

class reportlstcontainer : public QFrame {
public:
    reportlstcontainer();
    ~reportlstcontainer();

    virtual QSize sizeHint() const;
protected:
    void setUpSubviews();

private:
    QHBoxLayout* main_layout;

    resourcetreewidget* search_tree;
};

#endif // REPORTLSTCONTAINER_H
