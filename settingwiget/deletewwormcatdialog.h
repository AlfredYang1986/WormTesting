#ifndef DELETEWWORMCATDIALOG_H
#define DELETEWWORMCATDIALOG_H

#include <QDialog>
class QVBoxLayout;
class QComboBox;

class deletewwormcatdialog : public QDialog {
    Q_OBJECT

protected Q_SLOTS:
    void deleteWormCatImpl();
    void quitDialog();

    void deleteWormCatSuccess();

    void onlyCategoriesSuccess(const QJsonArray&);

private:
    QVBoxLayout* main_layout;
    QComboBox* box;

public:
    deletewwormcatdialog();
    ~deletewwormcatdialog();

    virtual QSize sizeHint() const;
    void setUpSubviews();

};

#endif // DELETEWWORMCATDIALOG_H
