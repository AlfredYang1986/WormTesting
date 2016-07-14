#include "authproxy.h"

authproxy::authproxy() {

}

authproxy::~authproxy() {

}

void authproxy::login(const QString &user_name, const QString &password) {
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

void authproxy::pushUser(const QString &user_name, const QString &password, AuthStatus s) {
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

void authproxy::popUser(const QString &user_name) {
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

void authproxy::changeUserStatus(const QString &user_name, AuthStatus s) {
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

void authproxy::changePassword(const QString &password) {
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

void authproxy::replayFinished(QNetworkReply * result) {
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

void authproxy::networkError(QNetworkReply::NetworkError error) {
    qDebug() << error << endl;
    QMessageBox::warning(NULL, "Error",
                         tr("访问数据库操作失败"),
                         QMessageBox::Ok, QMessageBox::Ok);
    QObject::sender()->deleteLater();
}
