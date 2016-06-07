#include "searchresulttablewidget.h"

searchresulttablewidget::searchresulttablewidget() {
    this->setUpSubviews();
}

searchresulttablewidget::~searchresulttablewidget() {

}

void searchresulttablewidget::setUpSubviews() {
    QStringList header;
    header<<"样本编号"<<"姓名" << "年龄" << "样本来源" << "样本总类" << "送检医生" << "审核医生" << "日期";
    this->setColumnCount(header.count());   //设置列数为5
    this->setHorizontalHeaderLabels(header);
}
