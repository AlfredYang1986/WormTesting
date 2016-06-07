#include "samplereportingpane.h"

#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <vector>
using std::vector;

class pred_row_creator {
public:
    pred_row_creator(QFormLayout* layout) : _layout(layout) {}

    void operator()(const std::pair<QString, QString>& p) {
        QLineEdit *tmp = new QLineEdit;
        tmp->setObjectName(p.first);
        tmp->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        _layout->addRow(p.second + ":", tmp);
    }
private:
    QFormLayout* _layout;
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

        std::for_each(vec.begin(), vec.end(), pred_row_creator(form_layout));
        main_layout->addLayout(form_layout);
    }

    {
        QFormLayout* form_layout = new QFormLayout;
        form_layout->setLabelAlignment(Qt::AlignJustify);

        vector<std::pair<QString, QString> > vec;
        vec.push_back(std::make_pair("patient_id", "病 历 号"));
        vec.push_back(std::make_pair("sample_check_doctor", "检测医生"));
        vec.push_back(std::make_pair("sample_check_date", "报告日期"));
        vec.push_back(std::make_pair("sample_description", "报告备注"));

        std::for_each(vec.begin(), vec.end(), pred_row_creator(form_layout));
        main_layout->addLayout(form_layout);
    }

    main_layout->addSpacerItem(new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Minimum));

    this->setLayout(main_layout);
}

QSize samplereportingpane::sizeHint() const {
    return QSize(300, 100);
}
