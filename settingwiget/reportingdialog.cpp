#include "reportingdialog.h"
#include "QVBoxLayout"
#include "QScrollArea"
#include "proxy/proxymanager.h"
#include "proxy/wormproxy.h"
#include <QDebug>
#include <QGroupBox>
#include <QCheckBox>
#include <QPushButton>
#include "addwormcatdialog.h"
#include "deletewwormcatdialog.h"
#include "addwormdialog.h"
#include "deletewormdialog.h"

reportingdialog::reportingdialog() {
    this->setUpSubviews();
}

reportingdialog::~reportingdialog() {
    main_layout->deleteLater();
    QObject::disconnect(proxymanager::instance()->getWormProxy(), SIGNAL(queryWormCatSuccess(const QJsonObject&)),
                     this, SLOT(queryWormCatSuccess(const QJsonObject&)));
}

QSize reportingdialog::sizeHint() const {
    return QSize(1000, 1000);
}

void reportingdialog::setUpSubviews() {
    main_layout = new QVBoxLayout();

    area = new QScrollArea;
    area->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QHBoxLayout* btns_layout = new QHBoxLayout;
    {
        QPushButton* btn = new QPushButton("添加虫类");
        btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        QObject::connect(btn, SIGNAL(released()), this, SLOT(addWorsCatsDialog()));
        btns_layout->addWidget(btn);
    }

    {
        QPushButton* btn = new QPushButton("删除虫类");
        btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        QObject::connect(btn, SIGNAL(released()), this, SLOT(deleteWorsCatsDialog()));
        btns_layout->addWidget(btn);
    }

    {
        QPushButton* btn = new QPushButton("添加虫子");
        btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        QObject::connect(btn, SIGNAL(released()), this, SLOT(addWormDialog()));
        btns_layout->addWidget(btn);
    }

    {
        QPushButton* btn = new QPushButton("删除虫子");
        btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        QObject::connect(btn, SIGNAL(released()), this, SLOT(deleteWormDialog()));
        btns_layout->addWidget(btn);
    }

    {
        QPushButton* btn = new QPushButton("保存修改");
        btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        QObject::connect(btn, SIGNAL(released()), this, SLOT(saveWormchanges()));
        btns_layout->addWidget(btn);
    }

    main_layout->addWidget(area);
    main_layout->addLayout(btns_layout);
    this->setLayout(main_layout);

    QObject::connect(proxymanager::instance()->getWormProxy(), SIGNAL(queryWormCatSuccess(const QJsonObject&)),
                     this, SLOT(queryWormCatSuccess(const QJsonObject&)));

    proxymanager::instance()->getWormProxy()->queryWormCat();
}

void reportingdialog::reloadData() {
    proxymanager::instance()->getWormProxy()->queryWormCat();
}

void reportingdialog::queryWormCatSuccess(const QJsonObject & cats) {
    content_widget = new QFrame;
    content_layout = new QVBoxLayout;

    QStringList keys = cats.keys();
    QStringList::const_iterator key = keys.begin();
    for(; key != keys.end(); ++key) {

        QGroupBox* box = new QGroupBox(*key);

        QVBoxLayout* group_layout = new QVBoxLayout;
        int hint_width = 0;

        QHBoxLayout* tmp_layout = new QHBoxLayout;

        QJsonArray lst = cats[*key].toArray();
        QJsonArray::iterator iter = lst.begin();
        for (; iter != lst.end(); ++iter) {
            QString name = (*iter).toObject().operator []("name").toString();
            QCheckBox* tmp = new QCheckBox(name);
            tmp->setObjectName(*key + "/#/" + name);
            QObject::connect(tmp, SIGNAL(clicked(bool)),
                             this, SLOT(checkBtnChanged(bool)));

            int setting = (*iter).toObject().operator []("setting").toInt();
            if (setting == 1) {
                tmp->setChecked(true);
            }
            tmp_layout->addWidget(tmp);

            hint_width += tmp->sizeHint().width();

            if (hint_width > 850) {
               group_layout->addLayout(tmp_layout);
               tmp_layout = new QHBoxLayout;
               hint_width = 0;
            }
        }

        tmp_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
        group_layout->addLayout(tmp_layout);
        box->setLayout(group_layout);
        content_layout->addWidget(box);
    }

    content_widget->setLayout(content_layout);

    area->setWidget(content_widget);
}

void reportingdialog::addWorsCatsDialog() {
    addWormCatDialog* dlg = new addWormCatDialog;
    dlg->exec();
    this->reloadData();
}

void reportingdialog::deleteWorsCatsDialog() {
    deletewwormcatdialog* dlg = new deletewwormcatdialog;
    dlg->exec();
    this->reloadData();
}

void reportingdialog::addWormDialog() {
    addwormdialog* dlg = new addwormdialog;
    dlg->exec();
    this->reloadData();
}

void reportingdialog::deleteWormDialog() {
    deletewormdialog* dlg = new deletewormdialog;
    dlg->exec();
    this->reloadData();
}

void reportingdialog::saveWormchanges() {
    QMap<QString, bool> ::iterator iter = changes.begin();
    for (; iter != changes.end(); ++iter) {
        QStringList tmp = iter.key().split("/#/");
        bool selected = iter.value();
        QString worm_cat = tmp.first();
        QString worm = tmp.last();

        proxymanager::instance()->getWormProxy()->changeSetting(worm, worm_cat, selected);
    }
    this->reloadData();
    QTime dieTime = QTime::currentTime().addMSecs(1500);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void reportingdialog::checkBtnChanged(bool selected) {
    QString tmp = QObject::sender()->objectName();
    changes[tmp] = selected;
}
