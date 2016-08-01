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
    int current_index;
    CvCapture* p;
    QTimer* timer;
    bool canTakePic;

    static cameraproxy* _instance;

    cameraproxy();
public:
    static cameraproxy* instance();
    ~cameraproxy();

    void setUpCamera(int index = 0);
    void startTesting(int index = 0);
    void endTesting();
    void releaseCamera();

    QImage* takeImage();
};

#endif // CAMERAPROXY_H
