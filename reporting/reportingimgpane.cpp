#include "reportingimgpane.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include "proxy/proxymanager.h"
#include "proxy/fileoptproxy.h"

reportingimgpane::reportingimgpane() {
    this->setUpSubviews();
}

reportingimgpane::~reportingimgpane() {
    main_layout->deleteLater();
}

void reportingimgpane::setUpSubviews() {
    main_layout = new QVBoxLayout;

    large_img = new QLabel;
    large_img->setAutoFillBackground(true);

    large_img->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    main_layout->addWidget(large_img);

    main_layout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Minimum, QSizePolicy::Expanding));

    QHBoxLayout* btn_line_one = new QHBoxLayout;
    btn_line_one->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Expanding, QSizePolicy::Minimum));
    QPushButton* save_btn = new QPushButton(tr("保存"));
    save_btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    btn_line_one->addWidget(save_btn);
    btn_line_one->addSpacerItem(new QSpacerItem(10,0,QSizePolicy::Fixed, QSizePolicy::Minimum));
    QPushButton* preview_btn = new QPushButton(tr("预览"));
    preview_btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    btn_line_one->addWidget(preview_btn);
    btn_line_one->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Expanding, QSizePolicy::Minimum));

    main_layout->addLayout(btn_line_one);

    QHBoxLayout* btn_line_two = new QHBoxLayout;
    btn_line_two->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Expanding, QSizePolicy::Minimum));
    QPushButton* print_btn = new QPushButton(tr("打印"));
    print_btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    btn_line_two->addWidget(print_btn);
    btn_line_two->addSpacerItem(new QSpacerItem(10,0,QSizePolicy::Fixed, QSizePolicy::Minimum));
    QPushButton* cancel_btn = new QPushButton(tr("取消"));
    cancel_btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    btn_line_two->addWidget(cancel_btn);
    btn_line_two->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Expanding, QSizePolicy::Minimum));

    main_layout->addLayout(btn_line_two);
    main_layout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Minimum, QSizePolicy::Expanding));

    this->setLayout(main_layout);

    this->setStyleSheet("QPushButton {"
                            "background-color: #1bd7ff;"
                            "width: 90px;"
                            "height: 30px;"
                            "color: #fff;"
                            "font-size: 14px;"
                            "margin: 0px;"
                            "border: none;"
                        "}");

    QObject::connect(proxymanager::instance()->getFileProxy(), SIGNAL(downloadFileSuccess(const QByteArray&)),
                     this, SLOT(downloadFileSuccess(const QByteArray&)));
}

QSize reportingimgpane::sizeHint() const {
    return QSize(350, 280);
}

void reportingimgpane::fillImages(const QJsonObject& sample) {
    QJsonArray arr = sample["images"].toArray();
    QString name = arr.last().toString();
    proxymanager::instance()->getFileProxy()->downloadFile(name);
}

void reportingimgpane::downloadFileSuccess(const QByteArray& arr) {
    QPixmap m;
    m.loadFromData(arr);
    m = m.scaled(this->width(), this->height() - 100);
    large_img->setPixmap(m);
}
