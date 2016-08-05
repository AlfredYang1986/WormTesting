#include "samplesearchingwidget.h"
#include <QVBoxLayout>
#include <QTableWidget>
#include <QTableWidgetItem>
#include "proxy/proxymanager.h"
#include "proxy/sampleproxy.h"

samplesearchingwidget::samplesearchingwidget() {
    this->setUpSubviews();
}

samplesearchingwidget::~samplesearchingwidget() {
    main_layout->deleteLater();
    not_test_sample->deleteLater();
    tested_sample->deleteLater();
}

void samplesearchingwidget::setUpSubviews() {
    main_layout = new QVBoxLayout;

    not_test_sample = new QTableWidget;
    not_test_sample->setEditTriggers(QAbstractItemView::NoEditTriggers);
    not_test_sample->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    {
        QStringList header;
//        header<<"样本编号"<<"姓名" << "年龄" << "样本来源" << "样本总类" << "送检医生" << "审核医生" << "日期";
        header<<"病人编号"<<"姓名" << "年龄" << "样本编号" << "样本类型" << "送检医生" << "检测医生" << "日期";
        not_test_sample->setColumnCount(header.count());
        not_test_sample->setHorizontalHeaderLabels(header);
    }
    main_layout->addWidget(not_test_sample);

    tested_sample = new QTableWidget;
    tested_sample->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tested_sample->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    {
        QStringList header;
//        header<<"样本编号"<<"姓名" << "年龄" << "样本来源" << "样本总类" << "送检医生" << "审核医生" << "日期";
        header<<"病人编号"<<"姓名" << "年龄" << "样本编号" << "样本类型" << "送检医生" << "检测医生" << "日期";
        tested_sample->setColumnCount(header.count());
        tested_sample->setHorizontalHeaderLabels(header);
    }
    main_layout->addWidget(tested_sample);

    this->setLayout(main_layout);

    QObject::connect(proxymanager::instance()->getSampleProxy(), SIGNAL(queryNotTestSampleSuccess(const QJsonArray&)),
                     this, SLOT(queryNotTestSamples(const QJsonArray&)));
    QObject::connect(proxymanager::instance()->getSampleProxy(), SIGNAL(queryTestedSampleSuccess(const QJsonArray&)),
                     this, SLOT(queryTesetedSamples(const QJsonArray&)));

    QObject::connect(not_test_sample, SIGNAL(clicked(const QModelIndex&)),
                     this, SLOT(notTestWidgetClicked(const QModelIndex&)));
    QObject::connect(tested_sample, SIGNAL(clicked(const QModelIndex&)),
                     this, SLOT(testedWidgetClicked(const QModelIndex&)));

    QObject::connect(not_test_sample, SIGNAL(doubleClicked(const QModelIndex&)),
                     this, SLOT(notTestWidgetDoubleClicked(const QModelIndex&)));
    QObject::connect(tested_sample, SIGNAL(doubleClicked(const QModelIndex&)),
                     this, SLOT(testedWidgetDoubleClicked(const QModelIndex&)));

//    proxymanager::instance()->getSampleProxy()->queryNotTestSample();
//    proxymanager::instance()->getSampleProxy()->queryTestedSample();
}

QSize samplesearchingwidget::sizeHit() const {
    return QSize(300, 300);
}

void samplesearchingwidget::queryNotTestSamples(const QJsonArray& samples) {
    not_test_sample->clear();
    QStringList header;
//    header<<"样本编号"<<"姓名" << "年龄" << "样本来源" << "样本总类" << "送检医生" << "审核医生" << "日期";
    header<<"病人编号"<<"姓名" << "年龄" << "样本编号" << "样本类型" << "送检医生" << "检测医生" << "日期";
    not_test_sample->setColumnCount(header.count());
    not_test_sample->setHorizontalHeaderLabels(header);

    not_test_sample->setRowCount(samples.count());

    QJsonArray::const_iterator iter = samples.begin();
    int index = 0;
    for(; iter != samples.end(); ++iter) {
        QJsonObject tmp = (*iter).toObject();
        QJsonObject patient = tmp["patient"].toObject();
        not_test_sample->setItem(index, 0, new QTableWidgetItem(patient["patient_id"].toString()));
        not_test_sample->setItem(index, 1, new QTableWidgetItem(patient["patient_name"].toString()));
        not_test_sample->setItem(index, 2, new QTableWidgetItem(QString("%1").arg(patient["patient_age"].toInt())));
        not_test_sample->setItem(index, 3, new QTableWidgetItem(tmp["sample_id"].toString()));
        not_test_sample->setItem(index, 4, new QTableWidgetItem(tmp["resource"].toString()));
        not_test_sample->setItem(index, 5, new QTableWidgetItem(tmp["query_doctor"].toString()));
        not_test_sample->setItem(index, 6, new QTableWidgetItem(tmp["testing_doctor"].toString()));

        qlonglong timespan = tmp["date"].toVariant().toLongLong() * 1000 * 24 * 60 * 60;
        QDateTime t;
        t.setMSecsSinceEpoch(timespan);
        QString format = "MM-dd-yyyy";
        not_test_sample->setItem(index, 7, new QTableWidgetItem(t.toString(format)));
        ++index;
    }
    vec_sample_not_test = samples;
}

