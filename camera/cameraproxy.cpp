#include "cameraproxy.h"

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <QTimer>
#include <iostream>
#include <QImage>
#include <QTime>
#include <QCoreApplication>
#include "qtipl.hpp"
using namespace cv;


#define FAILURE_CHECK(p, x)      \
  assert(p);                     \
  if (p == NULL)                 \
  {                              \
    std::cerr << x << std::endl; \
    exit(EXIT_FAILURE);          \
  }

cameraproxy* cameraproxy::_instance;

cameraproxy* cameraproxy::instance() {
    if (!_instance) {
        _instance = new cameraproxy;
    }
    return _instance;
}

cameraproxy::cameraproxy()
    : p(NULL), canTakePic(false) {
//    this->setUpCamera();
}

cameraproxy::~cameraproxy() {
    if (p) {
        this->releaseCamera();
        timer->deleteLater();
    }
}

void cameraproxy::setUpCamera(int index) {

    if (p) {
        this->releaseCamera();
        disconnect(timer, SIGNAL(timeout()), this, SLOT(readFarme()));
        timer->deleteLater();
        QTime t;
        t.start();
        while(t.elapsed() < 500)
            QCoreApplication::processEvents();
    }

    p = cvCaptureFromCAM(index);
    FAILURE_CHECK(p, "Init Capture Failed");
    current_index = index;

    QTime t;
    t.start();
    while(t.elapsed() < 500)
        QCoreApplication::processEvents();

    if (!cvGrabFrame(p)) {
        std::cerr << "Conldn't GrabFrame" << std::endl;
        exit(EXIT_FAILURE);
    }

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(readFarme()));
}

void cameraproxy::releaseCamera() {
    if (p) {
        cvReleaseCapture(&p);
        p = NULL;
    }
}

void cameraproxy::readFarme() {
    IplImage* frame = cvQueryFrame(p);

    uchar *data;
    if (frame) {
        QImage *qImage = IplImageToQImage(frame, &data);
        emit stream(*qImage);
        delete qImage;
        free(data);
    } else {
        this->setUpCamera();
        this->readFarme();
    }
}

QImage* cameraproxy::takeImage() {
    if (canTakePic) {
        IplImage* frame = cvQueryFrame(p);
        uchar *data;
        QImage* reVal = IplImageToQImage(frame, &data);
        //free(data);
        return reVal;
    } else {
        return NULL;
    }
}

void cameraproxy::startTesting(int index) {

    if (!p)
        this->setUpCamera(index);

    timer->start(33);
    canTakePic = true;
}

void cameraproxy::endTesting() {
    if (p) {
        timer->stop();
        canTakePic = false;
        this->releaseCamera();
    }
}
