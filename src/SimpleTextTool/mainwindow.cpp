#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../../lib/text2flash.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedSize(720, 450);

    ui->txtTarget->setReadOnly(true);
    ui->txtEncodedTarget->setReadOnly(true);

    textTool = new UTFTools::Text2Flash();
}

MainWindow::~MainWindow()
{
    delete textTool;

    delete ui;
}

void MainWindow::on_btnGenerate_clicked()
{
    ui->txtTarget->setPlainText(QString::fromStdWString(
                                    textTool->GetFlashStr(ui->txtSource->toPlainText().toStdWString(),
                                                          false)));

    ui->txtEncodedTarget->setPlainText(QString::fromStdWString(
                                           textTool->GetFlashStr(ui->txtSource->toPlainText().toStdWString(),
                                                                 true)));
}
