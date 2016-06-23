#ifndef SAMPLEREPORTINGPANE_H
#define SAMPLEREPORTINGPANE_H

#include <QFrame>

class QHBoxLayout;

class samplereportingpane : public QFrame {
    Q_OBJECT

Q_SIGNALS:

protected Q_SLOTS:
    void startReporting();
    void endReporting();

public:
    samplereportingpane();
    ~samplereportingpane();

    virtual QSize sizeHint() const;

    void fillInputs(const QJsonObject& sample);
protected:
    void setUpSubviews();

private:
    QHBoxLayout* main_layout;

    QVector<QWidget*> inputs;
};

#endif // SAMPLEREPORTINGPANE_H
