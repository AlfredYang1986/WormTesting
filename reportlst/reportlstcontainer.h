#ifndef REPORTLSTCONTAINER_H
#define REPORTLSTCONTAINER_H

#include <QFrame>

class QHBoxLayout;

class reportlstcontainer : public QFrame {
public:
    reportlstcontainer();
    ~reportlstcontainer();

    virtual QSize sizeHint() const;
protected:
    void setUpSubviews();

private:
    QHBoxLayout* main_layout;
};

#endif // REPORTLSTCONTAINER_H
