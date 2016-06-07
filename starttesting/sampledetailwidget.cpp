#include "sampledetailwidget.h"
#include <QFormLayout>
#include <QLineEdit>
#include <QLabel>
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

sampledetailwidget::sampledetailwidget() {
    this->setUpSubviews();
}

sampledetailwidget::~sampledetailwidget() {
    main_layout->deleteLater();
}

QSize sampledetailwidget::sizeHint() const {
    return QSize(200, 440);
}

void sampledetailwidget::setUpSubviews() {
    this->setObjectName("sample_detail_page_one");
//    this->setStyleSheet("QWidget#sample_detail_page_one { background-color: red; }");

    main_layout = new QVBoxLayout;

    QLabel* l = new QLabel("样本信息");
    l->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    main_layout->addWidget(l);

    QFormLayout* form_layout = new QFormLayout;
    form_layout->setLabelAlignment(Qt::AlignJustify);

    vector<std::pair<QString, QString> > vec;
    vec.push_back(std::make_pair("sample_id", "样本编号"));
    vec.push_back(std::make_pair("sample_index", "样本位号"));
    vec.push_back(std::make_pair("patient_name", "姓   名"));
    vec.push_back(std::make_pair("patient_gender", "性   别"));
    vec.push_back(std::make_pair("patient_age", "年    龄"));
    vec.push_back(std::make_pair("patient_id", "病 历 号"));
    vec.push_back(std::make_pair("sample_hq", "科   室"));
    vec.push_back(std::make_pair("sample_section", "病   区"));
    vec.push_back(std::make_pair("sample_bed_no", "床   号"));
    vec.push_back(std::make_pair("sample_source", "标本来源"));
    vec.push_back(std::make_pair("sample_kind", "标本种类"));
    vec.push_back(std::make_pair("sample_test_doctor", "送检医生"));

    std::for_each(vec.begin(), vec.end(), pred_row_creator(form_layout));
    main_layout->addLayout(form_layout);

    this->setLayout(main_layout);

    this->setStyleSheet("QLineEdit {"
                            "width: 110px;"
                            "height: 20px;"
                            "font-size: 14px;"
                            "border: 1px solid grey;"
                        "}");
}
