#include "cameraproxy.h"

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <QTimer>
#include <iostream>
#include <QImage>
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
    : canTakePic(false) {
    this->setUpCamera();
}

cameraproxy::~cameraproxy() {

}

void cameraproxy::setUpCamera() {
    p = cvCaptureFromCAM(0);
    timer   = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(readFarme()));

    FAILURE_CHECK(p, "Init Capture Failed");

    if (!cvGrabFrame(p)) {
      std::cerr << "Conldn't GrabFrame" << std::endl;
      exit(EXIT_FAILURE);
    }
}

void cameraproxy::readFarme() {
    IplImage* frame = cvQueryFrame(p);
    uchar *data;
    QImage qImage = *(IplImageToQImage(frame, &data));
    emit stream(qImage);
}

QImage* cameraproxy::takeImage() {
    if (canTakePic) {
        IplImage* frame = cvQueryFrame(p);
        uchar *data;
        return IplImageToQImage(frame, &data);
    } else {
        return NULL;
    }
}

void cameraproxy::startTesting() {
    timer->start(33);
    canTakePic = true;
}

void cameraproxy::endTesting() {
    timer->stop();
    canTakePic = false;
}
