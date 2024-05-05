//
// Created by beni on 2024/4/30.
//

#include "HttpInterface.h"
#include <QUrl>
#include <QNetworkRequest>
#include <QEventLoop>
#include <QNetworkReply>

void HttpInterface::get(const QUrl &url, const CallBack& callBack) {
    if (callBack == nullptr)
        return;
    m_callBack=callBack;
    assert(!url.isEmpty());
    assert(url.isValid());
    QNetworkRequest qnr(url);
    QNetworkReply *reply = m_qnam.get(qnr);
    initNetworkParams(reply);
    QByteArray replyData = reply->readAll();
    responseStatusCheck(reply,replyData);
    m_callBack(replyData);
    reply->deleteLater();
    reply = nullptr;
}

void HttpInterface::initNetworkParams(const QNetworkReply *reply) {
    QEventLoop eventLoop;
    connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
}
/**
 *
 * @param url
 * @param data
 * @param callBack 回调
 */
void HttpInterface::post(const QUrl &url, const QString &data, const HttpInterface::CallBack &callBack) {
    if (callBack == nullptr)
        return;
    m_callBack=callBack;
    assert(!url.isEmpty());
    assert(url.isValid());
    QNetworkRequest qnr(url);
    QNetworkReply *reply = m_qnam.post(qnr,data.toUtf8());
    initNetworkParams(reply);
    QByteArray replyData = reply->readAll();
    responseStatusCheck(reply,replyData);
    m_callBack(replyData);
    reply->deleteLater();
    reply = nullptr;
}

void HttpInterface::responseStatusCheck(const QNetworkReply *reply,QByteArray& data) {
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QVariant redirectAttr = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    if (reply->error() || 300 == statusCode //状态码300 Multiple Choices，既不是错误也不算重定向，应该是qt bug
        || !redirectAttr.isNull()) {
        QString errString = reply->error() ? reply->errorString() : QString("发生重定向(%1)，不允许此情况").arg(
                statusCode);
        qDebug()<<"HttpInterface::get"<<QString("发送get请求时出现错误：\n网址：%1\n错误信息：%2").arg(reply->request().url().toDisplayString(),
                                                                                                    errString);
        data.clear();
    }
}
