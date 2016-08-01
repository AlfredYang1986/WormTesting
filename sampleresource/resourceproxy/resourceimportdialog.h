#ifndef RESOURCEIMPORTDIALOG_H
#define RESOURCEIMPORTDIALOG_H

#include <QDialog>

class QProgressBar;
class QVBoxLayout;

class resourceimportdialog : public QDialog {
    Q_OBJECT

protected Q_SLOTS:
    void startBtnPushed();
    void cancelBtnPushed();

    void resrouceImportProgress(double);

public:
    resourceimportdialog();
    ~resourceimportdialog();

protected:
    void setUpSubviews();
    virtual QSize sizeHint() const;

private:
    QVBoxLayout* main_layout;
    QProgressBar* bar;
};

#endif // RESOURCEIMPORTDIALOG_H
