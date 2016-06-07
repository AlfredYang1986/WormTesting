#include "detailpane.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>

class  pred_item_creator {
public:
     pred_item_creator(QHBoxLayout* layout) : _layout(layout) {}

     void operator()(const QString& title) {
        QFrame* tmp =  new QFrame;
        tmp->setContentsMargins(0,0,0,0);
        QHBoxLayout* ml = new QHBoxLayout;
        ml->setContentsMargins(0,0,0,0);

        QLabel* l = new QLabel(title);
        l->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        ml->addWidget(l);
        ml->addSpacerItem(new QSpacerItem(10, 0, QSizePolicy::Fixed, QSizePolicy::Minimum));

        QLineEdit* ed = new QLineEdit;
        ed->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        ml->addWidget(ed);

        tmp->setLayout(ml);
        tmp->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        ml->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));

        _layout->addWidget(tmp);
     }

private:
     QHBoxLayout* _layout;
};

detailpane::detailpane(const vector<QString>& vec) : _vec(vec) {
    this->setUpSubviews();
}

detailpane::~detailpane() {
    main_layout->deleteLater();
}

void detailpane::setUpSubviews() {
    main_layout = new QHBoxLayout;
    main_layout->setContentsMargins(0,0,0,0);

    std::for_each(_vec.begin(), _vec.end(), pred_item_creator(main_layout));
    main_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));

    this->setLayout(main_layout);
}
