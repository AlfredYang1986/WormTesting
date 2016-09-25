#include "reportlstcontainer.h"

#include <QHBoxLayout>
//#include "searchtreewidget.h"
#include "commonwidget/resourcetreewidget.h"
#include "searchresulttablewidget.h"
#include "reportsearchconditionwidget.h"

reportlstcontainer::reportlstcontainer() {
    this->setUpSubviews();
}

reportlstcontainer::~reportlstcontainer() {
    main_layout->deleteLater();
}

void reportlstcontainer::setUpSubviews() {
    main_layout = new QHBoxLayout;

    condition_widget = new reportsearchconditionwidget;
    condition_widget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    condition_widget->setMinimumSize(QSize(200, 200));
    condition_widget->setContentsMargins(0,0,0,0);
    main_layout->addWidget(condition_widget);

    search_result = new searchresulttablewidget;
    search_result->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    search_result->setMinimumSize(QSize(200, 200));
    search_result->setContentsMargins(0,0,0,0);
    main_layout->addWidget(search_result);

    this->setLayout(main_layout);
}

QSize reportlstcontainer::sizeHint() const {
    return QSize(300, 300);
}

void reportlstcontainer::showEvent(QShowEvent *) {
    QObject::connect(condition_widget, SIGNAL(sampleConditionSearchSuccessSignal(QJsonArray)),
                     search_result, SLOT(changeSearchResult(QJsonArray)));

    QObject::connect(search_result, SIGNAL(startReport(QJsonObject)),
                     this, SLOT(startReportSlot(QJsonObject)));
}

void reportlstcontainer::hideEvent(QHideEvent *) {
    QObject::disconnect(condition_widget, SIGNAL(sampleConditionSearchSuccessSignal(QJsonArray)),
                     search_result, SLOT(changeSearchResult(QJsonArray)));
    QObject::disconnect(search_result, SIGNAL(startReport(QJsonObject)),
                     this, SLOT(startReportSlot(QJsonObject)));
}

void reportlstcontainer::startReportSlot(const QJsonObject& tmp) {
    QString str = tmp["sample_id"].toString();
    emit startReporting(str);
}
