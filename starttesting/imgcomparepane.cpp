#include "imgcomparepane.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

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
    QPushButton* title_take_photo = new QPushButton(tr("抓图"));
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

    // photo preview
    photo_preview = new QLabel;
    QPixmap m;
    m.load(":/resource/photo_preview.png");
    photo_preview->setPixmap(m);
    photo_preview->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    main_layout->addWidget(photo_preview);

    // btn lst

    QSpacerItem* spacer_bottom = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    main_layout->addSpacerItem(spacer_bottom);

    this->setLayout(main_layout);
}

QSize imgcomparepane::sizeHint() const {
    return QSize(200, 440);
}
