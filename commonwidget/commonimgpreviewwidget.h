#ifndef COMMONIMGPREVIEWWIDGET_H
#define COMMONIMGPREVIEWWIDGET_H

#include <QLabel>
#include <QFrame>
#include <QHBoxLayout>

class commonimgpreviewwidget : public QFrame /*QLabel*/ {
    Q_OBJECT

protected Q_SLOTS:
    void downloadFileSuccess(const QByteArray&, const QString&);
    void setPreviewImage(const QPixmap&);

public:
    commonimgpreviewwidget();
    ~commonimgpreviewwidget();

    void fillImages(const QJsonObject& sample);

protected:
    virtual void showEvent(QShowEvent*);
    virtual void hideEvent(QHideEvent *);

    float layoutContent();
private:
    QString current_img_name;
    QLabel* content;
};

#endif // COMMONIMGPREVIEWWIDGET_H
