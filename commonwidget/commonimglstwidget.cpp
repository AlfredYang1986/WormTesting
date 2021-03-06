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
#include "proxy/sampleproxy.h"
#include "commonwidget/imglstitem.h"

static bool current_runnning = false;

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

commonimglstwidget::commonimglstwidget(bool w, bool v, bool s)
    : isWormSample(w), isVer(v), select_able(s) {
        this->setUpSubviews();
}

commonimglstwidget::~commonimglstwidget() {
    main_layout->deleteLater();
}

QSize commonimglstwidget::sizeHint() const {
    if (isVer)
        return QSize(280, 200);
    else
        return QSize(140, 100);
}

void commonimglstwidget::setUpSubviews() {
    if (isVer) {
        main_layout = new QVBoxLayout;
        main_layout->addSpacerItem(new QSpacerItem(0,0, QSizePolicy::Minimum, QSizePolicy::Expanding));
    } else {
        main_layout = new QHBoxLayout;
        main_layout->addSpacerItem(new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Minimum));
    }

    main_layout->setContentsMargins(8,8,8,8);

//    main_layout->addSpacerItem(new QSpacerItem(0,0, QSizePolicy::Minimum, QSizePolicy::Expanding));
    this->setLayout(main_layout);
}

void commonimglstwidget::changeCurrentSample(const QJsonObject& sample) {
    this->clearLabels();
    img_name_lst.clear();

    sample_id = sample["sample_id"].toString();
    QVector<QVariant> tmp = sample["images"].toArray().toVariantList().toVector();
    QVector<QVariant>::iterator tmp_iter = tmp.begin();
    for (; tmp_iter != tmp.end(); ++tmp_iter) {
        img_name_lst.push_back((*tmp_iter).toString());
    }

    if (isVer)
        this->resize(280, (200 + 10) * img_name_lst.count());
    else
        this->resize((140 + 10) * img_name_lst.count(), 100);

    current_runnning = false;
    this->moveToNextImage();
}

bool commonimglstwidget::prePushImage() {
    return img_name_lst.count() < 5;
}

void commonimglstwidget::pushImageName(const QString& name) {
    img_name_lst.push_back(name);

    if (isVer)
        this->resize(280, (200 + 10) * img_name_lst.count());
    else
        this->resize((140 + 10) * img_name_lst.count(), 140);
    current_download_name = name;
    proxymanager::instance()->getFileProxy()->downloadFile(current_download_name);
    //QObject::connect(proxymanager::instance()->getFileProxy(), SIGNAL(downloadFileSuccess(const QByteArray&, const QString&)),
    //                 this, SLOT(downloadFileSuccess(const QByteArray&, const QString&)));
}

void commonimglstwidget::downloadFileSuccess(const QByteArray& data, const QString& filename) {

    if (!img_name_lst.contains(filename))
        return;

    imglstitem* tmp = new imglstitem(isWormSample, isVer);
    tmp->setObjectName(current_download_name);
    tmp->setContentsMargins(0,0,0,0);

    if (isVer)
        tmp->setFixedSize(QSize(280, 200));
    else
        tmp->setFixedSize(QSize(140, 100));

    QPixmap m;
    m.loadFromData(data);
    //tmp->setPixmap(m);
    tmp->setCurrentPixmap(m);

    QObject::connect(tmp, SIGNAL(imageSelected(const QPixmap*)),
                     this, SLOT(changeCurrentImage(const QPixmap*)));
    QObject::connect(tmp, SIGNAL(delectBtnSelected(QString)),
                     this, SLOT(deleteImageStart(QString)));

    if (select_able) {
        tmp->setSelectAble(select_able);
        QObject::connect(tmp, SIGNAL(canSelected(bool*)), this, SLOT(canSelectedMore(bool*)));
    }

    main_layout->insertWidget(0, tmp);
//    main_layout->addWidget(tmp);
    img_lst.push_back(tmp);

    this->moveToNextImage();
}

void commonimglstwidget::moveToNextImage() {

    if (!this->isVisible() || img_name_lst.isEmpty()) {
        return;
    }

    if (current_download_name.isEmpty()) {

        if (current_runnning)
            return;

        current_runnning = true;
        current_download_name = img_name_lst.first();
        //QObject::connect(proxymanager::instance()->getFileProxy(), SIGNAL(downloadFileSuccess(const QByteArray&, const QString&)),
        //             this, SLOT(downloadFileSuccess(const QByteArray&, const QString&)));

    } else {
        QVector<QString>::iterator iter = std::find_if(img_name_lst.begin(), img_name_lst.end(),
                                                       pred_find_current_download_filename(current_download_name));
        if (iter == img_name_lst.end() || (++iter) == img_name_lst.end()) {
            current_runnning = false;
            current_download_name = "";
            //QObject::disconnect(proxymanager::instance()->getFileProxy(), SIGNAL(downloadFileSuccess(const QByteArray&, const QString&)),
            //         this, SLOT(downloadFileSuccess(const QByteArray&, const QString&)));
            if (!img_lst.isEmpty()) {
//                const QPixmap* m = img_lst.first()->pixmap();
                QPixmap m = img_lst.first()->getCurrentPixmap();
                emit changeCurrentImageSignal(m);
            }

        } else {
            current_download_name = *iter;
        }
    }

    if (!current_download_name.isEmpty())
        proxymanager::instance()->getFileProxy()->downloadFile(current_download_name);
}

