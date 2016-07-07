#include "addsampleresourcedialog.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <proxy/proxymanager.h>
#include <proxy/configproxy.h>

addsampleresourcedialog::addsampleresourcedialog() {
    this->setUpSubviews();
}

addsampleresourcedialog::~addsampleresourcedialog() {
    main_layout->deleteLater();
}

QSize addsampleresourcedialog::sizeHint() const {
    return QSize(500, 300);
}

void addsampleresourcedialog::setUpSubviews() {
    main_layout = new QVBoxLayout;

    resource_edit = new QLineEdit;

    QFormLayout* content_layout = new QFormLayout;
    content_layout->addRow("添加样本来源", resource_edit);

    QHBoxLayout* btns_layout = new QHBoxLayout;
    btns_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));

    QPushButton* save_btn = new QPushButton("保存");
    QObject::connect(save_btn, SIGNAL(released()), this, SLOT(savaBtnClicked()));
    btns_layout->addWidget(save_btn);
    btns_layout->addSpacerItem(new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Minimum));

    QPushButton* cancel_btn = new QPushButton("取消");
    QObject::connect(cancel_btn, SIGNAL(released()), this, SLOT(cancelBtnClicked()));
    btns_layout->addWidget(cancel_btn);
    btns_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));

    main_layout->addLayout(content_layout);
    main_layout->addLayout(btns_layout);

    this->setLayout(main_layout);
}

void addsampleresourcedialog::savaBtnClicked() {
    QString resource = resource_edit->text();
    if (!resource.isEmpty())
        proxymanager::instance()->getConfigProxy()->addSampleResourceType(resource);

    this->close();
}

void addsampleresourcedialog::cancelBtnClicked() {
    this->close();
}