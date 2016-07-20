#ifndef DELETEUSERSDIALOG_H
#define DELETEUSERSDIALOG_H

#include <QDialog>
class QVBoxLayout;
class QComboBox;

class deleteusersdialog :  public QDialog {
    Q_OBJECT

Q_SIGNALS:

protected Q_SLOTS:
    void saveBtnClicked();
    void cancelBtnClicked();

    void queryLstDoctorsSuccess(const QJsonArray&);

public:
    deleteusersdialog();
    ~deleteusersdialog();

protected:
    virtual QSize sizeHint() const;
    void setUpSubviews();

private:
    QVBoxLayout* main_layout;
    QComboBox* box;
};

#endif // DELETEUSERSDIALOG_H
