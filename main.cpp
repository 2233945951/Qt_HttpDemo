#include <QApplication>
#include <QPushButton>
#include "HttpInterface.h"
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    HttpInterface anInterface;
    anInterface.get(QUrl("https://lj.lbbai.com/"),[&](const QByteArray& byteArray)->void*{
        qDebug()<<QString(byteArray);
    });
    return QApplication::exec();
}
