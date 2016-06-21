#include "patientproxy.h"
#include <QtNetwork>

patientproxy::patientproxy() {
    http_connect = new QNetworkAccessManager(this);
    QObject::connect(http_connect,SIGNAL(finished(QNetworkReply*)), this, SLOT(replayFinished(QNetworkReply*)));
}

patientproxy::~patientproxy() {
    http_connect->deleteLater();
}


void patientproxy::pushPatient(const QString& patient_id, const QString& patient_name,
                                PatientGender gender, unsigned int age) {
    QUrl url = QString("http://localhost:9000/patient/push");

    QNetworkRequest request( url );
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json.insert("patient_id", patient_id);
    json.insert("patient_name", patient_name);
    json.insert("patient_gender", gender);
    json.insert("patient_age", (int)age);

    QJsonDocument document;
    document.setObject(json);
    QByteArray arr = document.toJson(QJsonDocument::Compact);

    QNetworkReply* http_replay = http_connect->post(request , arr);

    QObject::connect(http_replay, SIGNAL(error(QNetworkReply::NetworkError)),
                     this, SLOT(networkError(QNetworkReply::NetworkError)));
}

void patientproxy::updatePatient(const QString &patient_id, const QString &patient_name,
                                 PatientGender gender, unsigned int age) {
    QUrl url = QString("http://localhost:9000/patient/update");

    QNetworkRequest request( url );
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json.insert("patient_id", patient_id);
    json.insert("patient_name", patient_name);
    json.insert("patient_gender", gender);
    json.insert("patient_age", (int)age);

    QJsonDocument document;
    document.setObject(json);
    QByteArray arr = document.toJson(QJsonDocument::Compact);

    QNetworkReply* http_replay = http_connect->post(request , arr);

    QObject::connect(http_replay, SIGNAL(error(QNetworkReply::NetworkError)),
                     this, SLOT(networkError(QNetworkReply::NetworkError)));
}

void patientproxy::queryPatiendWithId(const QString& patient_id) {
    QUrl url = QString("http://localhost:9000/patient/query");

    QNetworkRequest request( url );
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json.insert("patient_id", patient_id);

    QJsonDocument document;
    document.setObject(json);
    QByteArray arr = document.toJson(QJsonDocument::Compact);

    QNetworkReply* http_replay = http_connect->post(request , arr);

    QObject::connect(http_replay, SIGNAL(error(QNetworkReply::NetworkError)),
                     this, SLOT(networkError(QNetworkReply::NetworkError)));
}

void patientproxy::replayFinished(QNetworkReply* result) {
    if (result->error() == 0) {
        QByteArray data = result->readAll();
        qDebug() << QString(data) << endl;

        QJsonDocument json = QJsonDocument::fromJson(data);
        if(json.isObject()) {
            QJsonObject obj = json.object();//Qt5新类
            if (obj.contains("method")) {
                QString method_name = obj["method"].toString();
                if (method_name == "pushPatient") {
                    QJsonObject result = obj["result"].toObject();
                    emit pushPatientSuccess(result);
                } else if (method_name == "queryPatientWithId") {
                    QJsonObject result = obj["result"].toObject();
                    emit queryPatientSuccess(result);
                }
             }
         }
    }
}

void patientproxy::networkError(QNetworkReply::NetworkError error) {
    qDebug() << error;
}
