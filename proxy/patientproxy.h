#ifndef PATIENTPROXY_H
#define PATIENTPROXY_H

#include <QObject>
#include <QtNetwork>

class patientproxy : public QObject {
    Q_OBJECT

public:
    enum PatientGender {
        male,
        female
    };
    Q_ENUM(PatientGender);

Q_SIGNALS:
    void error(const QString& error_message);
    void pushPatientSuccess(const QJsonObject& patient);
    void queryPatientSuccess(const QJsonObject& patient);

private:
    QNetworkAccessManager* http_connect;

public:
    patientproxy();
    ~patientproxy();

    void pushPatient(const QString& patient_id, const QString& patient_name,
                     PatientGender gender, unsigned int age);
    void updatePatient(const QString& patient_id, const QString& patient_name,
                       PatientGender gender, unsigned int age);
    void queryPatiendWithId(const QString& patient_id);

protected Q_SLOTS:
    void replayFinished(QNetworkReply*);
    void networkError(QNetworkReply::NetworkError);
};

#endif // PATIENTPROXY_H
