#include "deletepatienttypedialog.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QComboBox>
#include <QPushButton>
#include <proxy/proxymanager.h>
#include <proxy/configproxy.h>

deletepatienttypedialog::deletepatienttypedialog() {
    this->setUpSubviews();
}

deletepatienttypedialog::~deletepatienttypedialog() {
    main_layout->deleteLater();
}

QSize deletepatienttypedialog::sizeHint() const {
    return QSize(500, 300);
}

void deletepatienttypedialog::setUpSubviews() {
    main_layout = new QVBoxLayout;

    patient_box = new QComboBox;

    QFormLayout* content_layout = new QFormLayout;
    content_layout->addRow("删除病人来源", patient_box);

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

    proxymanager::instance()->getConfigProxy()->queryPatientType();

    QObject::connect(proxymanager::instance()->getConfigProxy(), SIGNAL(queryPatientTypeSuccess(QJsonArray)),
                     this, SLOT(queryPatientTypeSuccess(QJsonArray)));
}

void deletepatienttypedialog::saveBtnClicked() {
    QString patient = patient_box->currentText();
    if (!patient.isEmpty())
        proxymanager::instance()->getConfigProxy()->deletePatientType(patient);

    this->close();
}

void deletepatienttypedialog::cancelBtnClicked() {
    this->close();
}

void deletepatienttypedialog::queryPatientTypeSuccess(const QJsonArray & result) {
    QJsonArray::const_iterator iter = result.begin();
    for(; iter != result.end(); ++iter) {
        QString tmp = (*iter).toString();
        patient_box->addItem(tmp);
    }
}
