#include "searchresulttablewidget.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QDateTime>
#include <QDebug>

searchresulttablewidget::searchresulttablewidget() {
    this->setUpSubviews();
}

searchresulttablewidget::~searchresulttablewidget() {

}

void searchresulttablewidget::setUpSubviews() {
    QStringList header;
    header<< QStringLiteral("样本编号")
          << QStringLiteral("姓名")
          << QStringLiteral("年龄")
          << QStringLiteral("样本来源")
//          << QStringLiteral("样本总类")
          << QStringLiteral("送检医生")
          << QStringLiteral("审核医生")
          << QStringLiteral("日期");
    this->setColumnCount(header.count());
    this->setHorizontalHeaderLabels(header);

    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QObject::connect(this, SIGNAL(doubleClicked(QModelIndex)),
                     this, SLOT(reportSearchResult(QModelIndex)));
}

QSize searchresulttablewidget::sizeHint() const {
    return QSize(300, 300);
}

void searchresulttablewidget::changeSearchResult(const QJsonArray & result) {
    this->clearSearchResult();
    current_result = result;

    this->setRowCount(result.count());
    QJsonArray::const_iterator iter = result.begin();
    int index = 0;
    for (; iter != result.end(); ++iter) {
        QJsonObject tmp = (*iter).toObject();
        QJsonObject patient = tmp["patient"].toObject();
        this->setItem(index, 0, new QTableWidgetItem(tmp["sample_id"].toString()));
        this->setItem(index, 1, new QTableWidgetItem(patient["patient_name"].toString()));
        this->setItem(index, 2, new QTableWidgetItem(QString("%1").arg(patient["patient_age"].toInt())));
        this->setItem(index, 3, new QTableWidgetItem(tmp["resource"].toString()));
        this->setItem(index, 4, new QTableWidgetItem(tmp["testing_doctor"].toString()));
        this->setItem(index, 5, new QTableWidgetItem(QString("%1").arg(patient["date"].toDouble())));

        qlonglong timespan = tmp["date"].toVariant().toLongLong();
        QDateTime t;
        t.setMSecsSinceEpoch(timespan * 24 * 60 * 60 * 1000);
        QString format = "MM-dd-yyyy";
        this->setItem(index, 6, new QTableWidgetItem(t.toString(format)));
        ++index;
    }
}

void searchresulttablewidget::clearSearchResult() {
    this->clear();
    QStringList header;
    header<< QStringLiteral("样本编号")
          << QStringLiteral("姓名")
          << QStringLiteral("年龄")
          << QStringLiteral("样本来源")
//          << QStringLiteral("样本总类")
          << QStringLiteral("送检医生")
          << QStringLiteral("审核医生")
          << QStringLiteral("日期");

    this->setColumnCount(header.count());   //设置列数为5
    this->setHorizontalHeaderLabels(header);
}

void searchresulttablewidget::reportSearchResult(QModelIndex index) {
    QJsonObject tmp = current_result.at(index.row()).toObject();
    qDebug() << tmp << endl;
    emit startReport(tmp);
}
