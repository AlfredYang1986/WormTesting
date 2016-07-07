#ifndef IMGLSTITEM_H
#define IMGLSTITEM_H

#include <QLabel>
class QPushButton;
class QPixmap;

class imglstitem : public QLabel {
    Q_OBJECT

Q_SIGNALS:
    void delectBtnSelected(const QString&);
//    void saveAsBtnSelected(const QString&);
    void imageSelected(const QPixmap*);

protected Q_SLOTS:
    void saveAsBtnSelected();
    void delectBtnSelected_slot();

protected:
    virtual void mousePressEvent(QMouseEvent *);

private:
    QPushButton* delect_btn;
    QPushButton* save_as_btn;

    const bool isWormImgItem;
public:
    imglstitem(bool w = false);
    ~imglstitem();

    virtual QSize sizeHint() const;

    void setUpSubviews();

    bool isShowOptBtns() const;
};

#endif // IMGLSTITEM_H
