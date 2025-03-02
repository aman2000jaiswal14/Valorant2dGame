#include "mainwindow.h"

#include <QApplication>
#include "communicationchannel.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    CommunicationChannel::instance();
    w.show();
    return a.exec();
}
