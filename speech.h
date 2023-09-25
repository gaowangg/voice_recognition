#ifndef SPEECH_H
#define SPEECH_H

#include <QObject>
#include <QString>
#include "http.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QJsonArray>
#include <QHostInfo>
#include <QFile>
#include <QMessageBox>

const QString baidu_tokenUrl = "https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id=%1&client_secret=%2&";
const QString client_id = "BvghsysoWb7L5n5R55PN03Fd";
const QString client_secret = "O7ouQyKIKd84bDvj6EHBjkwRqZoSc9Sl";


const QString baidu_speechUrl="http://vop.baidu.com/server_api?dev_pid=1537&cuid=%1&token=%2";


class Speech : public QObject
{
    Q_OBJECT
public:
    explicit Speech(QObject *parent = nullptr);

    //语言识别
    QString speechReconition(QString filename);

    //解析json
    QString getJsonValue(QByteArray replyData,QString key);

signals:

};

#endif // SPEECH_H
