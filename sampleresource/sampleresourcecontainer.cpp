#include "sampleresourcecontainer.h"
#include "commonwidget/resourcetreewidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <proxy/proxymanager.h>
#include <proxy/wormproxy.h>
#include <QScrollArea>
#include <commonwidget/commonimglstwidget.h>
#include "commonwidget/commonimgpreviewwidget.h"
#include <QGroupBox>

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

    QVBoxLayout* right_layout = new QVBoxLayout;

    img_preview = new commonimgpreviewwidget;
//    img_preview->setMaximumWidth(500);
    img_preview->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    right_layout->addWidget(img_preview);

    QScrollArea* area = new QScrollArea;
//    area->setMaximumSize(QSize(500, 100));
    area->setMaximumHeight(100);
    area->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    img_lst = new commonimglstwidget(true, false);
    //img_lst->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    area->setWidget(img_lst);

    right_layout->addWidget(area);

//    right_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));

    QGroupBox* box = new QGroupBox("样本描述");
    html = new QLabel;
    QVBoxLayout* a = new QVBoxLayout;
    a->addWidget(html);
    box->setLayout(a);
    right_layout->addWidget(box);

    right_layout->addSpacerItem(new QSpacerItem(0, 8, QSizePolicy::Minimum, QSizePolicy::Fixed));

    main_layout->addLayout(right_layout);
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

void sampleresourcecontainer::showEvent(QShowEvent *) {
    QObject::connect(img_lst, SIGNAL(changeCurrentImageSignal(QPixmap)),
                     img_preview, SLOT(setPreviewImage(QPixmap)));
}

void sampleresourcecontainer::hideEvent(QHideEvent *) {
    QObject::disconnect(img_lst, SIGNAL(changeCurrentImageSignal(QPixmap)),
                     img_preview, SLOT(setPreviewImage(QPixmap)));
}
