#include "samplereportingpane.h"

#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <vector>
#include <QDebug>
#include <proxy/proxymanager.h>
#include <proxy/sampleproxy.h>
#include <QMessageBox>
using std::vector;

class pred_row_creator_2 {
public:
    pred_row_creator_2(QFormLayout* layout, QVector<QWidget*>* inputs)
        : _layout(layout), _inputs(inputs) {}

    void operator()(const std::pair<QString, QString>& p) {
        QLineEdit *tmp = new QLineEdit;
        tmp->setObjectName(p.first);
        tmp->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        _layout->addRow(p.second + ":", tmp);
        _inputs->push_back(tmp);
    }
private:
    QFormLayout* _layout;
    QVector<QWidget*>* _inputs;
};

class pred_find_input_with_name {
public:
    pred_find_input_with_name(const QString& name) : _name(name) {}

    bool operator()(QWidget* lhs) {
        return lhs->objectName() == _name;
    }

private:
    QString _name;
};

samplereportingpane::samplereportingpane() {
    this->setUpSubviews();
}

samplereportingpane::~samplereportingpane() {
    main_layout->deleteLater();
}

void samplereportingpane::setUpSubviews() {

    main_layout = new QHBoxLayout;

    {
        QFormLayout* form_layout = new QFormLayout;
        form_layout->setLabelAlignment(Qt::AlignJustify);

        vector<std::pair<QString, QString> > vec;
        vec.push_back(std::make_pair("sample_id", "样本编号"));
        vec.push_back(std::make_pair("sample_test_doctor", "送检医生"));
        vec.push_back(std::make_pair("sample_test_date", "送检日期"));
        vec.push_back(std::make_pair("sample_test_result", "临床诊断"));

        std::for_each(vec.begin(), vec.end(), pred_row_creator_2(form_layout, &inputs));
        main_layout->addLayout(form_layout);
    }

    {
        QFormLayout* form_layout = new QFormLayout;
        form_layout->setLabelAlignment(Qt::AlignJustify);

        vector<std::pair<QString, QString> > vec;
        vec.push_back(std::make_pair("patient_id", "病 历 号"));
        vec.push_back(std::make_pair("patient_name", "病人姓名"));
        vec.push_back(std::make_pair("sample_check_doctor", "检测医生"));
        vec.push_back(std::make_pair("sample_check_date", "报告日期"));
        vec.push_back(std::make_pair("sample_description", "报告备注"));

        std::for_each(vec.begin(), vec.end(), pred_row_creator_2(form_layout, &inputs));
        main_layout->addLayout(form_layout);
    }

    QVBoxLayout* btn_layout =  new QVBoxLayout;

    QPushButton* start_btn = new QPushButton("开始填写报告");
    QObject::connect(start_btn, SIGNAL(released()), this, SLOT(startReporting()));
    btn_layout->addWidget(start_btn);

    QPushButton* end_btn = new QPushButton("完成填写报告");
    QObject::connect(end_btn, SIGNAL(released()), this, SLOT(endReporting()));
    btn_layout->addWidget(end_btn);

    main_layout->addLayout(btn_layout);

    main_layout->addSpacerItem(new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Minimum));

    this->setLayout(main_layout);
}

QSize samplereportingpane::sizeHint() const {
    return QSize(300, 100);
}

void samplereportingpane::startReporting() {
    QVector<QWidget*>::const_iterator iter = std::find_if(inputs.begin(), inputs.end(), pred_find_input_with_name("sample_id"));
    QString sample_id = ((QLineEdit*)(*iter))->text();

    if (!sample_id.isEmpty()) {
        proxymanager::instance()->getSampleProxy()->querySampleWithID(sample_id);
    } else {
        QMessageBox::information(this, "Error",
                                 tr("请填写样本编号"),
                                 QMessageBox::Ok, QMessageBox::Ok);
    }

}

void samplereportingpane::endReporting() {

}

void samplereportingpane::fillInputs(const QJsonObject &sample) {
    {
        QVector<QWidget*>::const_iterator iter = std::find_if(inputs.begin(), inputs.end(), pred_find_input_with_name("sample_id"));
        QString sample_id = sample["sample_id"].toString();
        ((QLineEdit*)(*iter))->setText(sample_id);
    }

    {
        QVector<QWidget*>::const_iterator iter = std::find_if(inputs.begin(), inputs.end(), pred_find_input_with_name("sample_test_date"));
        qlonglong timespan = sample["date"].toVariant().toLongLong();
        QDateTime t;
        t.setMSecsSinceEpoch(timespan);
        ((QLineEdit*)(*iter))->setText(t.toString());
    }

    QJsonObject patient = sample["patient"].toObject();
    {
        QVector<QWidget*>::const_iterator iter = std::find_if(inputs.begin(), inputs.end(), pred_find_input_with_name("patient_name"));
        QString patient_name = patient["patient_name"].toString();
        ((QLineEdit*)(*iter))->setText(patient_name);
    }
}
