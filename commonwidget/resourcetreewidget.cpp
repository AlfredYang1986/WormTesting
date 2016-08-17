#include "resourcetreewidget.h"
#include <QTreeWidgetItem>
#include "proxy/proxymanager.h"
#include "proxy/wormproxy.h"
#include <QJsonObject>
#include <QTreeWidgetItem>

resourcetreewidget::resourcetreewidget() : QTreeWidget() {
    this->setUpSubviews();
}

resourcetreewidget::~resourcetreewidget() {

}

void resourcetreewidget::setUpSubviews() {
    this->setColumnCount(1); //设置列数
    this->setHeaderLabel(tr("虫类选择")); //设置头的标题

//    this->expandAll(); //结点全部展开

    this->setStyleSheet("QTreeWidget::branch:closed:has-children:!has-siblings,"
                        "QTreeWidget::branch:closed:has-children:has-siblings { image: url(:/resource/plus.png);}"
                        "QTreeWidget::branch:open:has-children:!has-siblings,"
                        "QTreeWidget::branch:open:has-children:has-siblings { image: url(:/resource/minus.png); }"
                        "QTreeWidget {"
                            "margin-top: 20px;"
                            "border: none;"
                        "}");

    proxymanager::instance()->getWormProxy()->queryWormCat();

    QObject::connect(proxymanager::instance()->getWormProxy(), SIGNAL(queryWormCatSuccess(const QJsonObject&)),
                     this, SLOT(queryWormCatSuccess(const QJsonObject&)));

    QObject::connect(this, SIGNAL(itemClicked(QTreeWidgetItem*,int)),
                     this, SLOT(currentWormSlot(QTreeWidgetItem*,int)));
}

QSize resourcetreewidget::sizeHint() const {
    return QSize(200, 440);
}

void resourcetreewidget::queryWormCatSuccess(const QJsonObject& cat) {
    if (categories.isEmpty()) {
        QStringList keys = cat.keys();
        QStringList::const_iterator key = keys.begin();
        for(; key != keys.end(); ++key) {
            qDebug() << (*key) << endl;
            QTreeWidgetItem* tmp = new QTreeWidgetItem(this,QStringList((*key)));

            QJsonArray names = cat[(*key)].toArray();
            QJsonArray::const_iterator iter = names.begin();
            for (; iter != names.end(); ++iter) {
                QJsonObject obj = (*iter).toObject();
                QString name = obj["name"].toString();
                QTreeWidgetItem * sub_tmp =
                        new QTreeWidgetItem(tmp ,QStringList(name));
                tmp->addChild(sub_tmp);
            }
        }
        categories = cat;
    }
}

void resourcetreewidget::currentWormSlot(QTreeWidgetItem * item, int) {
    if (item->parent() != NULL) {
        QString worm_cat_name = item->parent()->data(0, 0).toString();
        QString worm_name = item->data(0, 0).toString();
        emit currentWormSignal(worm_name, worm_cat_name);
    }
}
