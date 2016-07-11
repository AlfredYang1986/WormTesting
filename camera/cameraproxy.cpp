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
        timer->deleteLater();
    }

    p = cvCaptureFromCAM(index);
    timer   = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(readFarme()));

    FAILURE_CHECK(p, "Init Capture Failed");

    if (!cvGrabFrame(p)) {
      std::cerr << "Conldn't GrabFrame" << std::endl;
      exit(EXIT_FAILURE);
    }
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
		QImage qImage = *(IplImageToQImage(frame, &data));
	    emit stream(qImage);
	}
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

    if (!p)
        this->setUpCamera();

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
