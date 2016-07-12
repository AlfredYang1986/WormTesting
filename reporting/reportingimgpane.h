#ifndef REPORTINGIMGPANE_H
#define REPORTINGIMGPANE_H

#include <QFrame>

class QVBoxLayout;
class QJsonObject;
class QLabel;

class reportingimgpane : public QFrame {
    Q_OBJECT

Q_SIGNALS:
    void saveReportTestResult();

protected Q_SLOTS:
    void downloadFileSuccess(const QByteArray&, const QString&);

    void saveBtnClicked();
    void previewBtnClicked();
    void printBtnClicked();
public:
    reportingimgpane();
    ~reportingimgpane();

    virtual QSize sizeHint() const;

    void fillImages(const QJsonObject& sample);
protected:
    void setUpSubviews();

    virtual void showEvent(QShowEvent*);
    virtual void hideEvent(QHideEvent*);

private:
    QVBoxLayout* main_layout;

    QLabel* large_img;
    QString current_img_name;
};

#endif // REPORTINGIMGPANE_H
