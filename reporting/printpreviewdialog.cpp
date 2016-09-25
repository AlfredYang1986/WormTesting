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
#include <QPrinterInfo>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

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
        if (html == "") {
            this->close();
        }
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

    QPushButton* preview_pdf_btn = new QPushButton("导出PDF");
    QObject::connect(preview_pdf_btn, SIGNAL(released()), this, SLOT(printReportPDF()));
    btn_layout->addWidget(preview_pdf_btn);

    btn_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));

    main_layout->addLayout(btn_layout);

    this->setLayout(main_layout);
}

void printpreviewdialog::printReport() {

    if (((reportingcontainer*)this->parent())->hasAuthToPrint()) {

        QPrinterInfo printerInfo = QPrinterInfo::defaultPrinter();

        QPrinter * pPrinter = 0;
        if ( !printerInfo.isNull() )
            pPrinter = new QPrinter(printerInfo, QPrinter::ScreenResolution);
        else {
            QMessageBox::warning(this, "error",
                                 QStringLiteral("没有有效的打印机"),
                                 QMessageBox::Ok, QMessageBox::Ok);
            return;
        }

        if ( pPrinter && pPrinter->isValid() ) {
           QPrintDialog dlg(pPrinter);
           dlg.setOptions(QAbstractPrintDialog::None);

           document->print(pPrinter);
           ((reportingcontainer*)this->parent())->changeReportingStatusToPrinted();
           delete pPrinter;
       }
    } else {
        QMessageBox::warning(this, "error",
                            QStringLiteral("没有权限执行打印操作"),
                            QMessageBox::Ok, QMessageBox::Ok);

    }
}

void printpreviewdialog::printReportPDF() {

    if (((reportingcontainer*)this->parent())->hasAuthToPrint()) {
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
        ((reportingcontainer*)this->parent())->changeReportingStatusToPrinted();

    } else {
        QMessageBox::warning(this, "error",
                            QStringLiteral("没有权限执行打印操作"),
                            QMessageBox::Ok, QMessageBox::Ok);
    }
}
