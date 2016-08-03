#ifndef ABOUTUSWIDGET_H
#define ABOUTUSWIDGET_H

#include <QFrame>

class QHBoxLayout;
class QLabel;

class aboutuswidget : public QFrame {
    Q_OBJECT

public:
    aboutuswidget();
    ~aboutuswidget();

protected:
    void setupSubviews();

private:
    QHBoxLayout* main_layout;
    QLabel* aboutus;
    QLabel* img;
};

#endif // ABOUTUSWIDGET_H
