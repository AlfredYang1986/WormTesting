#include "sampleproxy.h"
#include "fileoptproxy.h"
#include "proxymanager.h"
#include <iostream>
#include <QtGui>
using namespace std;

static const QString MethodKey_pushSample = "pushSample";

sampleproxy::sampleproxy() {
    http_connect = new QNetworkAccessManager(this);
    QObject::connect(http_connect,SIGNAL(finished(QNetworkReply*)), this, SLOT(replayFinished(QNetworkReply*)));
    file_proxy = proxymanager::instance()->getFileProxy();
    QObject::connect(file_proxy, SIGNAL(uploadSampleImageSuccess(const QString&, const QString&)),
                     this, SLOT(pushSampleImage(const QString&, const QString&)));
}

sampleproxy::~sampleproxy() {
    http_connect->deleteLater();
}

void pushSample(const QString& sample_id, const QString& patient_id = "",
                    const int status = -1, const QString& resource = "") {
    QUrl url = QString("http://localhost:9000/sample/push");

    QNetworkRequest request( url );
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json.insert("sample_id", sample_id);

    if (!patient_id.isEmpty())
        json.insert("patient_id", patient_id);

    if (status > 0)
        json.insert("status", status);

    if (!resource.isEmpty())
        json.insert("resource", resource);

    QJsonDocument document;
    document.setObject(json);
    QByteArray arr = document.toJson(QJsonDocument::Compact);

    QNetworkReply* http_replay = http_connect->post(request , arr);

    QObject::connect(http_replay, SIGNAL(error(QNetworkReply::NetworkError)),
                     this, SLOT(networkError(QNetworkReply::NetworkError)));
}


void sampleproxy::updateSample(const QString& sample_id, const QString& patient_id,
                  const int status, const QString& resource) {
    QUrl url = QString("http://localhost:9000/sample/update");

    QNetworkRequest request( url );
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json.insert("samplek_id", sample_id);

    if (!patient_id.isEmpty())
        json.insert("patient_id", patient_id);

    if (status > 0)
        json.insert("status", status);

    if (!resource.isEmpty())
        json.insert("resource", resource);

    QJsonDocument document;
    document.setObject(json);
    QByteArray arr = document.toJson(QJsonDocument::Compact);

    QNetworkReply* http_replay = http_connect->post(request , arr);

    QObject::connect(http_replay, SIGNAL(error(QNetworkReply::NetworkError)),
                     this, SLOT(networkError(QNetworkReply::NetworkError)));
}

void sampleproxy::pushSampleImage(const QString& sample_id, const QImage& image) {
    file_proxy->uploadSampleImage(sample_id, image);
}

void sampleproxy::pushSampleImage(const QString& sample_id, const QString& image_name) {
    QUrl url = QString("http://localhost:9000/sample/image/push");

    QNetworkRequest request( url );
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json.insert("sample_id", sample_id);
    json.insert("image", image_name);

    QJsonDocument document;
    document.setObject(json);
    QByteArray arr = document.toJson(QJsonDocument::Compact);

    QNetworkReply* http_replay = http_connect->post(request , arr);

    QObject::connect(http_replay, SIGNAL(error(QNetworkReply::NetworkError)),
                     this, SLOT(networkError(QNetworkReply::NetworkError)));
}

void sampleproxy::selectSampleImage(const QString& sample_id, const QString& image_name) {
    sample_id, image_name;
}

void sampleproxy::queryNotTestSample() {
    QUrl url = QString("http://localhost:9000/sample/query/nt");

    QNetworkRequest request( url );
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
//    json.insert("sample_id", sample_id);
//    json.insert("image", image_name);

    QJsonDocument document;
    document.setObject(json);
    QByteArray arr = document.toJson(QJsonDocument::Compact);

    QNetworkReply* http_replay = http_connect->post(request , arr);

    QObject::connect(http_replay, SIGNAL(error(QNetworkReply::NetworkError)),
                     this, SLOT(networkError(QNetworkReply::NetworkError)));
}

void sampleproxy::queryTestedSample() {
    QUrl url = QString("http://localhost:9000/sample/query/at");

    QNetworkRequest request( url );
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
//    json.insert("sample_id", sample_id);
//    json.insert("image", image_name);

    QJsonDocument document;
    document.setObject(json);
    QByteArray arr = document.toJson(QJsonDocument::Compact);

    QNetworkReply* http_replay = http_connect->post(request , arr);

    QObject::connect(http_replay, SIGNAL(error(QNetworkReply::NetworkError)),
                     this, SLOT(networkError(QNetworkReply::NetworkError)));
}

void sampleproxy::replayFinished(QNetworkReply* result) {
    if (result->error() == 0) {
        QByteArray data = result->readAll();
        qDebug() << QString(data) << endl;

        QJsonDocument json = QJsonDocument::fromJson(data);
        if(json.isObject()) {
            QJsonObject obj = json.object();
            if (obj.contains("method")) {
                QString method_name = obj["method"].toString();
                if (method_name == "queryNotTestSample") {
                    QJsonArray arr = obj["result"].toArray();
                    emit queryNotTestSampleSuccess(arr);
                } else if (method_name == "queryTestedSample") {
                    QJsonArray arr = obj["result"].toArray();
                    emit queryTestedSampleSuccess(arr);
                }
             }
         }
    }
}

void sampleproxy::networkError(QNetworkReply::NetworkError error) {
    qDebug() << error;
}