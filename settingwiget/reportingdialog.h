#ifndef REPORTINGDIALOG_H
#define REPORTINGDIALOG_H

#include <QDialog>
#include <QMap>
#include <QPair>
class QScrollArea;
class QVBoxLayout;
class QScrollArea;

class reportingdialog : public QDialog {
    Q_OBJECT

protected Q_SLOTS:
    void queryWormCatSuccess(const QJsonObject&);

    void addWorsCatsDialog();
    void deleteWorsCatsDialog();
    void addWormDialog();
    void deleteWormDialog();
    void saveWormchanges();

    void checkBtnChanged(bool);

private:
    QVBoxLayout* main_layout;

    QVBoxLayout* content_layout;
    QWidget* content_widget;
    QScrollArea* area;

    QMap<QString, bool> changes;

    void reloadData();
public:
    reportingdialog();
    ~reportingdialog();

    virtual QSize sizeHint() const;
    void setUpSubviews();
};

#endif // REPORTINGDIALOG_H
