#ifndef CAMERAPROXY_H
#define CAMERAPROXY_H

#include <QObject>
class CvCapture;
class QTimer;

class cameraproxy : public QObject {
    Q_OBJECT

Q_SIGNALS:
    void stream(const QImage&);

protected Q_SLOTS:
    void readFarme();

private:
    CvCapture* p;
    QTimer* timer;
    bool canTakePic;

    static cameraproxy* _instance;

    cameraproxy();
public:
    static cameraproxy* instance();
    ~cameraproxy();

    void setUpCamera();
    void startTesting();
    void endTesting();

    QImage* takeImage();
};

#endif // CAMERAPROXY_H
