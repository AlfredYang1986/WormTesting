#include "starttestingpage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include "sampledetailwidget.h"
#include "wormtreewidget.h"
#include "imgcomparepane.h"
#include "samplesearchingwidget.h"

starttestingpage::starttestingpage() {
    this->setUpSubviews();
}

starttestingpage::~starttestingpage() {
    main_layout->deleteLater();
    sample_detail->deleteLater();
//    worm_tree->deleteLater();
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
//    content_widget->setStyleSheet("QWidget#content_widget_page_one { background-color: green }");

    QHBoxLayout* page_one_content_layout = new QHBoxLayout;
    page_one_content_layout->setContentsMargins(8,0,0,0);
    sample_detail = new sampledetailwidget;
    sample_detail->setObjectName(QStringLiteral("sample_detail"));
    sample_detail->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
//    sample_detail->setStyleSheet("QWidget#sample_detail { background-color: red; }");
    page_one_content_layout->addWidget(sample_detail);

//    worm_tree = new wormtreewidget;
//    worm_tree->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
//    worm_tree->setMinimumSize(QSize(200, 200));
//    worm_tree->setContentsMargins(0,0,0,0);
//    page_one_content_layout->addWidget(worm_tree);

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
    QPushButton* control_start_btn = new QPushButton(tr("开始测试"));
    control_start_btn->setObjectName(QStringLiteral("page_one_start_btn"));
    control_start_btn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    QSpacerItem* control_mid_spacer = new QSpacerItem(40, 0, QSizePolicy::Fixed, QSizePolicy::Minimum);
    QPushButton* control_cancel_btn = new QPushButton(tr("重新测试"));
    control_cancel_btn->setObjectName(QStringLiteral("page_one_cancel_btn"));
    control_cancel_btn->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    QSpacerItem* control_right_spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

    control_pane->addSpacerItem(control_left_spacer);
    control_pane->addWidget(control_start_btn);
    control_pane->addSpacerItem(control_mid_spacer);
    control_pane->addWidget(control_cancel_btn);
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
}
