#ifndef DELETEPATIENTTYPEDIALOG_H
#define DELETEPATIENTTYPEDIALOG_H

#include <QDialog>
class QVBoxLayout;
class QComboBox;

class deletepatienttypedialog : public QDialog {
    Q_OBJECT

Q_SIGNALS:

protected Q_SLOTS:
    void saveBtnClicked();
    void cancelBtnClicked();

    void queryPatientTypeSuccess(const QJsonArray&);

private:
    QVBoxLayout* main_layout;
    QComboBox* patient_box;

public:
    deletepatienttypedialog();
    ~deletepatienttypedialog();

    virtual QSize sizeHint() const;
    void setUpSubviews();
};

#endif // DELETEPATIENTTYPEDIALOG_H
