#include "sampledetailwidget.h"
#include <QFormLayout>
#include <QLineEdit>
#include <QLabel>
#include <vector>
#include <QDebug>
#include <QJsonObject>
using std::vector;

class pred_row_creator {
public:
    pred_row_creator(QFormLayout* layout, QVector<QWidget*>* input)
        : _layout(layout), _input(input) {}

    void operator()(const std::pair<QString, QString>& p) {
        QLineEdit *tmp = new QLineEdit;
        tmp->setObjectName(p.first);
        tmp->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        _layout->addRow(p.second + ":", tmp);
        _input->push_back(tmp);
    }
private:
    QFormLayout* _layout;
    QVector<QWidget*>* _input;
};

class pred_find_widget {
public:
    pred_find_widget(const QString& right) : _right(right) {}

    bool operator()(QWidget* left) {
        return left->objectName() == _right;
    }

protected:
    QString _right;
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
    vec.push_back(std::make_pair("sample_resource", "标本来源"));
    vec.push_back(std::make_pair("sample_kind", "标本种类"));
    vec.push_back(std::make_pair("sample_test_doctor", "送检医生"));

    std::for_each(vec.begin(), vec.end(), pred_row_creator(form_layout, &inputs));
    main_layout->addLayout(form_layout);
    main_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));

    this->setLayout(main_layout);

    this->setStyleSheet("QLineEdit {"
                            "width: 110px;"
                            "height: 20px;"
                            "font-size: 14px;"
                            "border: 1px solid grey;"
                        "}");

    qDebug() << "inputs are : " << inputs << endl;
}


void sampledetailwidget::currentSample(const QJsonObject& sample) {
    {
        QString sample_id = sample["sample_id"].toString();
        QVector<QWidget*>::iterator iter = std::find_if(inputs.begin(), inputs.end(),
                                                        pred_find_widget("sample_id"));
        ((QLineEdit*)(*iter))->setText(sample_id);
    }

    {
        QString patient_name = sample["patient"].toObject().operator []("patient_name").toString();
        QVector<QWidget*>::iterator iter = std::find_if(inputs.begin(), inputs.end(),
                                                       pred_find_widget("patient_name"));
        ((QLineEdit*)(*iter))->setText(patient_name);
    }

    {
        int n_patient_gender = sample["patient"].toObject().operator []("patient_gender").toInt();
        QString patient_gender = n_patient_gender == 0 ? "男" : "女";
        QVector<QWidget*>::iterator iter = std::find_if(inputs.begin(), inputs.end(),
                                                       pred_find_widget("patient_gender"));
        ((QLineEdit*)(*iter))->setText(patient_gender);
    }

    {
        int n_patient_age = sample["patient"].toObject().operator []("patient_age").toInt();
        QString patient_age = QString("%1").arg(n_patient_age);
        QVector<QWidget*>::iterator iter = std::find_if(inputs.begin(), inputs.end(),
                                                       pred_find_widget("patient_age"));
        ((QLineEdit*)(*iter))->setText(patient_age);
    }

    {
        QString sample_resource = sample["resource"].toString();
        QVector<QWidget*>::iterator iter = std::find_if(inputs.begin(), inputs.end(),
                                                        pred_find_widget("sample_resource"));
        ((QLineEdit*)(*iter))->setText(sample_resource);
    }

    current_sample = sample;
}

const QJsonObject& sampledetailwidget::queryCurrentObject() const {
    return current_sample;
}
