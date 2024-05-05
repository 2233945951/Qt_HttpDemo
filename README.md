# Qt_HttpDemo
使用qt阻塞请求get和post接口，支持lanbda回调
#### 使用
#### Get
```c++
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
```
或
```c++
#include <QApplication>
#include <QPushButton>
#include "HttpInterface.h"
void get(const QByteArray& byteArray){
    qDebug()<<QString(byteArray);
}
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    HttpInterface anInterface;
    anInterface.get(QUrl("https://lj.lbbai.com/"),&get);
    return QApplication::exec();
}
```
#### post
还没试，应该问题不大(doge)