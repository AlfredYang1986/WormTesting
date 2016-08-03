#include "resourceimportdialog.h"
#include <QProgressBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include "resourceproxy.h"
#include <QMessageBox>
#include <QLabel>

resourceimportdialog::resourceimportdialog() {
    this->setUpSubviews();
}

resourceimportdialog::~resourceimportdialog() {
    main_layout->deleteLater();
}

void resourceimportdialog::setUpSubviews() {
    main_layout = new QVBoxLayout;

    QLabel* title = new QLabel(QStringLiteral("导入样本库"));
    title->setAlignment(Qt::AlignCenter);
    title->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    main_layout->addWidget(title);

    main_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));

    bar = new QProgressBar;
    bar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    bar->setRange(0, 100);
    main_layout->addWidget(bar);

    main_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));

    QHBoxLayout* btn_layout = new QHBoxLayout;

    start_btn = new QPushButton(QStringLiteral("开始"));
    QObject::connect(start_btn, SIGNAL(released()),
                     this, SLOT(startBtnPushed()));
    btn_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));
    btn_layout->addWidget(start_btn);

    QPushButton* cancel_btn = new QPushButton(QStringLiteral("取消"));
    QObject::connect(cancel_btn, SIGNAL(released()),
                     this, SLOT(cancelBtnPushed()));
    btn_layout->addWidget(cancel_btn);
    btn_layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum));

    main_layout->addLayout(btn_layout);

    this->setLayout(main_layout);

    QObject::connect(resourceproxy::instance(), SIGNAL(resrouceImportProgress(double)),
                     this, SLOT(resrouceImportProgress(double)));
}

QSize resourceimportdialog::sizeHint() const {
    return QSize(500, 200);
}

void resourceimportdialog::startBtnPushed() {
    if (QMessageBox::Yes == QMessageBox::warning(this, "Warning",
                                                 QStringLiteral("导入数据会覆盖以前数据，确定吗?"),
                                                 QMessageBox::Yes | QMessageBox::No,
                                                 QMessageBox::Yes)) {
        start_btn->setEnabled(false);
        resourceproxy::instance()->startResourceImport();
    }
}

void resourceimportdialog::cancelBtnPushed() {
    this->close();
}

void resourceimportdialog::resrouceImportProgress(double pro) {
    qDebug() << pro << endl;
    bar->setValue(pro);

    if (pro == 100) {
        QMessageBox::information(this, "Success",
                                 QStringLiteral("成功导入所有"),
                                 QMessageBox::Ok, QMessageBox::Ok);

        start_btn->setEnabled(true);
    }
}
