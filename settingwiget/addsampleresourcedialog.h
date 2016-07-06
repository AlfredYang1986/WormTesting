#ifndef ADDSAMPLERESOURCEDIALOG_H
#define ADDSAMPLERESOURCEDIALOG_H

#include <QDialog>
class QVBoxLayout;
class QLineEdit;

class addsampleresourcedialog : public QDialog {
    Q_OBJECT

Q_SIGNALS:

protected Q_SLOTS:
    void savaBtnClicked();
    void cancelBtnClicked();

private:
    QVBoxLayout* main_layout;

    QLineEdit* resource_edit;

public:
    addsampleresourcedialog();
    ~addsampleresourcedialog();

    virtual QSize sizeHint() const;
    void setUpSubviews();
};

#endif // ADDSAMPLERESOURCEDIALOG_H
