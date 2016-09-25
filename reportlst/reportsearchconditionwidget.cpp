#include "reportsearchconditionwidget.h"
#include <QFormLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QComboBox>
#include <QPushButton>
#include <QLineEdit>
#include "proxy/proxymanager.h"
#include "proxy/wormproxy.h"
#include "proxy/sampleproxy.h"
#include "proxy/authproxy.h"
#include <QDateEdit>

reportsearchconditionwidget::reportsearchconditionwidget() {
    this->setUpSubviews();
}

reportsearchconditionwidget::~reportsearchconditionwidget() {
    main_layout->deleteLater();
}

QSize reportsearchconditionwidget::sizeHint() const {
    return QSize(200, 300);
}

void reportsearchconditionwidget::setUpSubviews() {

    gb = new QGroupBox(QStringLiteral("检索条件"));

   time_box = new QDateEdit;
   time_box->setDisplayFormat("MM-dd-yyyy");
   time_box->setDate(QDate::currentDate());

   time_box_end = new QDateEdit;
   time_box_end->setDisplayFormat("MM-dd-yyyy");
   time_box_end->setDate(QDate::currentDate());

//    time_box->addItem("--------------");
//    time_box->addItem(QStringLiteral("当天"));
//    time_box->addItem(QStringLiteral("当周"));
//    time_box->addItem(QStringLiteral("当月"));

    testing_doctor_box = new QComboBox;
    testing_doctor_box->addItem("--------------");

    doctor_box = new QComboBox;
    doctor_box->addItem("--------------");

    worm_box = new QComboBox;
    worm_box->addItem("--------------");

    sample_id_edit = new QLineEdit;
    patient_id_edit = new QLineEdit;
    patient_name_edit = new QLineEdit;
    patient_age_edit = new QLineEdit;
    patient_section_edit = new QLineEdit;

    QFormLayout* content_layout = new QFormLayout;

    content_layout->addRow(QStringLiteral("时间"), time_box);
    content_layout->addRow(QStringLiteral("检测医生"), testing_doctor_box);
    content_layout->addRow(QStringLiteral("审核医生"), doctor_box);
    content_layout->addRow(QStringLiteral("虫子名称"), worm_box);

    content_layout->addRow(QStringLiteral("样本编号"), sample_id_edit);
    content_layout->addRow(QStringLiteral("病人姓名"), patient_name_edit);
    content_layout->addRow(QStringLiteral("病人编号"), patient_id_edit);
    content_layout->addRow(QStringLiteral("年   龄"), patient_age_edit);
    content_layout->addRow(QStringLiteral("科   室"), patient_section_edit);

    gb->setLayout(content_layout);

    main_layout = new QVBoxLayout;
    main_layout->addWidget(gb);

    QHBoxLayout* btn_layout = new QHBoxLayout;
    btn_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
    QPushButton* search_btn = new QPushButton(QStringLiteral("搜索"));
    btn_layout->addWidget(search_btn);
    btn_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
    main_layout->addLayout(btn_layout);

    main_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));

    this->setLayout(main_layout);

    proxymanager::instance()->getWormProxy()->queryWormCat();

    this->setStyleSheet("QPushButton {"
                            "width: 80px;"
                            "height: 30px;"
                            "color: white;"
                            "font-size: 14px;"
                            "background-color: #1bd7ff;"
                            "border: 1px solid #1bd7ff;"
                        "}");

    QObject::connect(search_btn, SIGNAL(released()), this, SLOT(searchBtnClicked()));

    QObject::connect(proxymanager::instance()->getAuthProxy(), SIGNAL(queryNormalDoctorSuccess(QVector<QString>)),
                     this, SLOT(queryNormalDoctorSuccess(QVector<QString>)));
    QObject::connect(proxymanager::instance()->getAuthProxy(), SIGNAL(queryAdjustDoctorSuccess(QVector<QString>)),
                     this, SLOT(queryAdjustDoctorSuccess(QVector<QString>)));

    proxymanager::instance()->getAuthProxy()->lstNormalDoctorsRemote();
    proxymanager::instance()->getAuthProxy()->lstTestedDoctorsRemote();
}


