#ifndef REPORTINGIMGPANE_H
#define REPORTINGIMGPANE_H

#include <QFrame>

class QVBoxLayout;

class reportingimgpane : public QFrame {
public:
    reportingimgpane();
    ~reportingimgpane();

    virtual QSize sizeHint() const;

protected:
    void setUpSubviews();

private:
    QVBoxLayout* main_layout;
};

#endif // REPORTINGIMGPANE_H
