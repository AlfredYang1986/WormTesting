#include "printpreviewdialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QTextBrowser>
#include "reportingcontainer.h"
#include <QPainter>
#include <QPrinter>
#include <QPrintDialog>
#include <QFileDialog>
#include <QMessageBox>

printpreviewdialog::printpreviewdialog(QWidget* p)
    : QDialog(p) {
    this->setUpSubviews();
}

printpreviewdialog::~printpreviewdialog() {

}

QSize printpreviewdialog::sizeHint() const {
    return QSize(800, 1000);
}

void printpreviewdialog::setUpSubviews() {
    main_layout = new QVBoxLayout;

//    QScrollArea* area = new QScrollArea;
//    area->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    {
        QTextBrowser* browser = new QTextBrowser;

        document = new QTextDocument;
        QString html = ((reportingcontainer*)this->parent())->htmlContent(*document);
        document->setHtml(html);

        browser->setDocument(document);
        browser->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//        area->setWidget(browser);
        main_layout->addWidget(browser);
    }

    QHBoxLayout* btn_layout = new QHBoxLayout;
    btn_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));

    QPushButton* preview_btn = new QPushButton("打印");
    QObject::connect(preview_btn, SIGNAL(released()), this, SLOT(printReport()));
    btn_layout->addWidget(preview_btn);

    QPushButton* preview_pdf_btn = new QPushButton("导出PTF");
    QObject::connect(preview_pdf_btn, SIGNAL(released()), this, SLOT(printReportPDF()));
    btn_layout->addWidget(preview_pdf_btn);

    btn_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));

    main_layout->addLayout(btn_layout);

    this->setLayout(main_layout);
}

void printpreviewdialog::printReport() {
    QPrinter printer;
    QPrintDialog printDialog(&printer, (QWidget*)this->parent());
    if (printDialog.exec()) {
//        QTextDocument textDocument;
//        QString html = ((reportingcontainer*)this->parent())->htmlContent(document);
//        textDocument.setHtml(html);
//        textDocument.print(&printer);
        document->print(&printer);
        ((reportingcontainer*)this->parent())->changeReportingStatusInService();
    }
}

void printpreviewdialog::printReportPDF() {
    QString filename = QFileDialog::getSaveFileName((QWidget*)this->parent(), "Save File", "", "Adobe PDF Files (*.pdf)");
    if (filename.trimmed() == "") {
        return;
    }

    QPrinter  printer;
    printer.setPageSize(QPrinter::A4);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filename);

//    QTextDocument textDocument;
//    QString html = ((reportingcontainer*)this->parent())->htmlContent(document);
//    textDocument.setHtml(html);
//    textDocument.print(&printer);
    document->print(&printer);
    ((reportingcontainer*)this->parent())->changeReportingStatusInService();
}
