#ifndef UPLOADWORMIMGDIALOG_H
#define UPLOADWORMIMGDIALOG_H

#include <QDialog>
#include <QJsonObject>
class QVBoxLayout;
class QComboBox;
class commonimglstwidget;
class QLabel;

class uploadwormimgdialog : public QDialog {
    Q_OBJECT

Q_SIGNALS:

protected Q_SLOTS:
    void savaBtnClicked();
    void cancelBtnClicked();

    void queryWormCatSuccess(const QJsonObject&);
    void currentBoxTextChanged(const QString&);

    void uploadSampleImageSuccess(const QString&, const QString&);

protected:
    virtual void showEvent(QShowEvent *);
    virtual void hideEvent(QHideEvent *);

private:
    QVBoxLayout* main_layout;
    QComboBox* box;
    QLabel* pic;
    commonimglstwidget* img_lst;

    QJsonObject current_cats;
public:
    uploadwormimgdialog();
    ~uploadwormimgdialog();

    virtual QSize sizeHint() const;
    void setUpSubviews();
};

#endif // UPLOADWORMIMGDIALOG_H
