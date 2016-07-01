#include "commonimglstwidget.h"
#include <QVBoxLayout>
#include <QVector>
#include <QJsonObject>
#include <QJsonArray>
#include <QLabel>
#include <QVariant>
#include <QSpacerItem>
#include "proxy/proxymanager.h"
#include "proxy/fileoptproxy.h"

class pred_find_current_download_filename {
public:
    pred_find_current_download_filename(const QString& cur)
        : _cur(cur) {}

    bool operator()(const QString& lhs) {
        return lhs == _cur;
    }

private:
    QString _cur;
};

commonimglstwidget::commonimglstwidget() {
    this->setUpSubviews();
}

commonimglstwidget::~commonimglstwidget() {
    main_layout->deleteLater();
}

QSize commonimglstwidget::sizeHint() const {
    return QSize(300, 300);
}

void commonimglstwidget::setUpSubviews() {
    main_layout = new QVBoxLayout;
    main_layout->setContentsMargins(0,0,0,0);

    main_layout->addSpacerItem(new QSpacerItem(0,0, QSizePolicy::Minimum, QSizePolicy::Expanding));
    this->setLayout(main_layout);

    QObject::connect(proxymanager::instance()->getFileProxy(), SIGNAL(downloadFileSuccess(const QByteArray&)),
                     this, SLOT(downloadFileSuccess(const QByteArray&)));
}



void commonimglstwidget::changeCurrentSample(const QJsonObject& sample) {
    QVector<QLabel*>::iterator iter_label = img_lst.begin();
    for(; iter_label != img_lst.end(); ++iter_label) {
        main_layout->removeWidget(*iter_label);
    }
    img_lst.clear();
    img_name_lst.clear();

    sample_id = sample["sample_id"].toString();
    QVector<QVariant> tmp = sample["images"].toArray().toVariantList().toVector();
    QVector<QVariant>::iterator tmp_iter = tmp.begin();
    for (; tmp_iter != tmp.end(); ++tmp_iter) {
        img_name_lst.push_back((*tmp_iter).toString());
    }

    this->moveToNextImage();
}

bool commonimglstwidget::prePushImage() {
    return img_name_lst.count() < 5;
}

void commonimglstwidget::pushImageName(const QString& name) {
    img_name_lst.push_back(name);

    current_download_name = name;
    proxymanager::instance()->getFileProxy()->downloadFile(current_download_name);
}

void commonimglstwidget::downloadFileSuccess(const QByteArray& data) {
    QLabel* tmp = new QLabel;
    tmp->setContentsMargins(0,0,0,0);
    tmp->setMaximumSize(QSize(300, 200));
    tmp->setMinimumSize(QSize(300, 200));
    QPixmap m;
    m.loadFromData(data);
    m = m.scaledToWidth(250);
    tmp->setPixmap(m);

    main_layout->insertWidget(0, tmp);
    img_lst.push_back(tmp);

    this->moveToNextImage();
}

void commonimglstwidget::moveToNextImage() {

    if (!this->isVisible() || img_name_lst.isEmpty()) {
        return;
    }

    if (current_download_name.isEmpty()) {
        current_download_name = img_name_lst.first();
    } else {
        QVector<QString>::iterator iter = std::find_if(img_name_lst.begin(), img_name_lst.end(),
                                                       pred_find_current_download_filename(current_download_name));
        if (iter == img_name_lst.end() || (++iter) == img_name_lst.end()) {
            current_download_name = "";
        } else {
            current_download_name = *iter;
        }
    }

    if (!current_download_name.isEmpty())
        proxymanager::instance()->getFileProxy()->downloadFile(current_download_name);
}
