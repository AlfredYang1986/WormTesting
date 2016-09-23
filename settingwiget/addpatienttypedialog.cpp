#include "addpatienttypedialog.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <proxy/proxymanager.h>
#include <proxy/configproxy.h>
#include <QMessageBox>

addpatienttypedialog::addpatienttypedialog() {
    this->setUpSubviews();
}

addpatienttypedialog::~addpatienttypedialog() {
    main_layout->deleteLater();
}

QSize addpatienttypedialog::sizeHint() const {
    return QSize(500, 300);
}

void addpatienttypedialog::setUpSubviews() {
    main_layout = new QVBoxLayout;

    patient_edit = new QLineEdit;

    QFormLayout* content_layout = new QFormLayout;
    content_layout->addRow(QStringLiteral("添加病人类型"), patient_edit);

    QHBoxLayout* btns_layout = new QHBoxLayout;
    btns_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));

    QPushButton* save_btn = new QPushButton(QStringLiteral("保存"));
    QObject::connect(save_btn, SIGNAL(released()), this, SLOT(savaBtnClicked()));
    btns_layout->addWidget(save_btn);
    btns_layout->addSpacerItem(new QSpacerItem(20, 0, QSizePolicy::Fixed, QSizePolicy::Minimum));

    QPushButton* cancel_btn = new QPushButton(QStringLiteral("取消"));
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

void addpatienttypedialog::savaBtnClicked() {
    QString patient = patient_edit->text();
    if (!patient.isEmpty() && !vec_patient_type.contains(patient)) {
        proxymanager::instance()->getConfigProxy()->addPatientType(patient);
        this->close();
    }
    else {
        QMessageBox::information(this, "Error",
                                 QStringLiteral("不能添加相同的类型"),
                                 QMessageBox::Ok,
                                 QMessageBox::Ok);
    }
}

void addpatienttypedialog::cancelBtnClicked() {
    this->close();
}

void addpatienttypedialog::queryPatientTypeSuccess(const QJsonArray& arr) {
    QVector<QVariant> tmp = arr.toVariantList().toVector();
    QVector<QVariant>::iterator iter = tmp.begin();
    for (; iter != tmp.end(); ++iter) {
        QString t = (*iter).toString();
        vec_patient_type.push_back(t);
    }
}
