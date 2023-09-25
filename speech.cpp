#include "speech.h"

Speech::Speech(QObject *parent) : QObject(parent)
{

}

QString Speech:: speechReconition(QString filename)
{
    //1.先获取令牌access_token
    //先组合用来获取access_token的url
    QString tokenUrl=baidu_tokenUrl.arg(client_id).arg(client_secret);

    //头部信息
    QMap<QString,QString> header;
    header.insert(QString("Content-Type:"),QString("audio/pcm;rate=16000"));

    //发送的数据
    QByteArray requesData;
    //服务器返回的数据
    QByteArray replyData;
    QString access_token;

    //第一次发送http请求,获取access_token
    Http myhttp;
    bool ret = myhttp.post_sync(tokenUrl,header,requesData,replyData);
    if(ret){
        QString key = "access_token";
        access_token = getJsonValue(replyData,key);
       // qDebug()<<access_token;
    }

    //第二次发送http请求,获取语言识别结果
    QString speechUrl = baidu_speechUrl.arg(QHostInfo::localHostName()).arg(access_token);

    //打开已经录制好的文件,并将音频文件转换成Qbytearry类型
    QFile file;
    file.setFileName(filename);
    file.open(QIODevice::ReadOnly);
    requesData=file.readAll();
    file.close();

    replyData.clear();
    ret = myhttp.post_sync(speechUrl,header,requesData,replyData);
    if(ret){
        //解析服务器返回的json数据
        QString key = "result";
        QString retText = getJsonValue(replyData,key);
        //qDebug()<<retText;
        return retText;
    }
    else{
        QMessageBox::warning(NULL,"warning","识别失败");
    }
    return "";

}

//解析json
QString Speech:: getJsonValue(QByteArray replyData,QString key)
{
    QJsonParseError parseError;
    //将replyData转换成对应的json文件
    QJsonDocument jsonDocuent=QJsonDocument::fromJson(replyData,&parseError);

    if(parseError.error==QJsonParseError::NoError){
        //json文件对象是否存在
        if(jsonDocuent.isObject()){
            //将jsonDocument转化成json对象
            QJsonObject jsonObj =jsonDocuent.object();
            //如何jsonObj包含了access_token字样,去除后面对应值
            if(jsonObj.contains(key)){
                QJsonValue jsonValue = jsonObj.value(key);
                //如果jsonvalue值为字符串
                if(jsonValue.isString()){
                    return jsonValue.toString();
                }
                //如果jsonvalue值为数组
                else if(jsonValue.isArray()){
                    QJsonArray jsonArr = jsonValue.toArray();
                    QJsonValue firstRet=jsonArr.at(0);
                    return firstRet.toString();
                }
            }
        }
   }
    return "";
}
