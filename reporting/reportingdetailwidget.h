#ifndef REPORTINGDETAILWIDGET_H
#define REPORTINGDETAILWIDGET_H

#include <QFrame>
#include <QJsonObject>
class QHBoxLayout;
class QVBoxLayout;
class QFormLayout;
class QScrollArea;
class reportingdetailitem;

class reportingdetailwidget : public QFrame {
    Q_OBJECT

Q_SIGNALS:

protected Q_SLOTS:
    void queryReportingWormSuccess(const QJsonObject&);

protected:
    virtual void showEvent(QShowEvent *);
    virtual void hideEvent(QHideEvent *);

    void clearItems();
private:
    QHBoxLayout* main_layout;
    QScrollArea* area;

    QFrame* content_widget;
    QVBoxLayout* content_layout;

    QVector<reportingdetailitem*> items;

    QJsonObject current_sample;
public:
    reportingdetailwidget();
    ~reportingdetailwidget();

    void setUpSubviews();
    virtual QSize sizeHint() const;

    QVector<QString> getTestItemResults() const;
    void setSampleDefaultResult(const QJsonObject& sample);

    QStringList getAllReportingField() const;
};

#endif // REPORTINGDETAILWIDGET_H
