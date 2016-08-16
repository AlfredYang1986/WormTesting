#ifndef PRINTCONFIGDIALOG_H
#define PRINTCONFIGDIALOG_H

#include <QDialog>

class QVBoxLayout;
class QLineEdit;

class printconfigdialog : public QDialog {
    Q_OBJECT

Q_SIGNALS:

protected Q_SLOTS:
    void saveBtnClicked();
    void cancelBtnClicked();

public:
    printconfigdialog();
    ~printconfigdialog();

protected:
    virtual QSize sizeHint() const;
    void setupSubviews();

private:
    QVBoxLayout* main_layout;
    QLineEdit* hos_name_edit;
};

#endif // PRINTCONFIGDIALOG_H