void commonimglstwidget::showEvent(QShowEvent *) {
    this->clearLabels();
    QObject::connect(proxymanager::instance()->getFileProxy(), SIGNAL(downloadFileSuccess(const QByteArray&, const QString&)),
                     this, SLOT(downloadFileSuccess(const QByteArray&, const QString&)));
    QObject::connect(proxymanager::instance()->getFileProxy(), SIGNAL(downloadFileFailed()),
                     this, SLOT(deleteImageFailed()));
    QObject::connect(proxymanager::instance()->getSampleProxy(), SIGNAL(popSampleImageSuccess(QString,QString)),
                     this, SLOT(deleteImageSuccess(QString,QString)));
}

void commonimglstwidget::hideEvent(QHideEvent *) {
    QObject::disconnect(proxymanager::instance()->getFileProxy(), SIGNAL(downloadFileSuccess(const QByteArray&, const QString&)),
                     this, SLOT(downloadFileSuccess(const QByteArray&, const QString&)));
    QObject::disconnect(proxymanager::instance()->getSampleProxy(), SIGNAL(popSampleImageSuccess(QString,QString)),
                     this, SLOT(deleteImageSuccess(QString,QString)));
    QObject::disconnect(proxymanager::instance()->getFileProxy(), SIGNAL(downloadFileFailed()),
                     this, SLOT(deleteImageFailed()));
    this->clearLabels();
}

void commonimglstwidget::deleteImageStart(const QString & name) {
    QVector<QString>::iterator iter = std::find_if(img_name_lst.begin(), img_name_lst.end(),
                                                   pred_find_current_download_filename(name));
    if (iter != img_name_lst.end()) {
        proxymanager::instance()->getSampleProxy()->popSampleImage(sample_id, name);
    }
}

void commonimglstwidget::deleteImageSuccess(const QString & sample_id_arg, const QString & image) {

    if (sample_id_arg != sample_id)
        return;

    this->clearLabels();

    img_name_lst.erase(std::remove_if(img_name_lst.begin(), img_name_lst.end(),
                                      pred_find_current_download_filename(image)), img_name_lst.end());

    current_download_name = "";
    this->moveToNextImage();
}

void commonimglstwidget::clearLabels() {
    QVector<imglstitem*>::iterator iter_label = img_lst.begin();
    for(; iter_label != img_lst.end(); ++iter_label) {
        main_layout->removeWidget(*iter_label);
        imglstitem* b = (imglstitem*)(*iter_label);
        b->deleteLater();
        QObject::disconnect(b, SIGNAL(imageSelected(const QPixmap*)),
                     this, SLOT(changeCurrentImage(const QPixmap*)));
        QObject::disconnect(b, SIGNAL(delectBtnSelected(QString)),
                     this, SLOT(deleteImageStart(QString)));

    }
    img_lst.clear();
}

void commonimglstwidget::changeShowingImgLst(const QVector<QString> &name_lst) {
    this->clearLabels();
    img_name_lst = name_lst;

    if (isVer)
        this->resize(280, (200 + 10) * img_name_lst.count());
    else
        this->resize((140 + 10) * img_name_lst.count(), 100);

    this->moveToNextImage();
}

bool commonimglstwidget::showOptBtns() const {
    return !isWormSample;
}


void commonimglstwidget::changeCurrentImage(const QPixmap* p) {
    emit changeCurrentImageSignal(*p);
}

QVector<QImage> commonimglstwidget::getCurrentImages() const {
    QVector<QImage> result;

    QVector<imglstitem*>::const_iterator iter = img_lst.begin();
    for (; iter != img_lst.end(); ++iter) {
        imglstitem* tmp = (*iter);
        result.push_back(tmp->getCurrentPixmap().toImage());
    }

    return result;
}

QVector<QImage> commonimglstwidget::getCurrentSelectedImages() const {
    QVector<QImage> result;

    QVector<imglstitem*>::const_iterator iter = img_lst.begin();
    for (; iter != img_lst.end(); ++iter) {
        imglstitem* tmp = (*iter);
        if (tmp->isSelected() && tmp->isSelectAble())
            result.push_back(tmp->getCurrentPixmap().toImage());
    }

    return result;
}

int commonimglstwidget::getCurrentSelectedImageCount() const {
    int result = 0;

    QVector<imglstitem*>::const_iterator iter = img_lst.begin();
    for (; iter != img_lst.end(); ++iter) {
        imglstitem* tmp = (*iter);
        if (tmp->isSelected() && tmp->isSelectAble())
            ++result;
    }

    return result;
}

void commonimglstwidget::canSelectedMore(bool * result) {
    int count = this->getCurrentSelectedImageCount();
    if (count < 2)
        *result = true;
    else
        *result = false;
}

void commonimglstwidget::deleteImageFailed() {
    qDebug() << "failed" << endl;
    this->moveToNextImage();
}
