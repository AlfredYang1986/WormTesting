#ifndef PRINTPREVIEWDIALOG_H
#define PRINTPREVIEWDIALOG_H

#include <QDialog>
#include <QTextDocument>
class QVBoxLayout;

class printpreviewdialog : public QDialog {
    Q_OBJECT

Q_SIGNALS:

protected Q_SLOTS:
    void printReport();
    void printReportPDF();

private:
    QVBoxLayout* main_layout;
    QTextDocument* document;

public:
    printpreviewdialog(QWidget* parent);
    ~printpreviewdialog();

protected:
    virtual QSize sizeHint() const;
    void setUpSubviews();
};

#endif // PRINTPREVIEWDIALOG_H
