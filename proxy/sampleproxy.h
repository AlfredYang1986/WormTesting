#ifndef SAMPLEMODULE_H
#define SAMPLEMODULE_H

#include <QObject>
#include <QtNetwork>

class QNetworkAccessManager;
class QNetworkReply;
class fileoptproxy;

class sampleproxy : public QObject {
    Q_OBJECT

Q_SIGNALS:
    void error(const QString& error_message);
    void pushSampleSuccess(const QString& sample_id, const QJsonObject& data);
    void updateSampleSuccess(const QString& sample_id, const QJsonObject& data);

    void queryNotTestSampleSuccess(const QJsonArray& samples);
    void queryTestedSampleSuccess(const QJsonArray& samples);

protected Q_SLOTS:
    void pushSampleImage(const QString& sample_id, const QString& image_name);

private:
    QNetworkAccessManager* http_connect;
    fileoptproxy* file_proxy;

protected Q_SLOTS:
    void replayFinished(QNetworkReply*);
    void networkError(QNetworkReply::NetworkError);

public:
    sampleproxy();
    ~sampleproxy();

    void pushSample(const QString& sample_id, const QString& patient_id = "",
                    const int status = -1, const QString& resource = "");
    void updateSample(const QString& sample_id, const QString& patient = "",
                      const int status = -1, const QString& resource = "");
    void pushSampleImage(const QString& sample_id, const QImage& image);
    void selectSampleImage(const QString& sample_id, const QString& image_name);

    void queryNotTestSample();
    void queryTestedSample();
};

#endif // SAMPLEMODULE_H