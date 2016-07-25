#include "titlepushbutton.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDir>
#include "tools/helptools.hpp"

titlepushbutton::titlepushbutton(const QString& img, const QString& title)
    : button_title(title) {
    //QString path = directoryOf("resource").absoluteFilePath(img);
    QString path = ":resource/" + img;
    button_img.load(path);
//    this->setObjectName("title_push_btn);
    this->setUpSubviews();
}

titlepushbutton::~titlepushbutton() {
    title_label->deleteLater();
    img_label->deleteLater();
    main_layout->deleteLater();
}

void titlepushbutton::setUpSubviews() {
    this->clearMask();
    this->setCheckable(true);

    main_layout = new QVBoxLayout;

    QHBoxLayout* line_one = new QHBoxLayout;
    QSpacerItem* line_one_left = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    QSpacerItem* line_one_right = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

    img_label = new QLabel;
    img_label->setObjectName(QStringLiteral("img_label"));
//    img_label->setPixmap(button_img.scaledToWidth(35));
    img_label->setPixmap(button_img.scaledToHeight(35));

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
    title_label->setObjectName(QStringLiteral("title_label"));
    title_label->setText(button_title);
    title_label->setContentsMargins(0, 0, 0, 0);

    line_two->addSpacerItem(line_two_left);
    line_two->addWidget(title_label);
    line_two->addSpacerItem(line_two_right);

    main_layout->addLayout(line_two);

    this->setLayout(main_layout);

    QObject::connect(this, SIGNAL(clicked()), this, SLOT(btnClicked()));

    this->setStyleSheet("QPushButton {"
                            "background-color: transparent;"
                            "border: none;"
                            "padding-left: 0px;"
                            "margin-left: 0px;"
                        "}"
                        "QPushButton:hover {"
                            "background-color: transparent;"
                            "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                                "stop: 0 rgba(255,255,255,0),"
                                                "stop: 1.0 rgba(255, 255, 255, 120));"
                            "border: none;"
                        "}"
                        "QPushButton:pressed {"
                            "background-color: transparent;"
                            "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                                "stop: 0 rgba(255,255,255,0),"
                                                "stop: 1.0 rgba(255, 255, 255, 120));"
                            "border: none;"
                        "}"
                        "QPushButton:checked {"
                            "background-color: transparent;"
                            "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                                                "stop: 0 rgba(255,255,255,0),"
                                                "stop: 1.0 rgba(255, 255, 255, 120));"
                            "border: none;"
                        "}"
                        "QLabel#title_label {"
                            "color: #fff;"
                            "font-size: 14px;"
                        "}");
}

QSize titlepushbutton::sizeHint() const {
    return QSize(100, 80);
}

void titlepushbutton::btnClicked() {
    emit didSelectTitle(button_title);
}

const QString& titlepushbutton::getBtnTitle() const {
    return button_title;
}
