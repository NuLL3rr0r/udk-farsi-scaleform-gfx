#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QtSql>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../../lib/sqlite3.h"
#include "../../lib/text2flash.hpp"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedSize(720, 450);

    textTool = new UTFTools::Text2Flash();

    dbFile = "game-msg.db";

    /* Cleaning-up db */
    Vacuum(dbFile);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbFile);

    if (!db.open()) {
        QMessageBox::critical(this, "DB Error", db.lastError().text());
        canOpenDB = false;
    }
    else {
        canOpenDB = true;

        QSqlQuery query;

        query.exec("CREATE TABLE IF NOT EXISTS "
                    "[messages] ("
                    " id TEXT PRIMARY KEY NOT NULL, "
                    " value TEXT NOT NULL, "
                    " UNIQUE (id) "
                    ");");

        query.clear();

        QSqlTableModel *model = new QSqlTableModel();
        model->setTable("messages");
        model->select();
        model->setHeaderData(0, Qt::Horizontal, "ID");
        model->setHeaderData(1, Qt::Horizontal, "Message");
        model->setSort(0, Qt::AscendingOrder);
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        ui->tblMessages->setModel(model);
        //ui->tblMessages->setSortingEnabled(true);
        ui->tblMessages->setColumnWidth(0, 220);
        ui->tblMessages->setColumnWidth(1, 440);
        ui->tblMessages->setSelectionMode(QAbstractItemView::SingleSelection);

        QObject::connect(ui->btnSave, SIGNAL(clicked(bool)),
                         model, SLOT(submitAll()));

        QObject::connect(ui->btnRevert, SIGNAL(clicked(bool)),
                         model, SLOT(revertAll()));
        QObject::connect(ui->btnRevert, SIGNAL(clicked(bool)),
                         this, SLOT(RevertHiddenRows()));

        QObject::connect(ui->btnAddRow, SIGNAL(clicked(bool)),
                         this, SLOT(AddEmptyRow()));

        QObject::connect(ui->btnEraseRow, SIGNAL(clicked(bool)),
                         this, SLOT(EraseRow()));

        QObject::connect(ui->btnGenerate, SIGNAL(clicked(bool)),
                         this, SLOT(Generate()));
    }
}

MainWindow::~MainWindow()
{
    db.close();
    QSqlDatabase::removeDatabase("QSQLITE");

    /* Cleaning-up db */
    Vacuum(dbFile);

    delete textTool;
    delete ui;
}

void MainWindow::Vacuum(const char *dbFile) {
    sqlite3 *db;
    int rc = sqlite3_open(dbFile, &db);
    if (!rc)
        sqlite3_exec(db, "VACUUM;", 0, 0, 0);
}

void MainWindow::AddEmptyRow() {
    QAbstractItemModel *model = ui->tblMessages->model();
    int r = model->rowCount();
    model->insertRow(r);
    ui->tblMessages->setCurrentIndex(model->index(r, 0));
}

void MainWindow::EraseRow() {
    QAbstractItemModel *model = ui->tblMessages->model();
    int r = ui->tblMessages->selectionModel()->currentIndex().row();
    ui->tblMessages->setRowHidden(r, true);
    model->removeRow(r);
}

void MainWindow::RevertHiddenRows() {
    QAbstractItemModel *model = ui->tblMessages->model();
    for (int i = 0; i < model->rowCount(); ++i)
        ui->tblMessages->setRowHidden(i, false);
}

void MainWindow::Generate() {
    QString folder(QFileDialog::getExistingDirectory(this,
                                                     "Pick a folder to generate message files",
                                                     QDir::homePath() + "/Desktop/"));

    if (!folder.isNull()) {
        QFile confFile(folder + "/UDKGameMessages.ini");
        QFile ucFile(folder + "/GameMessages.uc");

        if (!confFile.open(QIODevice::WriteOnly | QIODevice::Text) ||
                !ucFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::critical(this, "IO Error", "File generation is not possible because of IO error.");
            return;
        }

        QTextStream confOut(&confFile);
        QTextStream ucOut(&ucFile);
        confOut.setCodec("UTF-16");
        confOut.setGenerateByteOrderMark(true);

        QString newLine("\n");
        QString tabSpace("\t");

        confOut << "[GameUi.GameMessages]" << newLine;
        ucOut << "class GameMessages extends object"
               << newLine
               << tabSpace
               << "config ( GameMessages );"
               << newLine << newLine << newLine;

        QSqlQuery query("SELECT id,value FROM [messages]");
        QSqlRecord record = query.record();
        while (query.next()) {
            QString id(query.value(record.indexOf("id")).toString().toUtf8().constData());
            QString val(QString::fromStdWString(
                           textTool->GetFlashStr(query.value(record.indexOf("value")).toString().toStdWString(),
                                                 false)));

            confOut << id << "=" << val << newLine;
            ucOut << "var const config string " << id << ";" << newLine;
        }

        ucOut << newLine << newLine
               << "DefaultProperties"
               << newLine
               << "{"
               << newLine
               << "}"
               << newLine;

        confFile.flush();
        ucFile.flush();
        confFile.close();
        ucFile.close();

        QMessageBox::information(this, tr("Done"), tr("Generated Successfully!"));
    }
}
