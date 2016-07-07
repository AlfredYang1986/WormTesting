#ifndef COMMONIMGLSTWIDGET_H
#define COMMONIMGLSTWIDGET_H

#include <QFrame>
#include <QVector>

class QVBoxLayout;
class QLabel;

class commonimglstwidget : public QFrame {
    Q_OBJECT

Q_SIGNALS:
    void changeCurrentImageSignal(const QPixmap&);

protected Q_SLOTS:
    void downloadFileSuccess(const QByteArray&);

    void deleteImageStart(const QString&);
    void deleteImageSuccess(const QString &, const QString &);

    void changeCurrentImage(const QPixmap*);

protected:
    virtual void showEvent (QShowEvent* event);
    virtual void hideEvent(QHideEvent *event);

private:
    QVBoxLayout* main_layout;

    QString sample_id;
    QVector<QString> img_name_lst;
    QVector<QLabel*> img_lst;

    QString current_download_name;

    const bool isWormSample;

    void moveToNextImage();
    void clearLabels();
public:
    commonimglstwidget(bool w = false);
    ~commonimglstwidget();

    void setUpSubviews();

    virtual QSize sizeHint() const;

    void changeCurrentSample(const QJsonObject& sample);
    bool prePushImage();
    void pushImageName(const QString& name);

    // only for sample pic
    void changeShowingImgLst(const QVector<QString>& name_lst);

    bool showOptBtns() const;
};

#endif // COMMONIMGLSTWIDGET_H