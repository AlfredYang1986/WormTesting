#include "configproxy.h"
#include <QtNetwork>
#include <QDebug>
#include <QMessageBox>

configproxy::configproxy() {
    http_connect = new QNetworkAccessManager(this);
    QObject::connect(http_connect,SIGNAL(finished(QNetworkReply*)), this, SLOT(replayFinished(QNetworkReply*)));
}

configproxy::~configproxy() {

}

void configproxy::addSampleResourceType(const QString & resource) {
    QUrl url = QString("http://localhost:9000/config/resource/push");

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json.insert("resource", resource);

    QJsonDocument document;
    document.setObject(json);
    QByteArray arr = document.toJson(QJsonDocument::Compact);

    QNetworkReply* http_replay = http_connect->post(request , arr);

    QObject::connect(http_replay, SIGNAL(error(QNetworkReply::NetworkError)),
                     this, SLOT(networkError(QNetworkReply::NetworkError)));
}

void configproxy::deleteSampleResourceType(const QString & resource) {
    QUrl url = QString("http://localhost:9000/config/resource/pop");

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json.insert("resource", resource);

    QJsonDocument document;
    document.setObject(json);
    QByteArray arr = document.toJson(QJsonDocument::Compact);

    QNetworkReply* http_replay = http_connect->post(request , arr);

    QObject::connect(http_replay, SIGNAL(error(QNetworkReply::NetworkError)),
                     this, SLOT(networkError(QNetworkReply::NetworkError)));
}

void configproxy::querySampleResourceType() {
    QUrl url = QString("http://localhost:9000/config/resource/query");

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
//    json.insert("resource", resource);

    QJsonDocument document;
    document.setObject(json);
    QByteArray arr = document.toJson(QJsonDocument::Compact);

    QNetworkReply* http_replay = http_connect->post(request , arr);

    QObject::connect(http_replay, SIGNAL(error(QNetworkReply::NetworkError)),
                     this, SLOT(networkError(QNetworkReply::NetworkError)));
}

void configproxy::addPatientType(const QString& pt) {
    QUrl url = QString("http://localhost:9000/config/patient/push");

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json.insert("patient", pt);

    QJsonDocument document;
    document.setObject(json);
    QByteArray arr = document.toJson(QJsonDocument::Compact);

    QNetworkReply* http_replay = http_connect->post(request , arr);

    QObject::connect(http_replay, SIGNAL(error(QNetworkReply::NetworkError)),
                     this, SLOT(networkError(QNetworkReply::NetworkError)));
}

void configproxy::deletePatientType(const QString& pt) {
    QUrl url = QString("http://localhost:9000/config/patient/pop");

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json.insert("patient", pt);

    QJsonDocument document;
    document.setObject(json);
    QByteArray arr = document.toJson(QJsonDocument::Compact);

    QNetworkReply* http_replay = http_connect->post(request , arr);

    QObject::connect(http_replay, SIGNAL(error(QNetworkReply::NetworkError)),
                     this, SLOT(networkError(QNetworkReply::NetworkError)));
}

void configproxy::queryPatientType() {
    QUrl url = QString("http://localhost:9000/config/patient/query");

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
//    json.insert("patient", pt);

    QJsonDocument document;
    document.setObject(json);
    QByteArray arr = document.toJson(QJsonDocument::Compact);

    QNetworkReply* http_replay = http_connect->post(request , arr);

    QObject::connect(http_replay, SIGNAL(error(QNetworkReply::NetworkError)),
                     this, SLOT(networkError(QNetworkReply::NetworkError)));
}

void configproxy::replayFinished(QNetworkReply * result) {
    if (result->error() == 0) {
        QByteArray data = result->readAll();
        qDebug() << QString(data) << endl;

        QJsonDocument json = QJsonDocument::fromJson(data);
        if(json.isObject()) {
            QJsonObject obj = json.object();
            if (obj.contains("method")) {
                QString method_name = obj["method"].toString();
                if (method_name == "queryResourceType") {
                    QJsonArray arr = obj["result"].toArray();
                    emit querySampleResourceTypeSuccess(arr);
                } else if (method_name =="queryPatientType") {
                    QJsonArray arr = obj["result"].toArray();
                    emit queryPatientTypeSuccess(arr);
                }
            }
         }
    } else {
        QMessageBox::warning(NULL, "Error",
                             tr("访问数据库操作失败"),
                             QMessageBox::Ok, QMessageBox::Ok);
    }
}

void configproxy::networkError(QNetworkReply::NetworkError error) {
    qDebug() << error << endl;
    QMessageBox::warning(NULL, "Error",
                         tr("访问数据库操作失败"),
                         QMessageBox::Ok, QMessageBox::Ok);
    QObject::sender()->deleteLater();
}
