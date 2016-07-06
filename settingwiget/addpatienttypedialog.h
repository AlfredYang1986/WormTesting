#ifndef ADDPATIENTTYPEDIALOG_H
#define ADDPATIENTTYPEDIALOG_H

#include <QDialog>
class QVBoxLayout;
class QLineEdit;

class addpatienttypedialog : public QDialog {
    Q_OBJECT

Q_SIGNALS:

protected Q_SLOTS:
    void savaBtnClicked();
    void cancelBtnClicked();

private:
    QVBoxLayout* main_layout;
    QLineEdit* patient_edit;

public:
    addpatienttypedialog();
    ~addpatienttypedialog();

    virtual QSize sizeHint() const;
    void setUpSubviews();
};

#endif // ADDPATIENTTYPEDIALOG_H
