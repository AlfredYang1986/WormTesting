#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
class QVBoxLayout;
class QLineEdit;

class logindialog : public QDialog {
    Q_OBJECT

protected Q_SLOTS:
    void loginBtnClicked();

private:
    QVBoxLayout* main_layout;
    QLineEdit* user_name_edit;
    QLineEdit* password_edit;

public:
    logindialog();
    ~logindialog();

protected:
    virtual QSize sizeHint() const;
    void setUpSubview();

    virtual void showEvent(QShowEvent *);
};

#endif // LOGINDIALOG_H
