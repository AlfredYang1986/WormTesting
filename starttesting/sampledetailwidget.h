#ifndef SAMPLEDETAILWIDGET_H
#define SAMPLEDETAILWIDGET_H

#include <QFrame>
#include <QVector>
#include <QWidget>
#include <QJsonObject>

class QFormLayout;
class QVBoxLayout;

class sampledetailwidget : public QFrame {
    Q_OBJECT

Q_SIGNALS:

public Q_SLOTS:
    void currentSample(const QJsonObject&);

public:
    sampledetailwidget();
    ~sampledetailwidget();

    virtual QSize sizeHint() const;

    const QJsonObject& queryCurrentObject() const;
protected:
    void setUpSubviews();

private:
//    QFormLayout* main_layout;
    QVBoxLayout* main_layout;
    QVector<QWidget*> inputs;

    QJsonObject current_sample;
};

#endif // SAMPLEDETAILWIDGET_H
