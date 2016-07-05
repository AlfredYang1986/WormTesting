#ifndef COMMONIMGLSTWIDGET_H
#define COMMONIMGLSTWIDGET_H

#include <QFrame>
#include <QVector>

class QVBoxLayout;
class QLabel;

class commonimglstwidget : public QFrame {
    Q_OBJECT

protected Q_SLOTS:
    void downloadFileSuccess(const QByteArray&);

    void deleteImageStart(const QString&);
    void deleteImageSuccess(const QString &, const QString &);

protected:
    virtual void showEvent (QShowEvent* event);
    virtual void hideEvent(QHideEvent *event);

private:
    QVBoxLayout* main_layout;

    QString sample_id;
    QVector<QString> img_name_lst;
    QVector<QLabel*> img_lst;

    QString current_download_name;

    void moveToNextImage();
    void clearLabels();
public:
    commonimglstwidget();
    ~commonimglstwidget();

    void setUpSubviews();

    virtual QSize sizeHint() const;

    void changeCurrentSample(const QJsonObject& sample);
    bool prePushImage();
    void pushImageName(const QString& name);
};

#endif // COMMONIMGLSTWIDGET_H
