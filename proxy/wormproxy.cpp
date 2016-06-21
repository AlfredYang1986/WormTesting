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
    QUrl url = QString("http://localhost:9000/worm/categories/query");

    QNetworkRequest request( url );
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json.insert("take", take);
    json.insert("skip", skip);

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

void wormproxy::queryWorm(const QString& worm_cat_name) {
    QUrl url = QString("http://localhost:9000/worm/query");

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

void wormproxy::replayFinished(QNetworkReply* result) {
    if (result->error() == 0) {
        QByteArray data = result->readAll();
        qDebug() << QString(data) << endl;
    }
}

void wormproxy::networkError(QNetworkReply::NetworkError error) {
    qDebug() << error;
}