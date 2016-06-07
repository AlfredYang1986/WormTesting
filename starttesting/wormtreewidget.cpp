#include "wormtreewidget.h"
#include <QTreeWidgetItem>

wormtreewidget::wormtreewidget() : QTreeWidget() {
    this->setUpSubviews();
}

wormtreewidget::~wormtreewidget() {

}

void wormtreewidget::setUpSubviews() {
    this->setColumnCount(1); //设置列数
    this->setHeaderLabel(tr("虫类选择")); //设置头的标题

    QTreeWidgetItem *imageItem1 = new QTreeWidgetItem(this,QStringList(QString("虫类1")));
//    imageItem1->setIcon(0,QIcon("xxx.png"));
    QTreeWidgetItem *imageItem1_1 = new QTreeWidgetItem(imageItem1,QStringList(QString("虫子1"))); //子节点1
    imageItem1->addChild(imageItem1_1); //添加子节点

    QTreeWidgetItem *imageItem2 = new QTreeWidgetItem(this,QStringList(QString("虫类2")));
    QTreeWidgetItem *imageItem2_1 = new QTreeWidgetItem(imageItem2,QStringList(QString("虫子1"))); //子节点1
    QTreeWidgetItem *imageItem2_2 = new QTreeWidgetItem(imageItem2,QStringList(QString("虫子2"))); //子节点2
    imageItem2->addChild(imageItem2_1);  //添加子节点
    imageItem2->addChild(imageItem2_2);

    this->expandAll(); //结点全部展开

    this->setStyleSheet("QTreeWidget::branch:closed:has-children:!has-siblings,"
                        "QTreeWidget::branch:closed:has-children:has-siblings { image: url(:/resource/plus.png);}"
                        "QTreeWidget::branch:open:has-children:!has-siblings,"
                        "QTreeWidget::branch:open:has-children:has-siblings { image: url(:/resource/minus.png); }"
                        "QTreeWidget {"
                            "margin-top: 20px;"
                            "border: none;"
                        "}");
}

QSize wormtreewidget::sizeHint() const {
    return QSize(200, 440);
}
