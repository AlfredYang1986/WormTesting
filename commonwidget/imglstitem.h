#ifndef IMGLSTITEM_H
#define IMGLSTITEM_H

#include <QLabel>
class QPushButton;

class imglstitem : public QLabel {
    Q_OBJECT

Q_SIGNALS:
    void delectBtnSelected(const QString&);
//    void saveAsBtnSelected(const QString&);

protected Q_SLOTS:
    void saveAsBtnSelected();
    void delectBtnSelected_slot();

private:
    QPushButton* delect_btn;
    QPushButton* save_as_btn;

public:
    imglstitem();
    ~imglstitem();

    virtual QSize sizeHint() const;

    void setUpSubviews();
};

#endif // IMGLSTITEM_H
