#ifndef COMMONIMGPREVIEWWIDGET_H
#define COMMONIMGPREVIEWWIDGET_H

#include <QLabel>

class commonimgpreviewwidget : public QLabel {
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

private:
    QString current_img_name;
};

#endif // COMMONIMGPREVIEWWIDGET_H
