#ifndef SAMPLERESOURCECONTAINER_H
#define SAMPLERESOURCECONTAINER_H

//#include <QScrollArea>
#include <QFrame>

class QHBoxLayout;
class QLabel;
class commonimglstwidget;

class sampleresourcecontainer : public QFrame {
    Q_OBJECT

Q_SIGNALS:

public Q_SLOTS:
    void currentWorm(const QString&, const QString&);
    void queryWormDetailSuccess(const QJsonObject&);

private:
    QHBoxLayout* main_layout;
    QLabel* html;
    commonimglstwidget* img_lst;

public:
    sampleresourcecontainer();
    ~sampleresourcecontainer();

    void setUpSubviews();

protected:
    virtual QSize sizeHint() const;
};

#endif // SAMPLERESOURCECONTAINER_H
