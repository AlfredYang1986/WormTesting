#ifndef PROXYMANAGER_H
#define PROXYMANAGER_H

#include <QObject>

class fileoptproxy;
class patientproxy;
class sampleproxy;
class wormproxy;
class configproxy;

class proxymanager : public QObject {
    Q_OBJECT

private:
    proxymanager();

    static proxymanager* _instance;

    fileoptproxy* file_proxy;
    patientproxy* patient_proxy;
    sampleproxy* sample_proxy;
    wormproxy* worm_proxy;
    configproxy* config_proxy;
public:
    static proxymanager* instance();
    ~proxymanager();

    fileoptproxy* getFileProxy();
    patientproxy* getPatientProxy();
    sampleproxy* getSampleProxy();
    wormproxy* getWormProxy();
    configproxy* getConfigProxy();
};

#endif // PROXYMANAGER_H
