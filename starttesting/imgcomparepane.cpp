#include "imgcomparepane.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include "camera/cameraproxy.h"
#include <QDebug>
#include <QCamera>
#include <QCameraInfo>
#include <QMessageBox>

imgcomparepane::imgcomparepane() {
    this->setUpSubviews();
}

imgcomparepane::~imgcomparepane() {
    main_layout->deleteLater();
    photo_preview->deleteLater();
}

void imgcomparepane::setUpSubviews() {
    main_layout = new QVBoxLayout;

    QHBoxLayout* title_layout = new QHBoxLayout;

    // top
    QLabel* title_label = new QLabel("监控");
    title_layout->addWidget(title_label);
    QSpacerItem* title_spacer_mid = new QSpacerItem(40, 0, QSizePolicy::Fixed, QSizePolicy::Minimum);
    title_layout->addSpacerItem(title_spacer_mid);

    box = new QComboBox;
    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    if (cameras.size() == 0) {
        foreach (const QCameraInfo &cameraInfo, cameras) {
           QString item = cameraInfo.description();
           if (item.count() == 0) {
               item = cameraInfo.deviceName();
           }
           box->addItem(item);
       }
    } else {
        box->addItem(tr("摄像头1"));
    }
    QObject::connect(box, SIGNAL(currentIndexChanged(int)),
                     this, SLOT(changeCurrentCamera(int)));
    title_layout->addWidget(box);

    title_take_photo = new QPushButton(tr("抓图"));
    QObject::connect(title_take_photo, SIGNAL(released()), this, SLOT(takeImage()));
    title_take_photo->setObjectName("title_take_photo");
    title_take_photo->setStyleSheet("QPushButton#title_take_photo {"
                                        "background-color: #1bd7ff;"
                                        "color: #fff;"
                                        "border: none;"
                                        "width: 50px;"
                                        "height: 25px;"
                                    "}");
    title_layout->addWidget(title_take_photo);
    main_layout->addLayout(title_layout);

    photo_preview = new QLabel;
    photo_preview->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    main_layout->addWidget(photo_preview);

    // btn lst

    //QSpacerItem* spacer_bottom = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    //main_layout->addSpacerItem(spacer_bottom);

    this->setLayout(main_layout);
}

QSize imgcomparepane::sizeHint() const {
    return QSize(200, 440);
}

void imgcomparepane::imageStream(const QImage& image) {
    QPixmap m = QPixmap::fromImage(image);
    m = m.scaled(photo_preview->width(), photo_preview->height());
    photo_preview->setPixmap(m);
}

void imgcomparepane::takeImage() {
    title_take_photo->setEnabled(false);
    QImage* pImg = cameraproxy::instance()->takeImage();
    if (pImg) {
        emit takeImageSuccess(*pImg);
        delete(pImg);
    }
    title_take_photo->setEnabled(true);
}

void imgcomparepane::clearPane() {
    photo_preview->clear();
}

void imgcomparepane::changeCurrentCamera(int) {
//    cameraproxy::instance()->setUpCamera(index);
}

void imgcomparepane::startTesting(bool bTesting) {
    box->setEnabled(!bTesting);
}

int imgcomparepane::currentCameraIndex() const {
    if (box->count() > 0)
        return box->currentIndex();
    else return 0;
}
