#include "sampleresourcecontainer.h"
#include "resourcetreewidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <proxy/proxymanager.h>
#include <proxy/wormproxy.h>

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

    QVBoxLayout* content_layout = new QVBoxLayout;

    html = new QLabel("<h2>test</h2>");
    html->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    content_layout->addWidget(html);
    content_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));
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
}
