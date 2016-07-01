#include "settingmainwidget.h"
#include <QVBoxLayout>
#include <QPushButton>
#include "reportingdialog.h"

settingmainwidget::settingmainwidget() {
    this->setUpSubviews();
}

settingmainwidget::~settingmainwidget() {
    main_layout->deleteLater();
}

QSize settingmainwidget::sizeHint() const {
    return QSize(300, 300);
}

void settingmainwidget::setUpSubviews() {
    main_layout = new QVBoxLayout;

    {
        QPushButton* btn = new QPushButton("修改报告项目");
        btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        QObject::connect(btn, SIGNAL(released()), this, SLOT(showReportingSettingDialog()));
        main_layout->addWidget(btn);
    }

    QHBoxLayout* resource = new QHBoxLayout;
    {
        QPushButton* btn = new QPushButton("添加样本来源");
        btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        QObject::connect(btn, SIGNAL(released()), this, SLOT(showReportingSettingDialog()));
        resource->addWidget(btn);
    }

    {
        QPushButton* btn = new QPushButton("删除样本来源");
        btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        QObject::connect(btn, SIGNAL(released()), this, SLOT(showReportingSettingDialog()));
        resource->addWidget(btn);
    }
    resource->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
    main_layout->addLayout(resource);

    main_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));
    this->setLayout(main_layout);

    this->setStyleSheet("QPushButton {"
                            "width: 100px;"
                            "height: 30px;"
                            "color: white;"
                            "font-size: 14px;"
                            "background-color: #1bd7ff;"
                            "border: 1px solid #1bd7ff;"
                        "}");
}

void settingmainwidget::showReportingSettingDialog() {
    reportingdialog* dlg = new reportingdialog;
    dlg->exec();
}
