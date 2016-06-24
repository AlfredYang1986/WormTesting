#include "reportlstcontainer.h"

#include <QHBoxLayout>
//#include "searchtreewidget.h"
#include "commonwidget/resourcetreewidget.h"
#include "searchresulttablewidget.h"

reportlstcontainer::reportlstcontainer() {
    this->setUpSubviews();
}

reportlstcontainer::~reportlstcontainer() {
    main_layout->deleteLater();
}

void reportlstcontainer::setUpSubviews() {
    main_layout = new QHBoxLayout;

    search_tree = new resourcetreewidget;
    search_tree->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    search_tree->setMinimumSize(QSize(200, 200));
    search_tree->setContentsMargins(0,0,0,0);
    main_layout->addWidget(search_tree);

    searchresulttablewidget* search_result = new searchresulttablewidget;
    search_result->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    search_result->setMinimumSize(QSize(200, 200));
    search_result->setContentsMargins(0,0,0,0);
    main_layout->addWidget(search_result);

    this->setLayout(main_layout);
}

QSize reportlstcontainer::sizeHint() const {
    return QSize(300, 300);
}
