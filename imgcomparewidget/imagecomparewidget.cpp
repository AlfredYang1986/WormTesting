#include "imagecomparewidget.h"
#include "commonwidget/commonimglstwidget.h"
#include "commonwidget/commonimgpreviewwidget.h"
#include <QLabel>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QLineEdit>
#include "proxy/proxymanager.h"
#include "proxy/wormproxy.h"
#include "proxy/sampleproxy.h"
#include <QScrollArea>

imagecomparewidget::imagecomparewidget() {
    this->setUpSubviews();
}

imagecomparewidget::~imagecomparewidget() {
    main_layout->deleteLater();
}

QSize imagecomparewidget::sizeHint() const {
    return QSize(300, 300);
}

void imagecomparewidget::setUpSubviews() {
    main_layout = new QHBoxLayout;

    {
        QVBoxLayout* left_layout = new QVBoxLayout;

        box = new QComboBox;
        left_layout->addWidget(box);

        worm_preview = new commonimgpreviewwidget;
        worm_preview->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        left_layout->addWidget(worm_preview);

        QScrollArea* area = new QScrollArea;
        area->setMaximumHeight(100);
        area->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

        worm_resource_lst = new commonimglstwidget(true, false);
        area->setWidget(worm_resource_lst);

        left_layout->addWidget(area);
        main_layout->addLayout(left_layout);
    }

    {
        QVBoxLayout* right_layout = new QVBoxLayout;

        sample_id_edit = new QLineEdit;
        right_layout->addWidget(sample_id_edit);

        sample_preview = new commonimgpreviewwidget;
        sample_preview->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        right_layout->addWidget(sample_preview);

        QScrollArea* area = new QScrollArea;
        area->setMaximumHeight(100);
        area->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

        sample_lst = new commonimglstwidget(false, false);
        area->setWidget(sample_lst);

        right_layout->addWidget(area);
        main_layout->addLayout(right_layout);
    }


//    {
//        QHBoxLayout* line_three = new QHBoxLayout;

//        QPushButton* btn_plus = new QPushButton("放大");
//        QPushButton* btn_mins = new QPushButton("缩小");
//        QPushButton* btn_back_to_report = new QPushButton("返回报告");

//        line_three->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
//        line_three->addWidget(btn_plus);
//        line_three->addWidget(btn_mins);
//        line_three->addWidget(btn_back_to_report);

//        content_layout->addLayout(line_three);
//    }

    this->setLayout(main_layout);

    QObject::connect(box, SIGNAL(currentTextChanged(QString)),
                     this, SLOT(currentBoxTextChanged(QString)));
    QObject::connect(sample_id_edit, SIGNAL(editingFinished()),
                     this, SLOT(didFinishEditSampleID_slot()));

    proxymanager::instance()->getWormProxy()->queryWormCat();
}

void imagecomparewidget::showEvent(QShowEvent *) {
    QObject::connect(proxymanager::instance()->getWormProxy(), SIGNAL(queryWormCatSuccess(QJsonObject)),
                     this, SLOT(queryWormCatSuccess(QJsonObject)));
    QObject::connect(proxymanager::instance()->getSampleProxy(), SIGNAL(querySampleWithIDSuccess(QJsonObject)),
                     this, SLOT(querySampleWithIDSuccess(QJsonObject)));
//    QObject::connect(worm_resource_lst, SIGNAL(changeCurrentImageSignal(QPixmap)),
//                     this, SLOT(changeWormPreview(QPixmap)));
//    QObject::connect(sample_lst, SIGNAL(changeCurrentImageSignal(QPixmap)),
//                     this, SLOT(changeSamplePreview(QPixmap)));
    QObject::connect(worm_resource_lst, SIGNAL(changeCurrentImageSignal(QPixmap)),
                     worm_preview, SLOT(setPreviewImage(QPixmap)));
    QObject::connect(sample_lst, SIGNAL(changeCurrentImageSignal(QPixmap)),
                     sample_preview, SLOT(setPreviewImage(QPixmap)));
}

void imagecomparewidget::hideEvent(QHideEvent *) {
    QObject::disconnect(proxymanager::instance()->getWormProxy(), SIGNAL(queryWormCatSuccess(QJsonObject)),
                     this, SLOT(queryWormCatSuccess(QJsonObject)));
    QObject::disconnect(proxymanager::instance()->getSampleProxy(), SIGNAL(querySampleWithIDSuccess(QJsonObject)),
                     this, SLOT(querySampleWithIDSuccess(QJsonObject)));
//    QObject::disconnect(worm_resource_lst, SIGNAL(changeCurrentImageSignal(QPixmap)),
//                     this, SLOT(changeWormPreview(QPixmap)));
//    QObject::disconnect(sample_lst, SIGNAL(changeCurrentImageSignal(QPixmap)),
//                     this, SLOT(changeSamplePreview(QPixmap)));
    QObject::disconnect(worm_resource_lst, SIGNAL(changeCurrentImageSignal(QPixmap)),
                     worm_preview, SLOT(setPreviewImage(QPixmap)));
    QObject::disconnect(sample_lst, SIGNAL(changeCurrentImageSignal(QPixmap)),
                     sample_preview, SLOT(setPreviewImage(QPixmap)));
}

void imagecomparewidget::queryWormCatSuccess(const QJsonObject & cats) {
    current_resource = cats;

    QStringList keys = cats.keys();
    QStringList::iterator key = keys.begin();
    for (; key != keys.end(); ++key) {
        QJsonArray arr = cats[*key].toArray();

        QJsonArray::iterator iter = arr.begin();
        for (; iter != arr.end(); ++iter) {
            QString name = (*iter).toObject()["name"].toString();
            box->addItem(name);
        }
    }
}

void imagecomparewidget::currentBoxTextChanged(const QString & cur) {
    if (this->isHidden())
        return;

    QStringList keys = current_resource.keys();
    QStringList::iterator key = keys.begin();
    for (; key != keys.end(); ++key) {
        QJsonArray arr = current_resource[*key].toArray();

        QJsonArray::iterator iter = arr.begin();
        for (; iter != arr.end(); ++iter) {
            QString name = (*iter).toObject()["name"].toString();
            if (name == cur) {
                QVector<QVariant> var_lst = (*iter).toObject()["img_lst"]
                        .toArray().toVariantList().toVector();
                QVector<QString> name_lst;
                QVector<QVariant>::iterator i = var_lst.begin();
                for (; i != var_lst.end(); ++i) {
                    name_lst.push_back((*i).toString());
                }
                worm_resource_lst->changeShowingImgLst(name_lst);
                break;
            }
        }
    }
}

void imagecomparewidget::didFinishEditSampleID_slot() {
    QString sample_id = sample_id_edit->text();
    if (!sample_id.isEmpty()) {
        proxymanager::instance()->getSampleProxy()->querySampleWithID(sample_id);
    }
}

void imagecomparewidget::querySampleWithIDSuccess(const QJsonObject& sample) {
    sample_lst->changeCurrentSample(sample);
}

//void imagecomparewidget::changeWormPreview(const QPixmap &p) {
//    QSize s = worm_preview->size();
//    QPixmap np = p.scaled(s.width(), s.height());
//    worm_preview->setPixmap(np);
//}

//void imagecomparewidget::changeSamplePreview(const QPixmap &p) {
//    QSize s = sample_preview->size();
//    QPixmap np = p.scaled(s.width(), s.height());
//    sample_preview->setPixmap(np);
//}
