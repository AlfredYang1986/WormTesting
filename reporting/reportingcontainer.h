#ifndef REPORTINGCONTAINER_H
#define REPORTINGCONTAINER_H

#include <QFrame>

class QHBoxLayout;
class reportingdetailcontainer;
class reportingimgpane;

class reportingcontainer : public QFrame {
    Q_OBJECT

public:
    reportingcontainer();
    ~reportingcontainer();

    virtual QSize sizeHint() const;

protected:
    void setUpSubviews();

private:
    QHBoxLayout* main_layout;
    reportingdetailcontainer* reporting_detail;
    reportingimgpane* reporting_img;
};

#endif // REPORTINGCONTAINER_H