void reportsearchconditionwidget::showEvent(QShowEvent *) {
    QObject::connect(proxymanager::instance()->getWormProxy(), SIGNAL(queryWormCatSuccess(QJsonObject)),
                     this, SLOT(queryWormCatSuccess(QJsonObject)));

    QObject::connect(proxymanager::instance()->getSampleProxy(), SIGNAL(sampleConditionSearchSuccess(QJsonArray)),
                     this, SLOT(sampleConditionSearchSuccess(QJsonArray)));
}

void reportsearchconditionwidget::hideEvent(QHideEvent *) {
    QObject::disconnect(proxymanager::instance()->getWormProxy(), SIGNAL(queryWormCatSuccess(QJsonObject)),
                     this, SLOT(queryWormCatSuccess(QJsonObject)));

    QObject::disconnect(proxymanager::instance()->getSampleProxy(), SIGNAL(sampleConditionSearchSuccess(QJsonArray)),
                     this, SLOT(sampleConditionSearchSuccess(QJsonArray)));
}

void  reportsearchconditionwidget::queryWormCatSuccess(const QJsonObject & cats) {
    QStringList keys = cats.keys();
    QStringList::iterator key = keys.begin();
    for (; key != keys.end(); ++key) {
        QJsonArray arr = cats[*key].toArray();

        QJsonArray::iterator iter = arr.begin();
        for (; iter != arr.end(); ++iter) {
            QString name = (*iter).toObject()["name"].toString();
            worm_box->addItem(name);
        }
    }
}

void reportsearchconditionwidget::searchBtnClicked() {
    QJsonObject conditions;
    this->pushConditions(conditions);
    proxymanager::instance()->getSampleProxy()->searchSamplesWithConditions(conditions);
}

void reportsearchconditionwidget::pushConditions(QJsonObject & conditions) {
    if (!time_box->text().isEmpty()) {
//        conditions
        QString date = time_box->text();
        QString format = "MM-dd-yyyy";
        QDateTime t = QDateTime::fromString(date, format);
        qlonglong l = t.toMSecsSinceEpoch();
//        conditions.insert("date", (qlonglong)(l / 24 * 60 * 60 * 1000));
        conditions.insert("time", l + 1);
    }

    if (!time_box_end->text().isEmpty()) {
//        conditions
        QString date = time_box->text();
        QString format = "MM-dd-yyyy";
        QDateTime t = QDateTime::fromString(date, format);
        qlonglong l = t.toMSecsSinceEpoch();
//        conditions.insert("date", (qlonglong)(l / 24 * 60 * 60 * 1000));
        conditions.insert("time_end", l + 1);
    }

    if (testing_doctor_box->currentIndex() > 0) {
        conditions.insert("testing_doctor", testing_doctor_box->currentText());
    }

    if (doctor_box->currentIndex() > 0) {
        conditions.insert("post_test_doctor", doctor_box->currentText());
    }

    if (worm_box->currentIndex() > 0) {
        conditions.insert("worm", worm_box->currentText());
    }

    if (!sample_id_edit->text().isEmpty()) {
        conditions.insert("sample_id", sample_id_edit->text());
    }

    if (!patient_id_edit->text().isEmpty()) {
        conditions.insert("patient_id", patient_id_edit->text());
    }

    if (!patient_name_edit->text().isEmpty()) {
        conditions.insert("patient_name", patient_name_edit->text());
    }

    if (!patient_age_edit->text().isEmpty()) {
        conditions.insert("patient_age", patient_age_edit->text().toInt());
    }
    qDebug() << conditions << endl;
}

void reportsearchconditionwidget::sampleConditionSearchSuccess(const QJsonArray & result) {
    qDebug() << result << endl;
    emit sampleConditionSearchSuccessSignal(result);
}

void reportsearchconditionwidget::queryNormalDoctorSuccess(const QVector<QString>& vec) {
    testing_doctor_box->clear();
    testing_doctor_box->addItem("--------------");

    QVector<QString>::const_iterator iter = vec.begin();
    for (; iter != vec.end(); ++iter) {
        testing_doctor_box->addItem(*iter);
    }
}

void reportsearchconditionwidget::queryAdjustDoctorSuccess(const QVector<QString>& vec) {
    doctor_box->clear();
    doctor_box->addItem("--------------");

    QVector<QString>::const_iterator iter = vec.begin();
    for (; iter != vec.end(); ++iter) {
        doctor_box->addItem(*iter);
    }
}
