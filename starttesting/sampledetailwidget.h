#ifndef SAMPLEDETAILWIDGET_H
#define SAMPLEDETAILWIDGET_H

#include <QFrame>

class QFormLayout;
class QVBoxLayout;

class sampledetailwidget : public QFrame {
    Q_OBJECT

public:
    sampledetailwidget();
    ~sampledetailwidget();

    virtual QSize sizeHint() const;
protected:
    void setUpSubviews();

private:
//    QFormLayout* main_layout;
    QVBoxLayout* main_layout;
};

#endif // SAMPLEDETAILWIDGET_H
