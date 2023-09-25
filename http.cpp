#include "http.h"

Http::Http(QObject *parent) : QObject(parent)
{

}

 bool Http::post_sync(QString Url,QMap<QString,QString> header,QByteArray requestData,QByteArray& replyData)
 {
     //执行发送请求动作
     QNetworkAccessManager manager;

     //创建请求对象-整合url和header
     QNetworkRequest request;
     request.setUrl(Url);

     //遍历header
     QMapIterator<QString,QString> iter(header);
     while(iter.hasNext()){
         iter.next();
         request.setRawHeader(iter.key().toLatin1(),iter.value().toLatin1());
     }

     QNetworkReply *reply = manager.post(request,requestData);
     //等待服务器返回-阻塞状态
     QEventLoop loop;
     //当reply收到服务器返回的数据时,会产生结束的信号
     connect(reply,&QNetworkReply::finished,&loop,&QEventLoop::quit);
     loop.exec();

     if(reply!=nullptr&&reply->error()==QNetworkReply::NoError){
         replyData=reply->readAll();
         //qDebug()<<replyData;
         return true;
     }else{
         qDebug()<<"请求失败";
         return  false;
     }

 }
