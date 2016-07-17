#ifndef REPORTINGDETAILITEM_H
#define REPORTINGDETAILITEM_H

#include <QFrame>
class QHBoxLayout;
class QLabel;
class QComboBox;

class reportingdetailitem : public QFrame {
    Q_OBJECT

private:
    QHBoxLayout* main_layout;

    QLabel* label;
    QComboBox* box;

    QString title;

public:
    reportingdetailitem(const QString& t="");
    ~reportingdetailitem();

    void setUpSubviews();
    virtual QSize sizeHint() const;

    QString getItemTestResult() const;
    QString getItemTitle() const;
    void setCurrentSelected(bool b);
};

#endif // REPORTINGDETAILITEM_H
