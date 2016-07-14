#ifndef AUTHPROXY_H
#define AUTHPROXY_H

#include <QObject>
#include <QtNetwork>

class authproxy : public QObject {
    Q_OBJECT

Q_SIGNALS:
    void loginSuccess();
//    void pushUserSuccess();
//    void popUserSuccess();

protected Q_SLOTS:
    void replayFinished(QNetworkReply*);
    void networkError(QNetworkReply::NetworkError);

public:
    enum AuthStatus {
        Auth_testing_doctor,
        Auth_post_test_doctor,
        Auth_admin,
        Auth_programer,
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

private:
    QString current_user_name;
    AuthStatus status;

    QNetworkAccessManager* http_connect;
};

#endif // AUTHPROXY_H
