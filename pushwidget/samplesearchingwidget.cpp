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
        header<<"样本编号"<< "导入日期";
        not_test_sample->setColumnCount(header.count());
        not_test_sample->setHorizontalHeaderLabels(header);
    }
    main_layout->addWidget(not_test_sample);

    tested_sample = new QTableWidget;
    not_test_sample->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tested_sample->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    {
        QStringList header;
        header<<"样本编号"<< "导入日期";
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

    proxymanager::instance()->getSampleProxy()->queryNotTestSample();
    proxymanager::instance()->getSampleProxy()->queryTestedSample();
}

QSize samplesearchingwidget::sizeHit() const {
    return QSize(300, 300);
}

void samplesearchingwidget::queryNotTestSamples(const QJsonArray& samples) {
    not_test_sample->clear();
    QStringList header;
    header<<"样本编号"<< "导入日期";
    not_test_sample->setColumnCount(header.count());
    not_test_sample->setHorizontalHeaderLabels(header);

    not_test_sample->setRowCount(samples.count());

    QJsonArray::const_iterator iter = samples.begin();
    int index = 0;
    for(; iter != samples.end(); ++iter) {
        QJsonObject tmp = (*iter).toObject();
        not_test_sample->setItem(index, 0, new QTableWidgetItem(tmp["sample_id"].toString()));
        qlonglong timespan = tmp["date"].toVariant().toLongLong();
        QDateTime t;
        t.setMSecsSinceEpoch(timespan);
        not_test_sample->setItem(index, 1, new QTableWidgetItem(t.toString()));
        ++index;
    }
    vec_sample_not_test = samples;
}

void samplesearchingwidget::queryTesetedSamples(const QJsonArray& samples) {
    tested_sample->clear();
    QStringList header;
    header<<"样本编号"<< "导入日期";
    tested_sample->setColumnCount(header.count());
    tested_sample->setHorizontalHeaderLabels(header);

    tested_sample->setRowCount(samples.count());

    QJsonArray::const_iterator iter = samples.begin();
    int index = 0;
    for(; iter != samples.end(); ++iter) {
        QJsonObject tmp = (*iter).toObject();
        QTableWidgetItem* item1 = new QTableWidgetItem(tmp["sample_id"].toString());
        if (tmp["status"].toInt() == 1)
            item1->setForeground(QBrush(QColor(255, 0, 0)));
        else
            item1->setForeground(QBrush(QColor(0, 0, 255)));
        tested_sample->setItem(index, 0, item1);

        qlonglong timespan = tmp["date"].toVariant().toLongLong();
        QDateTime t;
        t.setMSecsSinceEpoch(timespan);
        QTableWidgetItem* item2 = new QTableWidgetItem(t.toString());
        if (tmp["status"].toInt() == 1)
            item2->setForeground(QBrush(QColor(255, 0, 0)));
        else
            item2->setForeground(QBrush(QColor(0, 0, 255)));
        tested_sample->setItem(index, 1, item2);
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
