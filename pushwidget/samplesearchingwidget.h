#ifndef SAMPLESEARCHINGWIDGET_H
#define SAMPLESEARCHINGWIDGET_H

#include <QFrame>
#include <QJsonArray>
#include <QJsonObject>

class QVBoxLayout;
class QTableWidget;

class samplesearchingwidget : public QFrame {
    Q_OBJECT

Q_SIGNALS:
    void currentSample(const QJsonObject&);
    void doubleSelectSample(const QJsonObject&);

protected Q_SLOTS:
    void queryNotTestSamples(const QJsonArray&);
    void queryTesetedSamples(const QJsonArray&);
    void notTestWidgetClicked(const QModelIndex&);
    void testedWidgetClicked(const QModelIndex&);
    void notTestWidgetDoubleClicked(const QModelIndex&);
    void testedWidgetDoubleClicked(const QModelIndex&);

protected:
    virtual void showEvent(QShowEvent *);

private:
    QVBoxLayout*  main_layout;
    QTableWidget* not_test_sample;
    QTableWidget* tested_sample;

    QJsonArray vec_sample_not_test;
    QJsonArray vec_sample_tested;
public:
    samplesearchingwidget();
    ~samplesearchingwidget();

    void setUpSubviews();
    void reloadData();

protected:
    virtual QSize sizeHit() const;
};

#endif // SAMPLESEARCHINGWIDGET_H
