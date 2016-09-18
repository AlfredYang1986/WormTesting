#ifndef AUTHPROXY_H
#define AUTHPROXY_H

#include <QObject>
#include <QtNetwork>
#include <QJsonObject>

class authproxy : public QObject {
    Q_OBJECT

Q_SIGNALS:
    void loginSuccess();
    void queryNormalDoctorSuccess(const QVector<QString>&);
    void queryAdjustDoctorSuccess(const QVector<QString>&);
//    void pushUserSuccess();
//    void popUserSuccess();

protected Q_SLOTS:
    void replayFinished(QNetworkReply*);
    void networkError(QNetworkReply::NetworkError);

public:
    enum AuthStatus {
        Auth_testing_doctor = 0,
        Auth_post_test_doctor = 1,
        Auth_programer = 3,
        Auth_admin = 99,
    };
    Q_ENUM(AuthStatus);

public:
    authproxy();
    ~authproxy();

    void login(const QString& user_name, const QString& password);
    void pushUser(const QString& user_name, const QString& password, AuthStatus s);
    void popUser(const QString& user_name);
    void changeUserStatus(const QString& user_name, AuthStatus s);
    void changePassword(const QString& password);

    QVector<QString> lstNormalDoctors();
    QVector<QString> lstTestedDoctors();

    void lstNormalDoctorsRemote();
    void lstTestedDoctorsRemote();

    AuthStatus currentAuthStatus() const;
//    bool isNeedRemoteLstDector() const;
    void setNeedRemoteLstDectro(bool);

    QString current_user_name;
private:
    AuthStatus status;

    QNetworkAccessManager* http_connect;

    QVector<QString> normal_doctors;
    QVector<QString> adjust_doctors;

    bool isNeedRemoteNormalDoctors;
    bool isNeedRemoteAdjustDoctors;
};

#endif // AUTHPROXY_H