void samplesearchingwidget::queryTesetedSamples(const QJsonArray& samples) {
    tested_sample->clear();
    QStringList header;
//    header<<"样本编号"<<"姓名" << "年龄" << "样本来源" << "样本总类" << "送检医生" << "审核医生" << "日期";
    header<<"病人编号"<<"姓名" << "年龄" << "样本编号" << "样本类型" << "送检医生" << "检测医生" << "日期";
    tested_sample->setColumnCount(header.count());
    tested_sample->setHorizontalHeaderLabels(header);

    tested_sample->setRowCount(samples.count());

    QJsonArray::const_iterator iter = samples.begin();
    int index = 0;
    for(; iter != samples.end(); ++iter) {
        QJsonObject tmp = (*iter).toObject();
        QJsonObject patient = tmp["patient"].toObject();

        {
            QTableWidgetItem* item1 = new QTableWidgetItem(patient["patient_id"].toString());
            if (tmp["status"].toInt() == 1)
                item1->setForeground(QBrush(QColor(255, 0, 0)));
            else
                item1->setForeground(QBrush(QColor(0, 0, 255)));
            tested_sample->setItem(index, 0, item1);
        }

        {
            QTableWidgetItem* item1 = new QTableWidgetItem(patient["patient_name"].toString());
            if (tmp["status"].toInt() == 1)
                item1->setForeground(QBrush(QColor(255, 0, 0)));
            else
                item1->setForeground(QBrush(QColor(0, 0, 255)));
            tested_sample->setItem(index, 1, item1);
        }

        {
            QTableWidgetItem* item1 = new QTableWidgetItem(QString("%1").arg(patient["patient_age"].toInt()));
            if (tmp["status"].toInt() == 1)
                item1->setForeground(QBrush(QColor(255, 0, 0)));
            else
                item1->setForeground(QBrush(QColor(0, 0, 255)));
            tested_sample->setItem(index, 2, item1);
        }

        {
            QTableWidgetItem* item1 = new QTableWidgetItem(tmp["sample_id"].toString());
            if (tmp["status"].toInt() == 1)
                item1->setForeground(QBrush(QColor(255, 0, 0)));
            else
                item1->setForeground(QBrush(QColor(0, 0, 255)));
            tested_sample->setItem(index, 3, item1);
        }

        {
            QTableWidgetItem* item1 = new QTableWidgetItem(tmp["resource"].toString());
            if (tmp["status"].toInt() == 1)
                item1->setForeground(QBrush(QColor(255, 0, 0)));
            else
                item1->setForeground(QBrush(QColor(0, 0, 255)));
            tested_sample->setItem(index, 4, item1);
        }

        {
            QTableWidgetItem* item1 = new QTableWidgetItem(tmp["query_doctor"].toString());
            if (tmp["status"].toInt() == 1)
                item1->setForeground(QBrush(QColor(255, 0, 0)));
            else
                item1->setForeground(QBrush(QColor(0, 0, 255)));
            tested_sample->setItem(index, 5, item1);
        }

        {
            QTableWidgetItem* item1 = new QTableWidgetItem(tmp["testing_doctor"].toString());
            if (tmp["status"].toInt() == 1)
                item1->setForeground(QBrush(QColor(255, 0, 0)));
            else
                item1->setForeground(QBrush(QColor(0, 0, 255)));
            tested_sample->setItem(index, 6, item1);
        }

        {
            qlonglong timespan = tmp["date"].toVariant().toLongLong() * 1000 * 24 * 60 * 60;
            QDateTime t;
            t.setMSecsSinceEpoch(timespan);
            QString format = "MM-dd-yyyy";
            QTableWidgetItem* item2 = new QTableWidgetItem(t.toString(format));
            if (tmp["status"].toInt() == 1)
                item2->setForeground(QBrush(QColor(255, 0, 0)));
            else
                item2->setForeground(QBrush(QColor(0, 0, 255)));
            tested_sample->setItem(index, 7, item2);
        }
        ++index;
    }
    vec_sample_tested = samples;
}

void samplesearchingwidget::notTestWidgetClicked(const QModelIndex& index) {
    QJsonObject sample = vec_sample_not_test.at(index.row()).toObject();
    emit currentSample(sample);
}

void samplesearchingwidget::testedWidgetClicked(const QModelIndex& index) {
    QJsonObject sample = vec_sample_tested.at(index.row()).toObject();
    emit currentSample(sample);
}

void samplesearchingwidget::notTestWidgetDoubleClicked(const QModelIndex & index) {
    QJsonObject sample = vec_sample_not_test.at(index.row()).toObject();
    emit doubleSelectSample(sample);
}

void samplesearchingwidget::testedWidgetDoubleClicked(const QModelIndex & index) {
    QJsonObject sample = vec_sample_tested.at(index.row()).toObject();
    emit doubleSelectSample(sample);
}

void samplesearchingwidget::reloadData() {
    proxymanager::instance()->getSampleProxy()->queryNotTestSample();
    proxymanager::instance()->getSampleProxy()->queryTestedSample();
}

void samplesearchingwidget::showEvent(QShowEvent *) {
    this->reloadData();
}
