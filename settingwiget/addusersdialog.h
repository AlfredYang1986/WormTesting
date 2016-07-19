#ifndef ADDUSERSDIALOG_H
#define ADDUSERSDIALOG_H

#include <QDialog>

class addusersdialog : public QDialog {
    Q_OBJECT

public:
    addusersdialog();
    ~addusersdialog();

protected:
    virtual QSize sizeHint() const;
    void setUpSubviews();
};

#endif // ADDUSERSDIALOG_H
