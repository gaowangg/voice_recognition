#ifndef HTTP_H
#define HTTP_H

#include <QObject>
#include <QWidget>
#include <QMap>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QDebug>

class Http : public QObject
{
    Q_OBJECT
public:
    explicit Http(QObject *parent = nullptr);

    //发送请求
    bool post_sync(QString Url,QMap<QString,QString> header,QByteArray requestData,QByteArray& replyData);

signals:

};

#endif // HTTP_H
