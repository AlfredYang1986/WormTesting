#include "titlewidget.h"
#include <QHBoxLayout>
#include "titlepushbutton.h"
#include <QSpacerItem>
#include <QObject>

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
    return QSize(100, 100);
}

void titlewidget::setUpSubViews() {
    this->setObjectName(QStringLiteral("title_widget"));
    this->setStyleSheet("QWidget#title_widget { background-color : #1bd7ff; }");

    main_layout = new QHBoxLayout;
    main_layout->setContentsMargins(8, 8, 8, 0);

    menu_lst = vector<titlepushbutton*>();

    vector<std::pair<QString, QString> > tmp_lst;
    tmp_lst.push_back(std::make_pair("menu1.png", "录入样本"));
    tmp_lst.push_back(std::make_pair("menu2.png", "开始检测"));
    tmp_lst.push_back(std::make_pair("menu3.png", "填写报告"));
    tmp_lst.push_back(std::make_pair("menu4.png", "报告列表"));
    tmp_lst.push_back(std::make_pair("menu5.png", "样本资料"));
    tmp_lst.push_back(std::make_pair("menu6.png", "对比结果"));
    tmp_lst.push_back(std::make_pair("menu7.png", "系统设置"));
    tmp_lst.push_back(std::make_pair("menu8.png", "关于系统"));

    std::for_each(tmp_lst.begin(), tmp_lst.end(), pred_btn_creator(&menu_lst));
    std::for_each(menu_lst.begin(), menu_lst.end(), pred_push_layout(main_layout));

    vector<titlepushbutton*>::iterator iter = menu_lst.begin();
    for (;iter != menu_lst.end(); ++iter) {
        QObject::connect(*iter, SIGNAL(didSelectTitle(const QString&)), this, SLOT(menu_btn_cleck(const QString&)));
    }

    right_item = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    main_layout->addSpacerItem(right_item);

    this->setLayout(main_layout);

    vector<titlepushbutton*>::iterator begin = menu_lst.begin();
    (*begin)->setChecked(true);
}

void titlewidget::menu_btn_cleck(const QString& title) {
    std::for_each(menu_lst.begin(), menu_lst.end(), pred_btn_click());
    vector<titlepushbutton*>::iterator iter = std::find_if(menu_lst.begin(), menu_lst.end(), pred_btn_locate_tab(title));
    (*iter)->setChecked(true);

    emit changeContentPane(title);
}
