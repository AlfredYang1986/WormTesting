#ifndef PUSHWIDGET_H
#define PUSHWIDGET_H

#include <QFrame>

class QVBoxLayout;
class QLineEdit;
class QTextEdit;
class QComboBox;
class samplesearchingwidget;
class sampledetailwidget;

class pushwidget : public QFrame {
    Q_OBJECT

Q_SIGNALS:
    void startTesting(const QJsonObject&);
    void startReporting(const QJsonObject&);

protected Q_SLOTS:
    void didFinishEditPatientId(const QString& patient_id);
    void didFinishEditSampleId(const QString& sample_id);
    void queryPatientSuccess(const QJsonObject&);
    void querySampleSuccess(const QJsonObject&);

    void pushSampleSuccess(const QJsonObject& sample);

    void doubleSelectSample(const QJsonObject& sample);

private:
    QVBoxLayout* main_layout;

    sampledetailwidget* sample_detail_widget;
    samplesearchingwidget* sample_searching_widget;
public:
    pushwidget();
    ~pushwidget();

    void setUpSubviews();

protected:
    virtual QSize sizeHint() const;
    virtual void showEvent(QShowEvent *);
    virtual void hideEvent(QHideEvent *);
};

#endif // PUSHWIDGET_H
