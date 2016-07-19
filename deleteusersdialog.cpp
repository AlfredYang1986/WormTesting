#include "deleteusersdialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include "proxy/configproxy.h"
#include "proxy/proxymanager.h"
#include <QMessageBox>
#include <QPushButton>
#include <QComboBox>

deleteusersdialog::deleteusersdialog() {
    this->setUpSubviews();
}

deleteusersdialog::~deleteusersdialog() {

}

QSize deleteusersdialog::sizeHint() const {
    return QSize(500, 300);
}

void deleteusersdialog::setUpSubviews() {
    main_layout = new QVBoxLayout;

    box = new QComboBox;

    QFormLayout* form = new QFormLayout;
    form->addRow("删除用户: ", box);
    main_layout->addLayout(form);

    QHBoxLayout* btn_layout = new QHBoxLayout;
    btn_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));

    QPushButton* save_btn = new QPushButton("删除");
    QObject::connect(save_btn, SIGNAL(released()), this, SLOT(saveBtnClicked()));
    btn_layout->addWidget(save_btn);

    btn_layout->addSpacerItem(new QSpacerItem(30, 0, QSizePolicy::Fixed, QSizePolicy::Minimum));

    QPushButton* cancal_btn = new QPushButton("取消");
    QObject::connect(cancal_btn, SIGNAL(released()), this, SLOT(cancelBtnClicked()));
    btn_layout->addWidget(cancal_btn);

    btn_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));

    main_layout->addLayout(btn_layout);

    this->setLayout(main_layout);

    QObject::connect(proxymanager::instance()->getConfigProxy(), SIGNAL(queryLstDoctorsSuccess(QJsonArray)),
                     this, SLOT(queryLstDoctorsSuccess(QJsonArray)));

    proxymanager::instance()->getConfigProxy()->lstUsers();
}

void deleteusersdialog::saveBtnClicked() {
    QString user_name = box->currentText();
    if (user_name == "admin") {
        QMessageBox::information(this, "Error",
                                 "不能删除admin用户",
                                 QMessageBox::Ok,
                                 QMessageBox::Ok);
    } else {
        proxymanager::instance()->getConfigProxy()->popUser(user_name);
        this->close();
    }
}

void deleteusersdialog::cancelBtnClicked() {
    this->close();
}

void deleteusersdialog::queryLstDoctorsSuccess(const QJsonArray& lst) {
    box->clear();
    QVector<QVariant> tmp = lst.toVariantList().toVector();
    QVector<QVariant>::iterator iter = tmp.begin();
    for (; iter != tmp.end(); ++iter) {
        box->addItem((*iter).toString());
    }
}
