#ifndef DELETESAMPLERESOURCEDIALOG_H
#define DELETESAMPLERESOURCEDIALOG_H

#include <QDialog>
class QVBoxLayout;
class QComboBox;

class deletesampleresourcedialog : public QDialog {
    Q_OBJECT

Q_SIGNALS:

protected Q_SLOTS:
    void saveBtnClicked();
    void cancelBtnClicked();

    void querySampleResourceTypeSuccess(const QJsonArray&);

private:
    QVBoxLayout* main_layout;
    QComboBox* resource_box;

public:
    deletesampleresourcedialog();
    ~deletesampleresourcedialog();

    virtual QSize sizeHint() const;
    void setUpSubviews();
};

#endif // DELETESAMPLERESOURCEDIALOG_H
