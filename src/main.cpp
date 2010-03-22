#include <QtGui/QApplication>
#include "wnd/mainwnd.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("AlexSnet");
    QCoreApplication::setOrganizationDomain("alexsnet.ru");
    QCoreApplication::setApplicationName("MusicFinder");
    a.setQuitOnLastWindowClosed(true);

    mainWnd w;
    w.show();
    return a.exec();
}
