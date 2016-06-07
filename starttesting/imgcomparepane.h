#ifndef IMGCOMPAREPANE_H
#define IMGCOMPAREPANE_H

#include <QFrame>

class QVBoxLayout;
class QLabel;

class imgcomparepane : public QFrame {
public:
    imgcomparepane();
    ~imgcomparepane();

    virtual QSize sizeHint() const;
protected:
    void setUpSubviews();

private:
    QVBoxLayout* main_layout;
    QLabel* photo_preview;
};

#endif // IMGCOMPAREPANE_H
