#ifndef FILEOPTPROXY_H
#define FILEOPTPROXY_H

#include <QObject>
#include <QtNetwork>
#include <QtGui>
#include <QVector>

class fileoptproxy : public QObject {
    Q_OBJECT

private:
    QNetworkAccessManager* http_connect;
    QVector<QString> download_lst;
    bool isDownLoading;

    void downloadFileImpl(const QString& name);
Q_SIGNALS:
    void uploadSampleImageSuccess(const QString& sample_id, const QString& image_name);
    void downloadFileSuccess(const QByteArray&, const QString&);
    void downloadFileFailed();

protected Q_SLOTS:
    void replayFinished(QNetworkReply*);
    void networkError(QNetworkReply::NetworkError);

public:
    fileoptproxy();
    ~fileoptproxy();

    void uploadSampleImage(const QString& sample_id, const QImage& image);
    void downloadFile(const QString& name);
};

#endif // FILEOPTPROXY_H
