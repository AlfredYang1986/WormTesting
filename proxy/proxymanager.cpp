#include "proxymanager.h"
#include "fileoptproxy.h"
#include "sampleproxy.h"
#include "wormproxy.h"
#include "patientproxy.h"
#include "configproxy.h"
#include "authproxy.h"

proxymanager* proxymanager::_instance;

proxymanager::proxymanager()
    : file_proxy(0), patient_proxy(0)
    , sample_proxy(0), worm_proxy(0)
    , config_proxy(0), auth_proxy(0) {

}

proxymanager::~proxymanager() {
    if (file_proxy) file_proxy->deleteLater();
    if (patient_proxy) patient_proxy->deleteLater();
    if (sample_proxy) sample_proxy->deleteLater();
    if (worm_proxy) worm_proxy->deleteLater();
    if (config_proxy) config_proxy->deleteLater();
}

proxymanager* proxymanager::instance() {
    if (!_instance) {
        _instance = new proxymanager();
    }
    return _instance;
}

fileoptproxy* proxymanager::getFileProxy() {
    if (!file_proxy)
        file_proxy = new fileoptproxy;
    return file_proxy;
}

patientproxy* proxymanager::getPatientProxy() {
    if (!patient_proxy)
        patient_proxy = new patientproxy;
    return patient_proxy;
}

sampleproxy* proxymanager::getSampleProxy() {
    if (!sample_proxy)
        sample_proxy = new sampleproxy;
    return sample_proxy;
}

wormproxy* proxymanager::getWormProxy() {
    if (!worm_proxy)
        worm_proxy = new wormproxy;
    return worm_proxy;
}

configproxy* proxymanager::getConfigProxy() {
    if (!config_proxy)
        config_proxy = new configproxy;
    return config_proxy;
}

authproxy* proxymanager::getAuthProxy() {
    if (!auth_proxy)
        auth_proxy = new authproxy;
    return auth_proxy;
}
