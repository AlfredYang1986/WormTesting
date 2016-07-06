#include "sampleresourcecontainer.h"
#include "commonwidget/resourcetreewidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <proxy/proxymanager.h>
#include <proxy/wormproxy.h>
#include <commonwidget/commonimglstwidget.h>

sampleresourcecontainer::sampleresourcecontainer() {
    this->setUpSubviews();
}

sampleresourcecontainer::~sampleresourcecontainer() {
    main_layout->deleteLater();
}

void sampleresourcecontainer::setUpSubviews() {
    main_layout = new QHBoxLayout;

    resourcetreewidget* tree = new resourcetreewidget;
    tree->setMinimumSize(QSize(200, 200));
    tree->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    main_layout->addWidget(tree);

    QHBoxLayout* content_layout = new QHBoxLayout;

    html = new QLabel;
    html->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    content_layout->addWidget(html);
//    content_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));

    img_lst = new commonimglstwidget;
    img_lst->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    content_layout->addWidget(img_lst);

    main_layout->addLayout(content_layout);
    this->setLayout(main_layout);

    QObject::connect(tree, SIGNAL(currentWormSignal(const QString&, const QString&)),
                     this, SLOT(currentWorm(const QString&, const QString&)));

    QObject::connect(proxymanager::instance()->getWormProxy(), SIGNAL(queryWormSuccess(const QJsonObject&)),
                     this, SLOT(queryWormDetailSuccess(const QJsonObject&)));
}

QSize sampleresourcecontainer::sizeHint() const {
    return QSize(300, 300);
}

void sampleresourcecontainer::currentWorm(const QString& worm_name, const QString& worm_cat_name) {
    proxymanager::instance()->getWormProxy()->queryWorm(worm_name, worm_cat_name);
}

void sampleresourcecontainer::queryWormDetailSuccess(const QJsonObject& detail) {
    qDebug() << detail << endl;
    QString tmp("<h2>虫名</h2>");
    tmp += "<p>";
    tmp += detail["name"].toString();
    tmp += "</p>";

    tmp += "<br/><h2>虫类</h2>";
    tmp += "<p>";
    tmp += detail["cat"].toString();
    tmp += "</p>";

    tmp += "<br/><h2>描述</h2>";
    tmp += "<p>";
    tmp += detail["description"].toString();
    tmp += "</p>";

    html->setText(tmp);

    QVector<QVariant> images_var = detail["img_lst"].toArray().toVariantList().toVector();
    QVector<QString> images;
    QVector<QVariant>::iterator iter = images_var.begin();
    for (; iter != images_var.end(); ++iter) {
        images.push_back((*iter).toString());
    }
    img_lst->changeShowingImgLst(images);
}
