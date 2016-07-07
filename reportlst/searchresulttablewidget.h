#ifndef SEARCHRESULTTABLEWIDGET_H
#define SEARCHRESULTTABLEWIDGET_H

#include <QTableWidget>
#include <QJsonArray>

class searchresulttablewidget : public QTableWidget {
    Q_OBJECT

Q_SIGNALS:
    void startReport(const QJsonObject&);

protected Q_SLOTS:
    void changeSearchResult(const QJsonArray&);
    void reportSearchResult(QModelIndex);

public:
    searchresulttablewidget();
    ~searchresulttablewidget();

protected:
    virtual QSize sizeHint() const;
    void setUpSubviews();

private:
    void clearSearchResult();

    QJsonArray current_result;
};

#endif // SEARCHRESULTTABLEWIDGET_H
