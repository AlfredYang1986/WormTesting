#ifndef STARTTESTINGPAGE_H
#define STARTTESTINGPAGE_H

#include <QFrame>
#include <QJsonObject>

class QVBoxLayout;
class QPushButton;
class sampledetailwidget;
class wormtreewidget;
class imgcomparepane;
class samplesearchingwidget;
class QImage;

class starttestingpage : public QFrame {
    Q_OBJECT

Q_SIGNALS:

protected Q_SLOTS:
    void startTestingBtnClicked();
    void endTestingBtnClicked();

    void takeImageSuccess(const QImage&);

public:
    enum TestStauts {
        TestStatus_not_ready,
        TestStatus_ready,
        TestStatus_testing
    };
    Q_ENUM(TestStauts);

public:
    starttestingpage();
    ~starttestingpage();

protected:
    void setUpSubviews();

private:
    QVBoxLayout* main_layout;
    sampledetailwidget* sample_detail;
    samplesearchingwidget* sample_searching_widget;
    imgcomparepane* img_pane;

    TestStauts status;
    QPushButton* control_start_btn;
    QPushButton* control_end_btn;
};

#endif // STARTTESTINGPAGE_H
