#ifndef SAMPLEREPORTINGPANE_H
#define SAMPLEREPORTINGPANE_H

#include <QFrame>

class QHBoxLayout;

class samplereportingpane : public QFrame {
public:
    samplereportingpane();
    ~samplereportingpane();

    virtual QSize sizeHint() const;
protected:
    void setUpSubviews();

private:
    QHBoxLayout* main_layout;
};

#endif // SAMPLEREPORTINGPANE_H
