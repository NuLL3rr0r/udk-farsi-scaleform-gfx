#include <string>
#include <unistd.h>
#include <QtGui/QApplication>
#include <Windows.h>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    try {
        if (argv[1] != NULL) {
            std::string path(argv[1]);
            path = path.substr(0, path.rfind("\\") + 1);
            chdir(path.c_str());
        }
    }
    catch (std::exception& ex) {
        std::string errTemp(ex.what());
        std::wstring err(errTemp.begin(), errTemp.end());
        MessageBox( NULL, err.c_str(), L"An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
        return -2;
    }

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    if (!w.canOpenDB) {
        return -1;
    }

    return a.exec();
}
