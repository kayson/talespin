#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //a.setStyle("plastique");
    MainWindow w;
    w.show();

//    QStringList list;
//    list << "Roboto-Medium.ttf";
//    int fontID(-1);
//    bool fontWarningShown(false);
//    for (QStringList::const_iterator constIterator = list.constBegin(); constIterator != list.constEnd(); ++constIterator) {
//        QFile res(":/MyFiles/" + *constIterator);
//        if (res.open(QIODevice::ReadOnly) == false) {
//            if (fontWarningShown == false) {
//                QMessageBox::warning(0, "Application", (QString)"Impossible heje " + QChar(0x00AB) + " RobotoMedium " + QChar(0x00BB) + ".");
//                fontWarningShown = true;
//            }
//        } else {
//            fontID = QFontDatabase::addApplicationFontFromData(res.readAll());
//            if (fontID == -1 && fontWarningShown == false) {
//                QMessageBox::warning(0, "Application", (QString)"hej hej monika " + QChar(0x00AB) + " Roboto-Medium " + QChar(0x00BB) + ".");
//                fontWarningShown = true;
//            }
//        }
//    }

    return a.exec();
}
