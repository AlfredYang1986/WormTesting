#include "wormproxy.h"

wormproxy::wormproxy() {
    http_connect = new QNetworkAccessManager(this);
    QObject::connect(http_connect,SIGNAL(finished(QNetworkReply*)), this, SLOT(replayFinished(QNetworkReply*)));
}

wormproxy::~wormproxy() {
    http_connect->deleteLater();
}

void wormproxy::pushWormCat(const QString &worm_cat_name) {
    QUrl url = QString("http://localhost:9000/worm/categories/push");

    QNetworkRequest request( url );
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json.insert("cat", worm_cat_name);

    QJsonDocument document;
    document.setObject(json);
    QByteArray arr = document.toJson(QJsonDocument::Compact);

    QNetworkReply* http_replay = http_connect->post(request , arr);

    QObject::connect(http_replay, SIGNAL(error(QNetworkReply::NetworkError)),
                     this, SLOT(networkError(QNetworkReply::NetworkError)));
}

void wormproxy::popWormCat(const QString &worm_cat_name) {
    QUrl url = QString("http://localhost:9000/worm/categories/pop");

    QNetworkRequest request( url );
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json.insert("cat", worm_cat_name);

    QJsonDocument document;
    document.setObject(json);
    QByteArray arr = document.toJson(QJsonDocument::Compact);

    QNetworkReply* http_replay = http_connect->post(request , arr);

    QObject::connect(http_replay, SIGNAL(error(QNetworkReply::NetworkError)),
                     this, SLOT(networkError(QNetworkReply::NetworkError)));
}

void wormproxy::queryWormCat(int take, int skip) {
    QUrl url = QString("http://localhost:9000/worm/categoies/query");

    QNetworkRequest request( url );
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
//    json.insert("take", take);
//    json.insert("skip", skip);

    QJsonDocument document;
    document.setObject(json);
    QByteArray arr = document.toJson(QJsonDocument::Compact);

    QNetworkReply* http_replay = http_connect->post(request , arr);

    QObject::connect(http_replay, SIGNAL(error(QNetworkReply::NetworkError)),
                     this, SLOT(networkError(QNetworkReply::NetworkError)));
}

void wormproxy::pushWorm(const QString& worm_name, const QString& worm_cat_name) {
    QUrl url = QString("http://localhost:9000/worm/push");

    QNetworkRequest request( url );
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json.insert("name", worm_name);
    json.insert("cat", worm_cat_name);

    QJsonDocument document;
    document.setObject(json);
    QByteArray arr = document.toJson(QJsonDocument::Compact);

    QNetworkReply* http_replay = http_connect->post(request , arr);

    QObject::connect(http_replay, SIGNAL(error(QNetworkReply::NetworkError)),
                     this, SLOT(networkError(QNetworkReply::NetworkError)));
}

void wormproxy::popWorm(const QString& worm_name, const QString& worm_cat_name) {
    QUrl url = QString("http://localhost:9000/worm/pop");

    QNetworkRequest request( url );
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json.insert("name", worm_name);
    json.insert("cat", worm_cat_name);

    QJsonDocument document;
    document.setObject(json);
    QByteArray arr = document.toJson(QJsonDocument::Compact);

    QNetworkReply* http_replay = http_connect->post(request , arr);

    QObject::connect(http_replay, SIGNAL(error(QNetworkReply::NetworkError)),
                     this, SLOT(networkError(QNetworkReply::NetworkError)));
}

void wormproxy::queryWorm(const QString& worm_name, const QString& worm_cat_name) {
    QUrl url = QString("http://localhost:9000/worm/query");

    QNetworkRequest request( url );
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json.insert("name", worm_name);
    json.insert("cat", worm_cat_name);

    QJsonDocument document;
    document.setObject(json);
    QByteArray arr = document.toJson(QJsonDocument::Compact);

    QNetworkReply* http_replay = http_connect->post(request , arr);

    QObject::connect(http_replay, SIGNAL(error(QNetworkReply::NetworkError)),
                     this, SLOT(networkError(QNetworkReply::NetworkError)));
}

void wormproxy::onlyWormCat() {
    QUrl url = QString("http://localhost:9000/worm/categoies/only");

    QNetworkRequest request( url );
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
//    json.insert("name", worm_name);
//    json.insert("cat", worm_cat_name);

    QJsonDocument document;
    document.setObject(json);
    QByteArray arr = document.toJson(QJsonDocument::Compact);

    QNetworkReply* http_replay = http_connect->post(request , arr);

    QObject::connect(http_replay, SIGNAL(error(QNetworkReply::NetworkError)),
                     this, SLOT(networkError(QNetworkReply::NetworkError)));
}

