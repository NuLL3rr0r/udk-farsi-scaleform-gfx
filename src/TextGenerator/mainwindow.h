#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>

namespace UTFTools {
    class Text2Flash;
}

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool canOpenDB;

public slots:
    void AddEmptyRow();
    void EraseRow();
    void RevertHiddenRows();
    void Generate();

private:
    Ui::MainWindow *ui;
    UTFTools::Text2Flash *textTool;

    void Vacuum(const char *dbFile);

    const char *dbFile;
    QSqlDatabase db;
};

#endif // MAINWINDOW_H
