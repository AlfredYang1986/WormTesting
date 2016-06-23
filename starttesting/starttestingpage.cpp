#include "starttestingpage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include "sampledetailwidget.h"
#include "wormtreewidget.h"
#include "imgcomparepane.h"
#include "samplesearchingwidget.h"
#include "camera/cameraproxy.h"
#include "proxy/proxymanager.h"
#include "proxy/sampleproxy.h"

starttestingpage::starttestingpage() {
    this->setUpSubviews();
}

starttestingpage::~starttestingpage() {
    main_layout->deleteLater();
    sample_detail->deleteLater();
    sample_searching_widget->deleteLater();
    img_pane->deleteLater();
}

void starttestingpage::setUpSubviews() {
    main_layout = new QVBoxLayout;
    main_layout->setContentsMargins(0,0,0,0);

    QFrame* content_widget = new QFrame;
    content_widget->setObjectName("content_widget_page_one");
    content_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    content_widget->setMinimumSize(QSize(200, 200));
    content_widget->setContentsMargins(0,0,0,0);

    QHBoxLayout* page_one_content_layout = new QHBoxLayout;
    page_one_content_layout->setContentsMargins(8,0,0,0);
    sample_detail = new sampledetailwidget;
    sample_detail->setObjectName(QStringLiteral("sample_detail"));
    sample_detail->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    page_one_content_layout->addWidget(sample_detail);

    sample_searching_widget = new samplesearchingwidget;
    sample_searching_widget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    sample_searching_widget->setMinimumSize(QSize(300,300));
    sample_searching_widget->setContentsMargins(0,0,0,0);
    page_one_content_layout->addWidget(sample_searching_widget);

    img_pane = new imgcomparepane;
    img_pane->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    img_pane->setMinimumSize(QSize(200, 200));
    img_pane->setContentsMargins(0,0,0,0);
    page_one_content_layout->addWidget(img_pane);

    QSpacerItem* page_one_content_spacer = new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    page_one_content_layout->addSpacerItem(page_one_content_spacer);
    content_widget->setLayout(page_one_content_layout);

    main_layout->addWidget(content_widget);

    QHBoxLayout* control_pane = new QHBoxLayout;
    QSpacerItem* control_left_spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    control_start_btn = new QPushButton(tr("开始测试"));
    control_start_btn->setObjectName(QStringLiteral("page_one_start_btn"));
    control_start_btn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    QObject::connect(control_start_btn, SIGNAL(released()), this, SLOT(startTestingBtnClicked()));

    QSpacerItem* control_mid_spacer = new QSpacerItem(40, 0, QSizePolicy::Fixed, QSizePolicy::Minimum);
    control_end_btn = new QPushButton(tr("完成测试"));
    control_end_btn->setObjectName(QStringLiteral("page_one_cancel_btn"));
    control_end_btn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    QObject::connect(control_end_btn, SIGNAL(released()), this, SLOT(endTestingBtnClicked()));

    QSpacerItem* control_right_spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    control_pane->addSpacerItem(control_left_spacer);
    control_pane->addWidget(control_start_btn);
    control_pane->addSpacerItem(control_mid_spacer);
    control_pane->addWidget(control_end_btn);
    control_pane->addSpacerItem(control_right_spacer);

    main_layout->addLayout(control_pane);

    this->setLayout(main_layout);

    this->setObjectName(QStringLiteral("content_widget"));
    this->setStyleSheet("QWidget#content_widget { "
                            "margin-bottom: 8px;"
                        "}"
                        "QPushButton#page_one_start_btn {"
                            "width: 80px;"
                            "height: 30px;"
                            "color: white;"
                            "font-size: 14px;"
                            "background-color: #1bd7ff;"
                            "border: 1px solid #1bd7ff;"
                        "}"
                        "QPushButton#page_one_cancel_btn {"
                            "width: 80px;"
                            "height: 30px;"
                            "color: white;"
                            "font-size: 14px;"
                            "background-color: #1bd7ff;"
                            "border: 1px solid #1bd7ff;"
                        "}");

    QObject::connect(sample_searching_widget, SIGNAL(currentSample(const QJsonObject&)),
                     sample_detail, SLOT(currentSample(const QJsonObject&)));
    QObject::connect(cameraproxy::instance(), SIGNAL(stream(const QImage&)),
                     img_pane, SLOT(imageStream(const QImage&)));
    QObject::connect(img_pane, SIGNAL(takeImageSuccess(const QImage&)),
                     this, SLOT(takeImageSuccess(const QImage&)));
}

void starttestingpage::startTestingBtnClicked() {

    const QJsonObject& current_sample = sample_detail->queryCurrentObject();
    if (!current_sample.isEmpty())
        cameraproxy::instance()->startTesting();
    else {
        QMessageBox::warning(this, "Error",
                             tr("请先选定测试样本"),
                             QMessageBox::Ok, QMessageBox::Ok);
    }
}

void starttestingpage::endTestingBtnClicked() {
    cameraproxy::instance()->endTesting();
}

void starttestingpage::takeImageSuccess(const QImage& image) {
    const QJsonObject& current_sample = sample_detail->queryCurrentObject();
    if (current_sample.isEmpty()) {
        QMessageBox::warning(this, "Error",
                             tr("请先选定测试样本"),
                             QMessageBox::Ok, QMessageBox::Ok);
        return;
    }

    QString sample_id = current_sample["sample_id"].toString();
    proxymanager::instance()->getSampleProxy()->pushSampleImage(sample_id, image);
}
