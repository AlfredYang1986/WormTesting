#ifndef ADDWORMCATDIALOG_H
#define ADDWORMCATDIALOG_H

#include <QDialog>
class QVBoxLayout;
class QLineEdit;

class addWormCatDialog : public QDialog {
    Q_OBJECT

protected Q_SLOTS:
    void addWormCatImpl();
    void quitDialog();
    void addWormCatSuccess();

private:
    QVBoxLayout* main_layout;
    QLineEdit* worm_cat_edit;

public:
    addWormCatDialog();
    ~addWormCatDialog();

    virtual QSize sizeHint() const;
    void setUpSubviews();
};

#endif // ADDWORMCATDIALOG_H
