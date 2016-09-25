#include "reportingdetailwidget.h"
#include <QHBoxLayout>
#include <QFormLayout>
#include <QScrollArea>
#include <QGroupBox>
#include <QVector>
#include "proxy/wormproxy.h"
#include "proxy/proxymanager.h"
#include "reportingdetailitem.h"

class pred_reset_items {
public:
    void operator()(reportingdetailitem* item) {
        item->setCurrentSelected(false);
    }
};

class pred_remove_empty_string {
public:
    bool operator()(const QString& lhs) {
        return lhs == "";
    }
};

class pred_find_label_with_name {
public:
    pred_find_label_with_name(const QString& str) : _str(str) {}

    bool operator()(const QWidget* item) {
        return item->objectName().contains(_str);
    }

private:
    QString _str;
};

reportingdetailwidget::reportingdetailwidget() : content_widget(0), isModified(false) {
    this->setUpSubviews();
}

reportingdetailwidget::~reportingdetailwidget() {
    main_layout->deleteLater();
    area->deleteLater();
    this->clearItems();
}

void reportingdetailwidget::setUpSubviews() {
    main_layout = new QHBoxLayout;

    area = new QScrollArea;
    area->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    main_layout->addWidget(area);

    this->setLayout(main_layout);

//    proxymanager::instance()->getWormProxy()->queryReportingWorm();
}

QSize reportingdetailwidget::sizeHint() const {
    return QSize(300, 300);
}

void reportingdetailwidget::showEvent(QShowEvent *) {
    QObject::connect(proxymanager::instance()->getWormProxy(), SIGNAL(queryReportingWormSuccess(QJsonObject)),
                     this, SLOT(queryReportingWormSuccess(QJsonObject)));

    proxymanager::instance()->getWormProxy()->queryReportingWorm();
}

void reportingdetailwidget::hideEvent(QHideEvent *) {
    QObject::disconnect(proxymanager::instance()->getWormProxy(), SIGNAL(queryReportingWormSuccess(QJsonObject)),
                     this, SLOT(queryReportingWormSuccess(QJsonObject)));
}

void reportingdetailwidget::queryReportingWormSuccess(const QJsonObject & cats) {
    if (!content_widget) {

        this->clearItems();
       content_widget = new QFrame;
       content_layout = new QVBoxLayout;

        QStringList keys = cats.keys();
        QStringList::const_iterator key = keys.begin();
        for(; key != keys.end(); ++key) {

            QGroupBox* box = new QGroupBox(*key);

            QVBoxLayout* group_layout = new QVBoxLayout;
            int hint_index = 0;

            QHBoxLayout* tmp_layout = new QHBoxLayout;

            QJsonArray lst = cats[*key].toArray();
            QJsonArray::iterator iter = lst.begin();
            for (; iter != lst.end(); ++iter) {
                QString name = (*iter).toObject().operator []("name").toString();
                reportingdetailitem* tmp = new reportingdetailitem(name);
                tmp->setObjectName(*key + "/#/" + name);

                tmp_layout->addWidget(tmp);
                items.push_back(tmp);

                if (++hint_index > 1) {
                    group_layout->addLayout(tmp_layout);
                    tmp_layout = new QHBoxLayout;
                    hint_index = 0;
                }
            }

            tmp_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
            group_layout->addLayout(tmp_layout);
            box->setLayout(group_layout);
            content_layout->addWidget(box);
        }

        content_widget->setLayout(content_layout);
        area->setWidget(content_widget);
        QObject::disconnect(proxymanager::instance()->getWormProxy(), SIGNAL(queryReportingWormSuccess(QJsonObject)),
                     this, SLOT(queryReportingWormSuccess(QJsonObject)));

        if (!current_sample.isEmpty()) {
            this->setSampleDefaultResult(current_sample);
        }
    }
}

void reportingdetailwidget::clearItems() {
    QVector<reportingdetailitem*>::iterator iter = items.begin();
    for (; iter != items.end(); ++iter) {
        (*iter)->deleteLater();
    }
}

QVector<QString> reportingdetailwidget::getTestItemResults() const {
    QVector<QString> reVal;
    QVector<reportingdetailitem*>::const_iterator iter = items.begin();
    for (; iter != items.end(); ++iter) {
        reportingdetailitem* item = (*iter);
        reVal.push_back(item->getItemTestResult());
    }

    reVal.erase(std::remove_if(reVal.begin(), reVal.end(), pred_remove_empty_string()), reVal.end());
    return reVal;
}

void reportingdetailwidget::setSampleDefaultResult(const QJsonObject &sample) {

    std::for_each(items.begin(), items.end(), pred_reset_items());

    current_sample = sample;
    QJsonArray result = sample["result"].toArray();
    QJsonArray::iterator iter = result.begin();
    for (; iter != result.end(); ++iter) {
        QString cur = (*iter).toString();
        QVector<reportingdetailitem*>::iterator iter =
                std::find_if(items.begin(), items.end(), pred_find_label_with_name(cur));

        if (iter != items.end()) {
            reportingdetailitem* item = (*iter);
            if (item)
                item->setCurrentSelected(true);
        }
    }
}

QStringList reportingdetailwidget::getAllReportingField() const {
    QStringList reVal;
    QVector<reportingdetailitem*> ::const_iterator iter = items.begin();
    for (; iter != items.end(); ++iter) {
        reVal.push_back((*iter)->getItemTitle());
    }
    return reVal;
}
