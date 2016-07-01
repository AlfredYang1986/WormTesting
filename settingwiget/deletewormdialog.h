#ifndef DELETEWORMDIALOG_H
#define DELETEWORMDIALOG_H

#include <QDialog>
#include <QJsonObject>
class QVBoxLayout;
class QComboBox;

class deletewormdialog : public QDialog {
    Q_OBJECT

protected Q_SLOTS:
    void deleteWormImpl();
    void quitDialog();
    void deleteWormSuccess();

    void queryWormCatSuccess(const QJsonObject&);

    void catChanges(const QString&);

private:
    QVBoxLayout* main_layout;
    QComboBox* worm_box;
    QComboBox* worm_cat_box;

    QJsonObject current_cats;
public:
    deletewormdialog();
    ~deletewormdialog();

    virtual QSize sizeHint() const;
    void setUpSubviews();
};

#endif // DELETEWORMDIALOG_H
