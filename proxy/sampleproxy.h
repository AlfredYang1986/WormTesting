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
    void pushSampleSuccess(const QJsonObject& data);
    void updateSampleSuccess(const QJsonObject& data);
    void queryNotTestSampleSuccess(const QJsonArray& samples);
    void queryTestedSampleSuccess(const QJsonArray& samples);
    void querySampleWithIDSuccess(const QJsonObject& samples);

    void sampleConditionSearchSuccess(const QJsonArray&);

    void popSampleImageSuccess(const QString &, const QString &);

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

    void pushOrUpdateSample(const QJsonObject& sample);

    void pushSample(const QString& sample_id, const QString& patient_id = "",
                    const int status = -1, const QString& resource = "");
    void updateSample(const QString& sample_id, const QString& patient = "",
                      const int status = -1, const QString& resource = "");
    void pushSampleImage(const QString& sample_id, const QImage& image);
    void selectSampleImage(const QString& sample_id, const QString& image_name);

    void queryNotTestSample();
    void queryTestedSample();
    void querySampleWithID(const QString& sample_id);

    void popSampleImage(const QString& sample_id, const QString& img_name);

    void sampleTestComplished(const QString& sample_id);

    void pushReportingTestResult(const QString& sample_id, const QVector<QString>& result);

    void searchSamplesWithConditions(const QJsonObject& conditions);
};

#endif // SAMPLEMODULE_H
