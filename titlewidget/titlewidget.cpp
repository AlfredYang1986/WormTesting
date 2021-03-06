﻿#include "titlewidget.h"
#include <QHBoxLayout>
#include "titlepushbutton.h"
#include <QSpacerItem>
#include <QObject>
#include <QDesktopServices>
#include <QUrl>
#include "proxy/proxymanager.h"
#include "proxy/authproxy.h"

class pred_btn_creator {
public:
    pred_btn_creator(vector<titlepushbutton*>* lst) : vec(lst) {}

    void operator()(const std::pair<QString, QString>& iter) {
        titlepushbutton* tmp = new titlepushbutton(iter.first, iter.second);
        tmp->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        vec->push_back(tmp);
    }
private:
    vector<titlepushbutton*>* vec;
};

class pred_push_layout {
public:
    pred_push_layout(QBoxLayout* layout) : _layout(layout) {}

    void operator()(titlepushbutton* const btn) {
        _layout->addWidget(btn);
    }

private:
    QBoxLayout* _layout;
};

class pred_release {
public:
    void operator()(titlepushbutton* const btn) {
        btn->deleteLater();
    }
};

class pred_btn_click {
public:
    void operator()(titlepushbutton* const btn) {
        btn->setChecked(false);
    }
};

class pred_btn_locate_tab {
public:
    pred_btn_locate_tab(const QString& title) : cur(title) {}

    bool operator()(titlepushbutton* const btn) {
       return btn->getBtnTitle() == cur;
    }

private:
    QString cur;
};

titlewidget::titlewidget() {
    this->setUpSubViews();
}

titlewidget::~titlewidget() {
    std::for_each(menu_lst.begin(), menu_lst.end(), pred_release());
    main_layout->deleteLater();
}

QSize titlewidget::sizeHint() const {
    return QSize(150, 100);
}

void titlewidget::setUpSubViews() {
    this->setObjectName(QStringLiteral("title_widget"));
    this->setStyleSheet("QWidget#title_widget { background-color : #1bd7ff; }");

    main_layout = new QHBoxLayout;
    main_layout->setContentsMargins(8, 8, 8, 0);

    menu_lst = vector<titlepushbutton*>();

    vector<std::pair<QString, QString> > tmp_lst;
    tmp_lst.push_back(std::make_pair("menu1.png", QStringLiteral("录入样本")));
    tmp_lst.push_back(std::make_pair("menu2.png", QStringLiteral("开始检测")));
    tmp_lst.push_back(std::make_pair("menu3.png", QStringLiteral("填写报告")));
    tmp_lst.push_back(std::make_pair("menu4.png", QStringLiteral("结果查询")));
    tmp_lst.push_back(std::make_pair("menu6.png", QStringLiteral("对比结果")));
    tmp_lst.push_back(std::make_pair("menu5.png", QStringLiteral("形态学图谱")));
    tmp_lst.push_back(std::make_pair("menu7.png", QStringLiteral("系统设置")));
    tmp_lst.push_back(std::make_pair("menu8.png", QStringLiteral("关于系统")));

    std::for_each(tmp_lst.begin(), tmp_lst.end(), pred_btn_creator(&menu_lst));
    std::for_each(menu_lst.begin(), menu_lst.end(), pred_push_layout(main_layout));

    vector<titlepushbutton*>::iterator iter = menu_lst.begin();
    for (;iter != menu_lst.end(); ++iter) {
        QObject::connect(*iter, SIGNAL(didSelectTitle(const QString&)), this, SLOT(menu_btn_cleck(const QString&)));
    }

    right_item = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    main_layout->addSpacerItem(right_item);

    titlepushbutton* help_btn = new titlepushbutton("help.png", QStringLiteral("联系我们"));
    help_btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    QObject::connect(help_btn, SIGNAL(didSelectTitle(const QString&)), this, SLOT(help_btn_click(QString)));

    titlepushbutton* sign_out_btn = new titlepushbutton("help.png", QStringLiteral("退出登陆"));
    sign_out_btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    QObject::connect(sign_out_btn, SIGNAL(didSelectTitle(const QString&)), this, SLOT(sign_out_btn_click(QString)));

    main_layout->addWidget(help_btn);
    main_layout->addWidget(sign_out_btn);

    this->setLayout(main_layout);

    vector<titlepushbutton*>::iterator begin = menu_lst.begin();
    (*begin)->setChecked(true);
}

void titlewidget::menu_btn_cleck(const QString& title) {
//    std::for_each(menu_lst.begin(), menu_lst.end(), pred_btn_click());
//    vector<titlepushbutton*>::iterator iter = std::find_if(menu_lst.begin(), menu_lst.end(), pred_btn_locate_tab(title));
//    (*iter)->setChecked(true);

    emit changeContentPane(title);
}

void titlewidget::help_btn_click(const QString &) {
    QDesktopServices::openUrl(QUrl("http://altbio.com.cn/"));
}

void titlewidget::changeCurrentIndex(int index) {
    std::for_each(menu_lst.begin(), menu_lst.end(), pred_btn_click());
    titlepushbutton* iter = menu_lst.at(index);
    iter->setChecked(true);
}

void titlewidget::sign_out_btn_click(const QString &) {
    proxymanager::instance()->getAuthProxy()->signOutCurrentUser();
}
