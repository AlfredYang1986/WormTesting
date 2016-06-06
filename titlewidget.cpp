#include "titlewidget.h"
#include <QHBoxLayout>
#include "titlepushbutton.h"
#include <QSpacerItem>

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
    main_layout = new QHBoxLayout;
    main_layout->setContentsMargins(8, 8, 8, 0);

    menu_lst = vector<titlepushbutton*>();

    vector<std::pair<QString, QString> > tmp_lst;
    tmp_lst.push_back(std::make_pair("test1.png", "开始检测"));
    tmp_lst.push_back(std::make_pair("test1.png", "填写报告"));
    tmp_lst.push_back(std::make_pair("test1.png", "报告列表"));
    tmp_lst.push_back(std::make_pair("test1.png", "查看样本"));
    tmp_lst.push_back(std::make_pair("test1.png", "对比结果"));

    std::for_each(tmp_lst.begin(), tmp_lst.end(), pred_btn_creator(&menu_lst));
    std::for_each(menu_lst.begin(), menu_lst.end(), pred_push_layout(main_layout));

    right_item = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    main_layout->addSpacerItem(right_item);

    this->setLayout(main_layout);
}
