#ifndef UPDATEWORMDESDIALOG_H
#define UPDATEWORMDESDIALOG_H

#include <QDialog>
#include <QJsonObject>

class QVBoxLayout;
class QTextEdit;
class QComboBox;

class updatewormdesdialog : public QDialog {
    Q_OBJECT

protected Q_SLOTS:
    void savaBtnClicked();
    void cancelBtnClicked();

    void queryWormCatSuccess(const QJsonObject&);
    void currentBoxTextChanged(const QString&);
private:
    QVBoxLayout* main_layout;
    QComboBox* box;
    QTextEdit* des;

    QJsonObject current_cats;
public:
    updatewormdesdialog();
    ~updatewormdesdialog();

    virtual QSize sizeHint() const;
    void setUpSubviews();
};

#endif // UPDATEWORMDESDIALOG_H
