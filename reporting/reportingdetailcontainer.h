#ifndef REPORTINGDETAILCONTAINER_H
#define REPORTINGDETAILCONTAINER_H

#include <QFrame>
#include <vector>
#include <map>
#include <QJsonObject>
using std::vector;		using std::map;

class QVBoxLayout;
class QHBoxLayout;
class QCheckBox;
class detailpane;
class samplereportingpane;

class reportingdetailcontainer : public QFrame {
    Q_OBJECT

Q_SIGNALS:
    void changeCurrentSample(const QJsonObject&);

protected Q_SLOTS:
    void querySampleWithIDSuccess(const QJsonObject&);

public:
    reportingdetailcontainer();
    ~reportingdetailcontainer();

    virtual QSize sizeHint() const;

public slots:
    void checkBtnClicked();

protected:
    void setUpSubviews();

private:
    QVBoxLayout* main_layout;

    QVBoxLayout* detail_layout;
    vector<QCheckBox*> detail_vec;
    map<QString, detailpane*> detail_vec_pane;

    QJsonObject current_sample;

    samplereportingpane* sample_pane;
};

#endif // REPORTINGDETAILCONTAINER_H
