#ifndef CONFIGPROXY_H
#define CONFIGPROXY_H

#include <QObject>
#include <QtNetwork>

class configproxy : public QObject {
    Q_OBJECT

Q_SIGNALS:
    void querySampleResourceTypeSuccess(const QJsonArray&);
    void queryPatientTypeSuccess(const QJsonArray&);

protected Q_SLOTS:
    void replayFinished(QNetworkReply*);
    void networkError(QNetworkReply::NetworkError);

private:
    QNetworkAccessManager* http_connect;

public:
    configproxy();
    ~configproxy();

    void addSampleResourceType(const QString&);
    void deleteSampleResourceType(const QString&);
    void querySampleResourceType();

    void addPatientType(const QString&);
    void deletePatientType(const QString&);
    void queryPatientType();
};

#endif // CONFIGPROXY_H
