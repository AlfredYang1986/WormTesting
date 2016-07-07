#ifndef REPORTLSTCONTAINER_H
#define REPORTLSTCONTAINER_H

#include <QFrame>

class QHBoxLayout;
class reportsearchconditionwidget;
class searchresulttablewidget;

class reportlstcontainer : public QFrame {
    Q_OBJECT

Q_SIGNALS:
    void startReporting(const QString&);

protected Q_SLOTS:
    void startReportSlot(const QJsonObject&);

public:
    reportlstcontainer();
    ~reportlstcontainer();

    virtual QSize sizeHint() const;
protected:
    void setUpSubviews();

    virtual void showEvent(QShowEvent *);
    virtual void hideEvent(QHideEvent *);

private:
    QHBoxLayout* main_layout;

    reportsearchconditionwidget* condition_widget;
    searchresulttablewidget* search_result;
};

#endif // REPORTLSTCONTAINER_H
