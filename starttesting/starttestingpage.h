#ifndef STARTTESTINGPAGE_H
#define STARTTESTINGPAGE_H

#include <QFrame>
#include <QJsonObject>

class QVBoxLayout;
class QPushButton;
class sampledetailwidget;
class imgcomparepane;
//class samplesearchingwidget;
class commonimglstwidget;
class QImage;

class starttestingpage : public QFrame {
    Q_OBJECT

Q_SIGNALS:
    void startReporting(const QString&);
    void startComparing(const QString&);

protected Q_SLOTS:
    void startTestingBtnClicked();
    void endTestingBtnClicked();
    void startReportingBtnClicked();
    void startComparingBtnClicked();

    void takeImageSuccess(const QImage&);
    void uploadSampleImageSuccess(const QString&, const QString&);

    void didFinishEditPatientId(const QString& patient_id);
    void didFinishEditSampleId(const QString& sample_id);
    void queryPatientSuccess(const QJsonObject & patient);
    void querySampleSuccess(const QJsonObject& sample);

    void querySampleWithIDSuccess(const QJsonObject&);

protected:
    virtual void showEvent (QShowEvent* event);
    virtual void hideEvent(QHideEvent *event);

public:
    enum TestStatus {
        TestStatus_not_ready,
        TestStatus_ready,
        TestStatus_testing
    };
    Q_ENUM(TestStatus);

public:
    starttestingpage();
    ~starttestingpage();

    void setCurrentTestingSample(const QJsonObject& sample);

    TestStatus currentStatus() const;
protected:
    void setUpSubviews();

private:
    QVBoxLayout* main_layout;
    sampledetailwidget* sample_detail;
    imgcomparepane* img_pane;
    commonimglstwidget* img_lst_pane;

    TestStatus status;
    QPushButton* control_start_btn;
    QPushButton* control_end_btn;
    QPushButton* control_report_btn;
    QPushButton* control_compare_btn;
};

#endif // STARTTESTINGPAGE_H
