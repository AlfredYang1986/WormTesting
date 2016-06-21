#ifndef SAMPLESEARCHINGWIDGET_H
#define SAMPLESEARCHINGWIDGET_H

#include <QFrame>
#include <QVector>

class QVBoxLayout;
class QTableWidget;

class samplesearchingwidget : public QFrame {
    Q_OBJECT

Q_SIGNALS:

protected Q_SLOTS:
    void queryNotTestSamples(const QJsonArray&);
    void queryTesetedSamples(const QJsonArray&);

private:
    QVBoxLayout*  main_layout;
    QTableWidget* not_test_sample;
    QTableWidget* tested_sample;

    QVector<QJsonObject> vec_sample_not_test;
    QVector<QJsonObject> vec_sample_tested;
public:
    samplesearchingwidget();
    ~samplesearchingwidget();

    void setUpSubviews();

protected:
    virtual QSize sizeHit() const;
};

#endif // SAMPLESEARCHINGWIDGET_H
