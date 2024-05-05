//
// Created by beni on 2024/4/30.
//

#ifndef HTTPDEMO_HTTPINTERFACE_H
#define HTTPDEMO_HTTPINTERFACE_H

#include <QObject>
#include <QNetworkAccessManager>
class HttpInterface: public QObject{
    Q_OBJECT
private:
    QNetworkAccessManager m_qnam;
    using CallBack=std::function<void(QByteArray)>;
    CallBack m_callBack= nullptr;
private:
    static void initNetworkParams(const QNetworkReply* reply);
    static void responseStatusCheck(const QNetworkReply *reply,QByteArray& data);
public:
    void get(const QUrl& url,const CallBack& callBack);
    void post(const QUrl& url,const QString & data,const CallBack &callBack);
};


#endif //HTTPDEMO_HTTPINTERFACE_H
