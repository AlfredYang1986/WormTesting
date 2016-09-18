#ifndef IMGLSTITEM_H
#define IMGLSTITEM_H

#include <QLabel>
class QPushButton;
class QPixmap;
class QLabel;

class imglstitem : public QLabel {
    Q_OBJECT

Q_SIGNALS:
    void delectBtnSelected(const QString&);
//    void saveAsBtnSelected(const QString&);
    void imageSelected(const QPixmap*);
    void canSelected(bool* result);

protected Q_SLOTS:
    void saveAsBtnSelected();
    void delectBtnSelected_slot();

protected:
    virtual void mousePressEvent(QMouseEvent *);

private:
    QPushButton* delect_btn;
    QPushButton* save_as_btn;
    QLabel* selected_label;

    QPixmap current_pixmap;

    //QLabel* pic_preview;

    const bool isWormImgItem;
    const bool isVer;

    bool selected;
    bool select_able;
public:
    imglstitem(bool w = false, bool v = true);
    ~imglstitem();

    virtual QSize sizeHint() const;

    void setUpSubviews();

    bool isShowOptBtns() const;

    void setCurrentPixmap(const QPixmap&);
    QPixmap getCurrentPixmap() const;

    bool isSelected() const;
    void setSelected(bool b);

    bool isSelectAble() const;
    void setSelectAble(bool b);

    virtual void mouseDoubleClickEvent(QMouseEvent * event);
};

#endif // IMGLSTITEM_H
