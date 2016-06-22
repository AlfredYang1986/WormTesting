#ifndef STARTTESTINGPAGE_H
#define STARTTESTINGPAGE_H

#include <QFrame>
#include <QJsonObject>

class QVBoxLayout;
class sampledetailwidget;
class wormtreewidget;
class imgcomparepane;
class samplesearchingwidget;

class starttestingpage : public QFrame {
    Q_OBJECT

public:
    starttestingpage();
    ~starttestingpage();

protected:
    void setUpSubviews();

private:
    QVBoxLayout* main_layout;
    sampledetailwidget* sample_detail;
//    wormtreewidget* worm_tree;
    samplesearchingwidget* sample_searching_widget;
    imgcomparepane* img_pane;
};

#endif // STARTTESTINGPAGE_H
