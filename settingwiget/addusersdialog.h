#ifndef ADDUSERSDIALOG_H
#define ADDUSERSDIALOG_H

#include <QDialog>
#include <QJsonArray>
class QLineEdit;
class QVBoxLayout;
class QComboBox;

class addusersdialog : public QDialog {
    Q_OBJECT

Q_SIGNALS:

protected Q_SLOTS:
    void saveBtnClicked();
    void cancelBtnClicked();

    void queryLstDoctorsSuccess(const QJsonArray&);
public:
    addusersdialog();
    ~addusersdialog();

protected:
    virtual QSize sizeHint() const;
    void setUpSubviews();

private:
    QVBoxLayout* main_layout;

    QLineEdit* user_name_edit;
    QLineEdit* pwd_edit;
    QComboBox* auth_box;

    QVector<QString> users_lst;
};

#endif // ADDUSERSDIALOG_H
