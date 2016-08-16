#include "resourceproxy.h"
#include <QApplication>
#include <QDir>
#include <QFileDialog>
#include <QDebug>
#include "proxy/proxymanager.h"
#include "proxy/wormproxy.h"
#include "proxy/fileoptproxy.h"
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonArray>

resourceproxy* resourceproxy::_instance = NULL;

resourceproxy::resourceproxy() {
    http_connect = new QNetworkAccessManager(this);
    QObject::connect(http_connect,SIGNAL(finished(QNetworkReply*)), this, SLOT(replayFinished(QNetworkReply*)));

    QObject::connect(proxymanager::instance()->getWormProxy(), SIGNAL(pushWormImageSuccess(QString)),
                     this, SLOT(pushSourceImageSuccess(QString)));

    QObject::connect(proxymanager::instance()->getWormProxy(), SIGNAL(pushWormCatSuccess()),
                     this, SLOT(pushWormCatSuccess()));
    QObject::connect(proxymanager::instance()->getWormProxy(), SIGNAL(pushWormSuccess(QString,QString)),
                     this, SLOT(pushWormSuccess(QString,QString)));

    dir_name = QApplication::applicationDirPath() + "/sample_resource";
    txt_name = QApplication::applicationDirPath() + "/sample_txt";

    QObject::connect(proxymanager::instance()->getFileProxy(), SIGNAL(uploadSampleImageSuccess(QString,QString)),
                     this, SLOT(uploadSampleImageSuccess(QString,QString)));

}

resourceproxy::~resourceproxy() {

}

resourceproxy* resourceproxy::instance() {
    if (_instance == NULL)
        _instance = new resourceproxy;

    return _instance;
}

int resourceproxy::getFetchCount() {
    index = 0;
    count = 0;

    QDir dir(dir_name);
    QFileInfoList lst = dir.entryInfoList();
    QFileInfoList::iterator iter = lst.begin();
    for (; iter != lst.end(); ++iter) {
        /**
         * worm cat name
         */
        QString tmp = (*iter).fileName();
        if (tmp != "." && tmp != "..") {
            qDebug() << tmp << endl;

            /**
             * worm name
             */
            QDir worm_name_dir(dir_name + "/" + tmp);
            QFileInfoList lst_wn = worm_name_dir.entryInfoList();
            QFileInfoList::iterator wn = lst_wn.begin();
            for (; wn != lst_wn.end(); ++ wn) {
                QString worm_name = (*wn).fileName();
                if (worm_name != "." && worm_name != "..") {
                    qDebug() << worm_name << endl;

                    QDir worm_image_dir(dir_name + "/" + tmp + "/" + worm_name);
                    qDebug() << worm_image_dir.exists() << endl;
                    QFileInfoList lst_img = worm_image_dir.entryInfoList();
                    QFileInfoList::iterator img_iter = lst_img.begin();
                    for (; img_iter != lst_img.end(); ++img_iter) {
                        QString worm_img_name = (*img_iter).fileName();
                        if (worm_img_name != "." && worm_img_name != "..") {
                            qDebug() << worm_img_name << endl;
                            ++count;
                        }
                    }
                }
            }
        }
    }
    return count;
}

void resourceproxy::fetchResourcesAccImg(const QString& cat, const QString& name) {
    QDir worm_image_dir(dir_name + "/" + cat + "/" + name);
    qDebug() << worm_image_dir.exists() << endl;
    QFileInfoList lst_img = worm_image_dir.entryInfoList();
    QFileInfoList::iterator img_iter = lst_img.begin();
    for (; img_iter != lst_img.end(); ++img_iter) {
        QString worm_img_name = (*img_iter).fileName();
        if (worm_img_name != "." && worm_img_name != "..") {
            qDebug() << worm_img_name << endl;
            QString file = dir_name + "/" + cat + "/" + name + "/" + worm_img_name;
            QImage image(file);
            proxymanager::instance()->getFileProxy()->uploadSampleImage(name, image);

            QFile description(txt_name + "/" + name + ".txt");
            if (description.exists()) {
                qDebug() << description.fileName() << endl;
                if(description.open(QIODevice::ReadOnly | QIODevice::Text)) {
                    QString str(description.readAll());
                    proxymanager::instance()->getWormProxy()->changeWromdescription(name, str);
                    description.close();
                }
            }

            QTime dieTime = QTime::currentTime().addMSecs(200);
            while( QTime::currentTime() < dieTime )
                QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }
    }
}

