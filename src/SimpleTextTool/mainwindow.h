#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private slots:
    void on_btnGenerate_clicked();

private:
    Ui::MainWindow *ui;
    UTFTools::Text2Flash *textTool;
};

#endif // MAINWINDOW_H
