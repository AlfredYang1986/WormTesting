#include "deletesampleresourcedialog.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QComboBox>
#include <QPushButton>
#include <proxy/proxymanager.h>
#include <proxy/configproxy.h>

deletesampleresourcedialog::deletesampleresourcedialog() {
    this->setUpSubviews();
}

deletesampleresourcedialog::~deletesampleresourcedialog() {
    main_layout->deleteLater();
}

QSize deletesampleresourcedialog::sizeHint() const {
    return QSize(500, 300);
}

void deletesampleresourcedialog::setUpSubviews() {
    main_layout = new QVBoxLayout;

    resource_box = new QComboBox;

    QFormLayout* content_layout = new QFormLayout;
    content_layout->addRow("删除样本来源", resource_box);

    QHBoxLayout* btns_layout = new QHBoxLayout;
    btns_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));

    QPushButton* save_btn = new QPushButton("删除");
    QObject::connect(save_btn, SIGNAL(released()), this, SLOT(saveBtnClicked()));
    btns_layout->addWidget(save_btn);
    btns_layout->addSpacerItem(new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Minimum));

    QPushButton* cancel_btn = new QPushButton("取消");
    QObject::connect(cancel_btn, SIGNAL(released()), this, SLOT(cancelBtnClicked()));
    btns_layout->addWidget(cancel_btn);
    btns_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));

    main_layout->addLayout(content_layout);
    main_layout->addLayout(btns_layout);

    this->setLayout(main_layout);

    proxymanager::instance()->getConfigProxy()->querySampleResourceType();

    QObject::connect(proxymanager::instance()->getConfigProxy(), SIGNAL(querySampleResourceTypeSuccess(QJsonArray)),
                     this, SLOT(querySampleResourceTypeSuccess(QJsonArray)));
}

void deletesampleresourcedialog::saveBtnClicked() {
    QString resource = resource_box->currentText();
    if (!resource.isEmpty())
        proxymanager::instance()->getConfigProxy()->deleteSampleResourceType(resource);

    this->close();
}

void deletesampleresourcedialog::cancelBtnClicked() {
    this->close();
}

void deletesampleresourcedialog::querySampleResourceTypeSuccess(const QJsonArray & result) {
    QJsonArray::const_iterator iter = result.begin();
    for(; iter != result.end(); ++iter) {
        QString tmp = (*iter).toString();
        resource_box->addItem(tmp);
    }
}
