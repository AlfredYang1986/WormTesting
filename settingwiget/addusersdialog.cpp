#include "addusersdialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QLineEdit>
#include "proxy/configproxy.h"
#include "proxy/proxymanager.h"
#include <QMessageBox>

addusersdialog::addusersdialog() {
    this->setUpSubviews();
}

addusersdialog::~addusersdialog() {
    main_layout->deleteLater();
}

QSize addusersdialog::sizeHint() const {
    return QSize(500, 300);
}

void addusersdialog::setUpSubviews() {
    main_layout = new QVBoxLayout;

    user_name_edit = new QLineEdit;
    pwd_edit = new QLineEdit;
    pwd_edit->setEchoMode(QLineEdit::Password);

    QFormLayout* form = new QFormLayout;
    form->addRow("用户名:", user_name_edit);
    form->addRow("密  码:", pwd_edit);

    main_layout->addLayout(form);

    QHBoxLayout* btn_layout = new QHBoxLayout;
    btn_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));

    QPushButton* save_btn = new QPushButton("保存");
    QObject::connect(save_btn, SIGNAL(released()), this, SLOT(saveBtnClicked()));
    btn_layout->addWidget(save_btn);

    btn_layout->addSpacerItem(new QSpacerItem(30, 0, QSizePolicy::Fixed , QSizePolicy::Minimum));

    QPushButton* cancel_btn = new QPushButton("取消");
    QObject::connect(cancel_btn, SIGNAL(released()), this, SLOT(cancelBtnClicked()));
    btn_layout->addWidget(cancel_btn);

    btn_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
    main_layout->addLayout(btn_layout);

    this->setLayout(main_layout);

    QObject::connect(proxymanager::instance()->getConfigProxy(), SIGNAL(queryLstDoctorsSuccess(QJsonArray)),
                     this, SLOT(queryLstDoctorsSuccess(QJsonArray)));

    proxymanager::instance()->getConfigProxy()->lstUsers();
}

void addusersdialog::queryLstDoctorsSuccess(const QJsonArray & lst) {
    users_lst.clear();
    QVector<QVariant> tmp = lst.toVariantList().toVector();
    QVector<QVariant>::iterator iter = tmp.begin();
    for (; iter != tmp.end(); ++iter) {
        users_lst.push_back((*iter).toString());
    }
}

void addusersdialog::saveBtnClicked() {
    QString user_name = user_name_edit->text();
    QString pwd = pwd_edit->text();
    qDebug() << users_lst << endl;
    if (!user_name.isEmpty() && !users_lst.contains(user_name)) {
        proxymanager::instance()->getConfigProxy()->pushUser(user_name, pwd);
        this->close();
    } else {
        QMessageBox::information(this, "Error",
                                 "不能重复注册",
                                 QMessageBox::Ok,
                                 QMessageBox::Ok);
    }
}

void addusersdialog::cancelBtnClicked() {
    this->close();
}
