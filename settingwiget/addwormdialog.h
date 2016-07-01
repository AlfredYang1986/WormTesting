#ifndef ADDWORMDIALOG_H
#define ADDWORMDIALOG_H

#include <QDialog>
class QVBoxLayout;
class QLineEdit;
class QComboBox;

class addwormdialog : public QDialog {
    Q_OBJECT

protected Q_SLOTS:
    void addWormImpl();
    void quitDialog();
    void addWormSuccess();
    void onlyCategoriesSuccess(const QJsonArray&);

private:
    QVBoxLayout* main_layout;
    QLineEdit* worm_edit;
    QComboBox* worm_cat_box;

public:
    addwormdialog();
    ~addwormdialog();

    virtual QSize sizeHint() const;
    void setUpSubviews();
};

#endif // ADDWORMDIALOG_H