void resourceproxy::fetchResources() {
//    dir_name = QFileDialog::getExistingDirectory(NULL);
//    if (dir_name.trimmed() == "") {
//        return;
//    }
//    qDebug() << dir_name << endl;

    this->getFetchCount();

    QDir dir(dir_name);
    QFileInfoList lst = dir.entryInfoList();
    QFileInfoList::iterator iter = lst.begin();
    for (; iter != lst.end(); ++iter) {
        /**
         * worm cat name
         */
        QString tmp = (*iter).fileName();
        if (tmp != "." && tmp != "..") {
            qDebug() << tmp << endl;
            proxymanager::instance()->getWormProxy()->pushWormCat(tmp);

            /**
             * worm name
             */
            QDir worm_name_dir(dir_name + "/" + tmp);
            QFileInfoList lst_wn = worm_name_dir.entryInfoList();
            QFileInfoList::iterator wn = lst_wn.begin();
            for (; wn != lst_wn.end(); ++ wn) {
                QString worm_name = (*wn).fileName();
                if (worm_name != "." && worm_name != "..") {
                    qDebug() << worm_name << endl;
                    proxymanager::instance()->getWormProxy()->pushWorm(worm_name, tmp);
                }
            }
        }
    }
}

void resourceproxy::startResourceImport() {
    QUrl url = QString("http://localhost:9000/worm/source/import");

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
//    json.insert("patient", pt);

    QJsonDocument document;
    document.setObject(json);
    QByteArray arr = document.toJson(QJsonDocument::Compact);

    QNetworkReply* http_replay = http_connect->post(request , arr);

    QObject::connect(http_replay, SIGNAL(error(QNetworkReply::NetworkError)),
                     this, SLOT(networkError(QNetworkReply::NetworkError)));
}

void resourceproxy::endResourceImport() {
//    QUrl url = QString("http://localhost:9000/config/patient/pop");
//
//    QNetworkRequest request(url);
//    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
//
//    QJsonObject json;
//    json.insert("patient", pt);
//
//    QJsonDocument document;
//    document.setObject(json);
//    QByteArray arr = document.toJson(QJsonDocument::Compact);
//
//    QNetworkReply* http_replay = http_connect->post(request , arr);
//
//    QObject::connect(http_replay, SIGNAL(error(QNetworkReply::NetworkError)),
//                     this, SLOT(networkError(QNetworkReply::NetworkError)));
}

void resourceproxy::replayFinished(QNetworkReply * result) {
    if (result->error() == 0) {
        QByteArray data = result->readAll();
        qDebug() << QString(data) << endl;

        QJsonDocument json = QJsonDocument::fromJson(data);
        if(json.isObject()) {
            QJsonObject obj = json.object();
            if (obj.contains("method")) {
                QString method_name = obj["method"].toString();
                if (method_name == "wormSourceImport") {
                    this->fetchResources();
                }
            }
         }
    } else {
        QMessageBox::warning(NULL, "Error",
                             QStringLiteral("访问数据库操作失败"),
                             QMessageBox::Ok, QMessageBox::Ok);
    }
}

void resourceproxy::networkError(QNetworkReply::NetworkError) {
    QMessageBox::warning(NULL, "Error",
                         QStringLiteral("访问数据库操作失败"),
                         QMessageBox::Ok, QMessageBox::Ok);
    QObject::sender()->deleteLater();
}

void resourceproxy::pushSourceImageSuccess(const QString &) {
    if (++index >= count) {
        QObject::disconnect(proxymanager::instance()->getFileProxy(), SIGNAL(uploadSampleImageSuccess(QString,QString)),
                     this, SLOT(uploadSampleImageSuccess(QString,QString)));
    }

    emit resrouceImportProgress(index * 100.0 / count);
}

void resourceproxy::pushWormCatSuccess() {
//    this->fetchResourcesAcc();
}

void resourceproxy::pushWormSuccess(const QString& cat, const QString& name) {
    this->fetchResourcesAccImg(cat, name);
}

void resourceproxy::uploadSampleImageSuccess(const QString & worm_name, const QString & img_name) {
    proxymanager::instance()->getWormProxy()->pushWormImage(worm_name, img_name);
}
