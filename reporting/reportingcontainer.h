#ifndef REPORTINGCONTAINER_H
#define REPORTINGCONTAINER_H

#include <QFrame>
#include <QJsonObject>
#include <QJsonArray>

class QHBoxLayout;
class sampledetailwidget;
class reportingimgpane;
class commonimglstwidget;
class reportingdetailwidget;
class commonimgpreviewwidget;
class QTableWidget;
class QTextDocument;

class reportingcontainer : public QFrame {
    Q_OBJECT

Q_SIGNALS:

protected Q_SLOTS:
    void didFinishEditPatientId(const QString& patient_id);
    void didFinishEditSampleId(const QString& sample_id);
    void queryPatientSuccess(const QJsonObject & patient);
    void querySampleSuccess(const QJsonObject& sample);

    void currentSampleChange(const QJsonObject&);
    void querySampleWithIDSuccess(const QJsonObject&);

    void saveTestResult();

    void testedWidgetClicked(const QModelIndex&);
    void queryTesetedSamples(const QJsonArray&);

//    void printReport();
//    void printReportPDF();
    void printPreview();
protected:
    virtual void showEvent(QShowEvent *);
    virtual void hideEvent(QHideEvent *);

public:
    reportingcontainer();
    ~reportingcontainer();

    virtual QSize sizeHint() const;

    void setCurrentReportingSampleId(const QString& sample_id);
    void setCurrentReportingSample(const QJsonObject& sample);

    QString htmlContent(QTextDocument& document);
    void changeReportingStatusInService();
protected:
    void setUpSubviews();

private:
    QHBoxLayout* main_layout;
    sampledetailwidget* sample_detail;
    //reportingimgpane* reporting_img;
    commonimglstwidget* img_lst;
    reportingdetailwidget* reporting_detail;
    commonimgpreviewwidget* img_preview;
    QTableWidget*     tested_sample;

    QJsonArray vec_sample_tested;

    QJsonObject current_sample;
};

#endif // REPORTINGCONTAINER_H
