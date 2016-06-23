#include "reportingdetailcontainer.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QButtonGroup>
#include <QLabel>
#include <QCheckBox>
#include <QSpacerItem>
#include "reportingdetailcontainer.h"
#include "detailpane.h"
#include "samplereportingpane.h"
#include <proxy/proxymanager.h>
#include <proxy/wormproxy.h>
#include <proxy/sampleproxy.h>

reportingdetailcontainer::reportingdetailcontainer() {
    this->setUpSubviews();
}

reportingdetailcontainer::~reportingdetailcontainer() {
    main_layout->deleteLater();
    detail_layout->deleteLater();
}

void reportingdetailcontainer::setUpSubviews() {
    main_layout = new QVBoxLayout;
    main_layout->setContentsMargins(0,0,0,0);

    sample_pane = new samplereportingpane;
    sample_pane->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    main_layout->addWidget(sample_pane);

    QHBoxLayout* group_layout = new QHBoxLayout;

    QLabel* label = new QLabel("虫子类型 : ");
    group_layout->addWidget(label);
    QSpacerItem* margin_between = new QSpacerItem(60, 0, QSizePolicy::Fixed, QSizePolicy::Minimum);
    group_layout->addSpacerItem(margin_between);

    QCheckBox* check_btn_0 = new QCheckBox("虫类1");
    check_btn_0->setChecked(true);
    group_layout->addWidget(check_btn_0);
    QObject::connect(check_btn_0, SIGNAL(clicked()), this, SLOT(checkBtnClicked()));
    detail_vec.push_back(check_btn_0);

    QCheckBox* check_btn_1 = new QCheckBox("虫类2");
    check_btn_1->setChecked(true);
    group_layout->addWidget(check_btn_1);
    QObject::connect(check_btn_1, SIGNAL(clicked()), this, SLOT(checkBtnClicked()));
    detail_vec.push_back(check_btn_1);

    group_layout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Expanding, QSizePolicy::Minimum));

    main_layout->addLayout(group_layout);

    detail_layout = new QVBoxLayout;

    {
        vector<QString> tmp_vec_0;
        tmp_vec_0.push_back("虫类1-1");
        tmp_vec_0.push_back("虫类1-2");
        detailpane* tmp_0 = new detailpane(tmp_vec_0);
        detail_layout->addWidget(tmp_0);

        detail_vec_pane[QStringLiteral("虫类1")] = tmp_0;

        vector<QString> tmp_vec_1;
        tmp_vec_1.push_back("虫类2-1");
        tmp_vec_1.push_back("虫类2-2");
        detailpane* tmp_1 = new detailpane(tmp_vec_1);
        detail_layout->addWidget(tmp_1);

        detail_vec_pane[QStringLiteral("虫类2")] = tmp_1;
    }

    main_layout->addLayout(detail_layout);

    QSpacerItem* spacer_bottom = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    main_layout->addSpacerItem(spacer_bottom);

    this->setLayout(main_layout);

    this->setStyleSheet("QWidget {"
                            "font-size: 12px;"
                        "}");

    QObject::connect(proxymanager::instance()->getSampleProxy(), SIGNAL(querySampleWithIDSuccess(const QJsonObject&)),
                     this, SLOT(querySampleWithIDSuccess(const QJsonObject&)));
}

QSize reportingdetailcontainer::sizeHint() const {
    return QSize(100, 100);
}

void reportingdetailcontainer::checkBtnClicked() {
    map<QString, detailpane*>::iterator iter = detail_vec_pane.begin();
    for (; iter != detail_vec_pane.end(); ++iter) {
        detailpane* tmp = (*iter).second;
        tmp->hide();
    }

    vector<QCheckBox*>::iterator iter_check = detail_vec.begin();
    for (; iter_check != detail_vec.end(); ++iter_check) {
        QCheckBox* btn = (*iter_check);
        if (btn->isChecked()) {
            QString title = btn->text();
            detailpane* tmp = detail_vec_pane[title];
            if (tmp) tmp->show();
        }
    }
}

void reportingdetailcontainer::querySampleWithIDSuccess(const QJsonObject& sample) {
    current_sample = sample;
    sample_pane->fillInputs(sample);
    emit changeCurrentSample(sample);
}
