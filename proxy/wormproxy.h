#ifndef WORMPROXY_H
#define WORMPROXY_H

#include <QObject>
#include <QtNetwork>

class wormproxy : public QObject {
    Q_OBJECT

private:
    QNetworkAccessManager* http_connect;

Q_SIGNALS:
    void queryWormCatSuccess(const QJsonObject&);
    void queryWormSuccess(const QJsonObject&);

    void pushWormCatSuccess();
    void pushWormSuccess();
    void popWormCatSuccess();
    void popWormSuccess();
    void onlyWormCatSuccess(const QJsonArray&);

    void queryReportingWormSuccess(const QJsonObject&);

public Q_SLOTS:
    void replayFinished(QNetworkReply*);
    void networkError(QNetworkReply::NetworkError);

public:
    wormproxy();
    ~wormproxy();

    void onlyWormCat();
    void pushWormCat(const QString& worm_cat_name);
    void popWormCat(const QString& worm_cat_name);
    void queryWormCat(int take = 10, int skip = 0);

    void pushWorm(const QString& worm_name, const QString& worm_cat_name);
    void popWorm(const QString& worm_name, const QString& worm_cat_name);
    void queryWorm(const QString& worm_name, const QString& worm_cat_name);

    void changeSetting(const QString& worm, const QString& worm_cat, bool b);

    void queryReportingWorm();
};

#endif // WORMPROXY_H
