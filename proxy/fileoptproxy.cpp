#include "fileoptproxy.h"

fileoptproxy::fileoptproxy() : isDownLoading(false) {
    http_connect = new QNetworkAccessManager(this);
    QObject::connect(http_connect,SIGNAL(finished(QNetworkReply*)), this, SLOT(replayFinished(QNetworkReply*)));
}

fileoptproxy::~fileoptproxy() {
    http_connect->deleteLater();
}

void fileoptproxy::uploadSampleImage(const QString &sample_id, const QImage &image) {
    QByteArray bytes;
    QBuffer buffer(&bytes);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG");

    //分界线的标识符
    QString TWITTERFON_FORM_BOUNDARY = "AaB03x";
    //根据url初始化request
    QUrl url = QString("http://localhost:9000/file/upload");
    QNetworkRequest request(url);

    //分界线 --AaB03x
    //结束符 AaB03x--
    //声明结束符：--AaB03x--
    QString end = QString("\r\n--%1--").arg(TWITTERFON_FORM_BOUNDARY);
    //要上传的图片
    //得到图片的data
    //http body的字符串
    QString data_header = QString("--%1\r\nContent-Disposition: form-data; name=\"upload\"; filename=\"%2\"\r\nContent-Type: image/png\r\n\r\n")
                        .arg(TWITTERFON_FORM_BOUNDARY).arg(sample_id);

    QByteArray data = data_header.toUtf8();
    data.append(bytes);
    data.append(end.toUtf8());

//    qDebug() << data << endl;

    //设置HTTPHeader中Content-Type的值
    //设置HTTPHeader
    request.setHeader(QNetworkRequest::ContentTypeHeader, QString("multipart/form-data; boundary=%1").arg(TWITTERFON_FORM_BOUNDARY));
    //设置Content-Length
    request.setHeader(QNetworkRequest::ContentLengthHeader, data.length());
    //设置http body
    //http method
    QNetworkReply* http_replay = http_connect->post(request, data);

    QObject::connect(http_replay, SIGNAL(error(QNetworkReply::NetworkError)),
                     this, SLOT(networkError(QNetworkReply::NetworkError)));
}

void fileoptproxy::downloadFile(const QString &name) {

    qDebug() << name << endl;
    download_lst.push_back(name);
    if (isDownLoading) return;
    else this->downloadFileImpl(download_lst.first());
}

void fileoptproxy::downloadFileImpl(const QString &name) {
    isDownLoading = true;
    QUrl url = QString("http://localhost:9000/images/") + name;

    QNetworkRequest request(url);
    QNetworkReply* http_replay = http_connect->get(request);

    QObject::connect(http_replay, SIGNAL(error(QNetworkReply::NetworkError)),
                     this, SLOT(networkError(QNetworkReply::NetworkError)));
}

void fileoptproxy::replayFinished(QNetworkReply* result) {
    if (result->error() == 0) {
        QByteArray data = result->readAll();

        QJsonDocument json = QJsonDocument::fromJson(data);
        if(json.isObject()) {
            QJsonObject obj = json.object();
            if (obj.contains("method")) {
                QString method_name = obj["method"].toString();
                if (method_name == "uploadFile") {
                    QJsonObject head = obj["result"].toArray().first().toObject();
                    QString sample_id = head["sample_id"].toString();
                    QString image_name = head["image_name"].toString();
                    emit uploadSampleImageSuccess(sample_id, image_name);
                }
             }
         } else {
            QString succ = download_lst.first();
            download_lst.pop_front();
            if (!download_lst.isEmpty())
                this->downloadFileImpl(download_lst.first());
            else
                isDownLoading = false;

            if (!data.isEmpty())
                emit downloadFileSuccess(data, succ);
        }
    }
}

void fileoptproxy::networkError(QNetworkReply::NetworkError error) {
    qDebug() << error;
    if (isDownLoading) {
// 		QString succ = download_lst.first();
        download_lst.pop_front();
        if (!download_lst.isEmpty())
            this->downloadFileImpl(download_lst.first());
        else
            isDownLoading = false;

        emit downloadFileFailed();
    }
}
