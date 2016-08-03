#include "aboutuswidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QFile>
#include <QDesktopWidget>
#include <QApplication>

aboutuswidget::aboutuswidget() {
    this->setupSubviews();
}

aboutuswidget::~aboutuswidget() {

}

void aboutuswidget::setupSubviews() {
    main_layout = new QHBoxLayout;

    aboutus = new QLabel;
    aboutus->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    aboutus->setAlignment(Qt::AlignTop);
    aboutus->setWordWrap(true);

    QFile f(":/resource/aboutus");
    if (f.open(QIODevice::OpenModeFlag::ReadOnly)) {
        QString html = f.readAll();
        aboutus->setText(html);
        f.close();
    }

    img = new QLabel;
    img->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    img->setFixedSize(500, 406);
    img->setPixmap(QPixmap(":/resource/aboutus.png").scaled(500, 406));

    QDesktopWidget* desktopWidget = QApplication::desktop();
    QRect clientRect = desktopWidget->availableGeometry();
    this->setMaximumWidth(clientRect.width() - 16);
//    aboutus->setMaximumWidth(clientRect.width() - 16 - 500);

    main_layout->addWidget(aboutus);
    main_layout->addWidget(img);
    this->setLayout(main_layout);
}
