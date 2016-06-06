#include "titlepushbutton.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDir>
#include "helptools.hpp"

titlepushbutton::titlepushbutton(const QString& img, const QString& title)
    : button_title(title) {
    QString path = directoryOf("resource").absoluteFilePath(img);
    button_img.load(path);
    this->setObjectName("title_push_btn");
    this->setUpSubviews();
}

titlepushbutton::~titlepushbutton() {
    title_label->deleteLater();
    img_label->deleteLater();
    main_layout->deleteLater();
}

void titlepushbutton::setUpSubviews() {
    this->clearMask();

    main_layout = new QVBoxLayout;

    QHBoxLayout* line_one = new QHBoxLayout;
    QSpacerItem* line_one_left = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem* line_one_right = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

    img_label = new QLabel;
    img_label->setObjectName(QStringLiteral("img_label"));
    img_label->setPixmap(button_img.scaledToWidth(60));

    line_one->addSpacerItem(line_one_left);
    line_one->addWidget(img_label);
    line_one->addSpacerItem(line_one_right);

    main_layout->addLayout(line_one);

    QSpacerItem* mid_spacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    main_layout->addSpacerItem(mid_spacer);

    QHBoxLayout* line_two = new QHBoxLayout;
    QSpacerItem* line_two_left = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem* line_two_right = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

    title_label = new QLabel;
    title_label->setObjectName(QStringLiteral("title_lable"));
    title_label->setText(button_title);

    line_two->addSpacerItem(line_two_left);
    line_two->addWidget(title_label);
    line_two->addSpacerItem(line_two_right);

    main_layout->addLayout(line_two);

    this->setLayout(main_layout);

    this->setStyleSheet("QPushButton#title_push_btn {"
                            "background-color: transparent;"
                            "border: none;"
                            "padding-left: 0px;"
                            "margin-left: 0px;"
                        "}"
                        "QPushButton#title_push_btn:hover {"
                            "background-color: red;"
                            "border: none;"
                        "}"
                        "QPushButton#title_push_btn:pressed {"
                            "background-color: yellow;"
                            "border: none;"
                        "}");
}

QSize titlepushbutton::sizeHint() const {
    return QSize(80, 100);
}
