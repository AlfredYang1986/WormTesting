#ifndef RESOURCEPROXY_H
#define RESOURCEPROXY_H

#include <QObject>
#include <QtNetwork>

class resourceproxy : public QObject {
    Q_OBJECT

Q_SIGNALS:
    void resourceImportStart();
    void resourceImportEnd();
    void resrouceImportProgress(double progress);

protected Q_SLOTS:
    void replayFinished(QNetworkReply*);
    void networkError(QNetworkReply::NetworkError);

    void pushSourceImageSuccess(const QString&);
    void pushWormCatSuccess();
    void pushWormSuccess(const QString&, const QString&);

    void uploadSampleImageSuccess(const QString & worm_name, const QString & img_name);
private:
    resourceproxy();
    static resourceproxy* _instance;

public:
    static resourceproxy* instance();
    ~resourceproxy();

    void fetchResources();
    void fetchResourcesAccImg(const QString& cat, const QString& name);
    void startResourceImport();
    void endResourceImport();
    int getFetchCount();

private:
    QNetworkAccessManager* http_connect;

    QString dir_name;
    QString txt_name;
    int count;
    int index;
};

#endif // RESOURCEPROXY_H