void wormproxy::changeSetting(const QString& worm, const QString& worm_cat, bool b) {
    QUrl url = QString("http://localhost:9000/worm/setting");

    QNetworkRequest request( url );
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json.insert("name", worm);
    json.insert("cat", worm_cat);
    if (b)
        json.insert("setting", 1);
    else
        json.insert("setting", 0);

    QJsonDocument document;
    document.setObject(json);
    QByteArray arr = document.toJson(QJsonDocument::Compact);

    QNetworkReply* http_replay = http_connect->post(request , arr);

    QObject::connect(http_replay, SIGNAL(error(QNetworkReply::NetworkError)),
                     this, SLOT(networkError(QNetworkReply::NetworkError)));
}

void wormproxy::queryReportingWorm() {
    QUrl url = QString("http://localhost:9000/worm/reporting");

    QNetworkRequest request( url );
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;

    QJsonDocument document;
    document.setObject(json);
    QByteArray arr = document.toJson(QJsonDocument::Compact);

    QNetworkReply* http_replay = http_connect->post(request , arr);

    QObject::connect(http_replay, SIGNAL(error(QNetworkReply::NetworkError)),
                     this, SLOT(networkError(QNetworkReply::NetworkError)));
}

void wormproxy::changeWromdescription(const QString &worm_name, const QString &des) {
    QUrl url = QString("http://localhost:9000/worm/description/update");

    QNetworkRequest request( url );
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json.insert("name", worm_name);
    json.insert("description", des);

    QJsonDocument document;
    document.setObject(json);
    QByteArray arr = document.toJson(QJsonDocument::Compact);

    QNetworkReply* http_replay = http_connect->post(request , arr);

    QObject::connect(http_replay, SIGNAL(error(QNetworkReply::NetworkError)),
                     this, SLOT(networkError(QNetworkReply::NetworkError)));
}

void wormproxy::pushWormImage(const QString &worm_name, const QString &image_name) {
    QUrl url = QString("http://localhost:9000/worm/images/push");

    QNetworkRequest request( url );
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json.insert("name", worm_name);
    json.insert("image", image_name);

    QJsonDocument document;
    document.setObject(json);
    QByteArray arr = document.toJson(QJsonDocument::Compact);

    QNetworkReply* http_replay = http_connect->post(request , arr);

    QObject::connect(http_replay, SIGNAL(error(QNetworkReply::NetworkError)),
                     this, SLOT(networkError(QNetworkReply::NetworkError)));
}

void wormproxy::popWormImage(const QString &worm_name, const QString &image_name) {
    QUrl url = QString("http://localhost:9000/worm/images/pop");

    QNetworkRequest request( url );
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json.insert("name", worm_name);
    json.insert("image", image_name);

    QJsonDocument document;
    document.setObject(json);
    QByteArray arr = document.toJson(QJsonDocument::Compact);

    QNetworkReply* http_replay = http_connect->post(request , arr);

    QObject::connect(http_replay, SIGNAL(error(QNetworkReply::NetworkError)),
                     this, SLOT(networkError(QNetworkReply::NetworkError)));
}

void wormproxy::replayFinished(QNetworkReply* result) {
    if (result->error() == 0) {
        QByteArray data = result->readAll();
        qDebug() << QString(data) << endl;

        QJsonDocument json = QJsonDocument::fromJson(data);
        if(json.isObject()) {
            QJsonObject obj = json.object();
            if (obj.contains("method")) {
                QString method_name = obj["method"].toString();
                if (method_name == "wormCategories") {
                    QJsonObject tmp = obj["result"].toObject();
                    emit queryWormCatSuccess(tmp);
                } else if (method_name == "queryWorm") {
                    QJsonObject tmp = obj["result"].toObject();
                    emit queryWormSuccess(tmp);
                } else if (method_name == "pushWormCategory") {
                    emit pushWormCatSuccess();
                } else if (method_name == "popWormCategory") {
                    emit popWormCatSuccess();
                } else if (method_name == "pushWorm") {
                    QJsonObject tmp = obj["result"].toObject();
                    emit pushWormSuccess();
                    emit pushWormSuccess(tmp["cat"].toString(), tmp["name"].toString());
                } else if (method_name == "popWorm") {
                    emit popWormSuccess();
                } else if (method_name == "onlyCategories") {
                    QJsonArray tmp = obj["result"].toArray();
                    emit onlyWormCatSuccess(tmp);
                } else if (method_name == "wormSettingQuery") {
                    QJsonObject tmp = obj["result"].toObject();
                    emit queryReportingWormSuccess(tmp);
                } else if (method_name == "pushWormImage") {
                    QJsonObject tmp = obj["result"].toObject();
                    QString name = tmp["name"].toString();
                    emit pushWormImageSuccess(name);
                } else if (method_name == "popWormImage") {
                    QJsonObject tmp = obj["result"].toObject();
                    QString name = tmp["name"].toString();
                    emit popWormImageSuccess(name);
                }
             }
         }
    }
}

void wormproxy::networkError(QNetworkReply::NetworkError error) {
    qDebug() << error;
    QObject::sender()->deleteLater();
}
