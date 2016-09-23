#include "authproxy.h"
#include <QMessageBox>

authproxy::authproxy() : isNeedRemoteNormalDoctors(true), isNeedRemoteAdjustDoctors(true), status(Auth_no_body), current_user_name("") {
    http_connect = new QNetworkAccessManager(this);
    QObject::connect(http_connect,SIGNAL(finished(QNetworkReply*)), this, SLOT(replayFinished(QNetworkReply*)));

    normal_doctors.clear();
    adjust_doctors.clear();
}

authproxy::~authproxy() {

}

void authproxy::signOutCurrentUser() {
    this->current_user_name = "";
    this->status = Auth_no_body;
    emit signoutSuccess();
}

void authproxy::login(const QString &user_name, const QString &password) {
    QUrl url = QString("http://localhost:9000/auth/login");

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json.insert("user_name", user_name);
    json.insert("password", password);

    QJsonDocument document;
    document.setObject(json);
    QByteArray arr = document.toJson(QJsonDocument::Compact);

    QNetworkReply* http_replay = http_connect->post(request , arr);

    QObject::connect(http_replay, SIGNAL(error(QNetworkReply::NetworkError)),
                     this, SLOT(networkError(QNetworkReply::NetworkError)));
}

void authproxy::pushUser(const QString &user_name, const QString &password, AuthStatus s) {
    QUrl url = QString("http://localhost:9000/auth/register");

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json.insert("user_name", user_name);
    json.insert("password", password);
    json.insert("auth", s);

    QJsonDocument document;
    document.setObject(json);
    QByteArray arr = document.toJson(QJsonDocument::Compact);

    QNetworkReply* http_replay = http_connect->post(request , arr);

    QObject::connect(http_replay, SIGNAL(error(QNetworkReply::NetworkError)),
                     this, SLOT(networkError(QNetworkReply::NetworkError)));
}

void authproxy::popUser(const QString &user_name) {
    QUrl url = QString("http://localhost:9000/auth/pop");

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json.insert("user_name", user_name);

    QJsonDocument document;
    document.setObject(json);
    QByteArray arr = document.toJson(QJsonDocument::Compact);

    QNetworkReply* http_replay = http_connect->post(request , arr);

    QObject::connect(http_replay, SIGNAL(error(QNetworkReply::NetworkError)),
                     this, SLOT(networkError(QNetworkReply::NetworkError)));
}

void authproxy::changeUserStatus(const QString &user_name, AuthStatus s) {
    QUrl url = QString("http://localhost:9000/auth/change/status");

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json.insert("user_name", user_name);
    json.insert("auth", s);

    QJsonDocument document;
    document.setObject(json);
    QByteArray arr = document.toJson(QJsonDocument::Compact);

    QNetworkReply* http_replay = http_connect->post(request , arr);

    QObject::connect(http_replay, SIGNAL(error(QNetworkReply::NetworkError)),
                     this, SLOT(networkError(QNetworkReply::NetworkError)));
}

void authproxy::changePassword(const QString &password) {
    QUrl url = QString("http://localhost:9000/auth/change/password");

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json.insert("user_name", current_user_name);
    json.insert("password", password);

    QJsonDocument document;
    document.setObject(json);
    QByteArray arr = document.toJson(QJsonDocument::Compact);

    QNetworkReply* http_replay = http_connect->post(request , arr);

    QObject::connect(http_replay, SIGNAL(error(QNetworkReply::NetworkError)),
                     this, SLOT(networkError(QNetworkReply::NetworkError)));
}

void authproxy::lstNormalDoctorsRemote() {
    if (this->isNeedRemoteNormalDoctors) {
        QUrl url = QString("http://localhost:9000/auth/doctors/lst");

        QNetworkRequest request(url);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        QJsonObject json;
        json.insert("auth", 0);

        QJsonDocument document;
        document.setObject(json);
        QByteArray arr = document.toJson(QJsonDocument::Compact);

        QNetworkReply* http_replay = http_connect->post(request , arr);

        QObject::connect(http_replay, SIGNAL(error(QNetworkReply::NetworkError)),
                         this, SLOT(networkError(QNetworkReply::NetworkError)));
    } else {
        emit this->queryNormalDoctorSuccess(this->normal_doctors);
    }
}

void authproxy::lstTestedDoctorsRemote() {
    if (this->isNeedRemoteAdjustDoctors) {

        QUrl url = QString("http://localhost:9000/auth/doctors/lst");

        QNetworkRequest request(url);
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        QJsonObject json;
        json.insert("auth", 1);

        QJsonDocument document;
        document.setObject(json);
        QByteArray arr = document.toJson(QJsonDocument::Compact);

        QNetworkReply* http_replay = http_connect->post(request , arr);

        QObject::connect(http_replay, SIGNAL(error(QNetworkReply::NetworkError)),
                     this, SLOT(networkError(QNetworkReply::NetworkError)));
    } else {
        emit this->queryAdjustDoctorSuccess(this->adjust_doctors);
    }

}

QVector<QString> authproxy::lstNormalDoctors() {
    return normal_doctors;
}

QVector<QString> authproxy::lstTestedDoctors() {
    return adjust_doctors;
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
                if (method_name == "login") {
                    QJsonObject tmp = obj["result"].toObject();
                    current_user_name = tmp["user_name"].toString();
                    status = (authproxy::AuthStatus)tmp["auth"].toInt();
                    emit loginSuccess();

                } else if (method_name =="queryPatientType") {

                } else if (method_name == "lstDoctor") {
//                    int auth = obj["auth"];
                    if (obj["auth"] == 0) {
                        this->isNeedRemoteNormalDoctors = false;
                        normal_doctors.clear();
                        QJsonArray arr = obj["result"].toArray();
                        QJsonArray::iterator iter = arr.begin();
                        for (; iter != arr.end(); ++iter) {
                            QString tmp = (*iter).toString();
                            normal_doctors.push_back(tmp);
                        }
                    } else {
                        this->isNeedRemoteAdjustDoctors = false;
                        adjust_doctors.clear();
                        QJsonArray arr = obj["result"].toArray();
                        QJsonArray::iterator iter = arr.begin();
                        for (; iter != arr.end(); ++iter) {
                            QString tmp = (*iter).toString();
                            adjust_doctors.push_back(tmp);
                        }
                    }
                }
            }
         }
    } else {
        QMessageBox::warning(NULL, "Error",
                             QStringLiteral("访问数据库操作失败"),
                             QMessageBox::Ok, QMessageBox::Ok);
    }
}

void authproxy::networkError(QNetworkReply::NetworkError error) {
    qDebug() << error << endl;
    QMessageBox::warning(NULL, "Error",
                         QStringLiteral("访问数据库操作失败"),
                         QMessageBox::Ok, QMessageBox::Ok);
    QObject::sender()->deleteLater();
}

authproxy::AuthStatus authproxy::currentAuthStatus() const {
    return status;
}

void authproxy::setNeedRemoteLstDectro(bool b) {
    isNeedRemoteAdjustDoctors = b;
    isNeedRemoteNormalDoctors = b;
}
