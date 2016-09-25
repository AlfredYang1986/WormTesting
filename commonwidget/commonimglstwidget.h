#ifndef COMMONIMGLSTWIDGET_H
#define COMMONIMGLSTWIDGET_H

#include <QFrame>
#include <QVector>

class QBoxLayout;
class QLabel;
class imglstitem;

class commonimglstwidget : public QFrame {
    Q_OBJECT

Q_SIGNALS:
    void changeCurrentImageSignal(const QPixmap&);

protected Q_SLOTS:
    void downloadFileSuccess(const QByteArray&, const QString&);

    void deleteImageStart(const QString&);
    void deleteImageSuccess(const QString &, const QString &);
    void deleteImageFailed();

    void changeCurrentImage(const QPixmap*);

    void canSelectedMore(bool*);

protected:
    virtual void showEvent (QShowEvent* event);
    virtual void hideEvent(QHideEvent *event);

private:
    QBoxLayout* main_layout;

    QString sample_id;
    QVector<QString> img_name_lst;
    QVector<imglstitem*> img_lst;

    QString current_download_name;

    const bool isWormSample;
    const bool isVer;
    const bool select_able;

    void moveToNextImage();
    void clearLabels();
public:
    commonimglstwidget(bool w = false, bool v = true, bool s = false);
    ~commonimglstwidget();

    void setUpSubviews();
//    void setUpSubviews2();

    virtual QSize sizeHint() const;

    void changeCurrentSample(const QJsonObject& sample);
    bool prePushImage();
    void pushImageName(const QString& name);

    // only for sample pic
    void changeShowingImgLst(const QVector<QString>& name_lst);

    bool showOptBtns() const;

    QVector<QImage> getCurrentImages() const;
    QVector<QImage> getCurrentSelectedImages() const;
    int getCurrentSelectedImageCount() const;
};

#endif // COMMONIMGLSTWIDGET_H
