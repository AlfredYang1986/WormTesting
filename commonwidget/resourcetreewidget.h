#ifndef RESOURCETREEWIDGET_H
#define RESOURCETREEWIDGET_H

#include <QFrame>
#include <QTreeWidget>
#include <QJsonObject>

class resourcetreewidget : public QTreeWidget {
    Q_OBJECT

Q_SIGNALS:
    void currentWormSignal(const QString& worm_name, const QString& worm_cat_name);

public Q_SLOTS:
    void queryWormCatSuccess(const QJsonObject&);
//    void currentWormSlot(const QModelIndex&);
    void currentWormSlot(QTreeWidgetItem*, int);

public:
    resourcetreewidget();
    ~resourcetreewidget();

    virtual QSize sizeHint() const;
protected:
    void setUpSubviews();

private:
    QJsonObject categories;
};

#endif // RESOURCETREEWIDGET_H
