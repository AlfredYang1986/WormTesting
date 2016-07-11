#ifndef IMGLSTITEM_H
#define IMGLSTITEM_H

#include <QFrame>
class QPushButton;
class QPixmap;
class QLabel;

class imglstitem : public QFrame {
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

    QLabel* pic_preview;

    const bool isWormImgItem;
    const bool isVer;
public:
    imglstitem(bool w = false, bool v = true);
    ~imglstitem();

    virtual QSize sizeHint() const;

    void setUpSubviews();

    bool isShowOptBtns() const;

    void setPixmap(const QPixmap&);
};

#endif // IMGLSTITEM_H
