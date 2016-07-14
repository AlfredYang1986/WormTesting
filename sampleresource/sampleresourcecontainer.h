#ifndef SAMPLERESOURCECONTAINER_H
#define SAMPLERESOURCECONTAINER_H

//#include <QScrollArea>
#include <QFrame>

class QHBoxLayout;
class QLabel;
class commonimglstwidget;
class commonimgpreviewwidget;

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
    commonimgpreviewwidget* img_preview;

public:
    sampleresourcecontainer();
    ~sampleresourcecontainer();

    void setUpSubviews();

protected:
    virtual QSize sizeHint() const;
    virtual void showEvent(QShowEvent *);
    virtual void hideEvent(QHideEvent *);
};

#endif // SAMPLERESOURCECONTAINER_H
