#ifndef IMAGECOMPAREWIDGET_H
#define IMAGECOMPAREWIDGET_H

#include <QFrame>
#include <QJsonObject>
class QHBoxLayout;
class commonimglstwidget;
class QComboBox;
class QLabel;
class QLineEdit;

class imagecomparewidget : public QFrame {
    Q_OBJECT

Q_SIGNALS:

protected Q_SLOTS:
    void queryWormCatSuccess(const QJsonObject&);

    void currentBoxTextChanged(const QString&);
    void didFinishEditSampleID_slot();

    void querySampleWithIDSuccess(const QJsonObject&);

    void changeWormPreview(const QPixmap&);
    void changeSamplePreview(const QPixmap&);

protected:
    virtual void showEvent(QShowEvent *);
    virtual void hideEvent(QHideEvent *);

private:
    QHBoxLayout* main_layout;

    commonimglstwidget* worm_resource_lst;
    commonimglstwidget* sample_lst;

    QComboBox* box;
    QLineEdit* sample_id_edit;
    QLabel* worm_preview;
    QLabel* sample_preview;

    QJsonObject current_resource;
    QJsonObject current_cats;

public:
    imagecomparewidget();
    ~imagecomparewidget();

    virtual QSize sizeHint() const;
    void setUpSubviews();
};

#endif // IMAGECOMPAREWIDGET_H
