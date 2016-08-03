#ifndef ABOUTMAINWIDGET_H
#define ABOUTMAINWIDGET_H

#include <QFrame>

class QVBoxLayout;
class descriptionlabel;
class QScrollArea;
class aboutuswidget;
class declearationwidget;

class aboutmainwidget : public QFrame {
    Q_OBJECT

protected Q_SLOTS:
    void des_btn_clicked();
    void aboutus_btn_clicked();
    void declearaton_btn_clicked();

public:
    aboutmainwidget();
    ~aboutmainwidget();

protected:
    void setupSubviews();
    virtual QSize sizeHint() const;

private:
    QVBoxLayout* main_layout;
    QScrollArea* area;
    descriptionlabel* t;
    aboutuswidget* a;
    declearationwidget* d;
};

#endif // ABOUTMAINWIDGET_H
