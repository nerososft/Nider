#include "jsonhelper.h"
#include <QString>

JsonHelper::JsonHelper()
{

}


QJsonObject JsonHelper::getJsonObjectFromString(const QString jsonString){
   QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonString.toLocal8Bit().data());
   if( jsonDocument.isNull() ){
       qDebug()<< "===> please check the string "<< jsonString.toLocal8Bit().data();
   }
   QJsonObject  jsonObject = jsonDocument.object();
   return jsonObject;
}


QString  JsonHelper::getStringFromJsonObject(const QJsonObject& jsonObject){
   return QString(QJsonDocument(jsonObject).toJson());
}

QJsonArray JsonHelper::getJsonArrayFromString(const QString jsonString){
    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonString.toLocal8Bit().data());
    if( jsonDocument.isNull() ){
        qDebug()<< "===> please check the string "<< jsonString.toLocal8Bit().data();
    }
    QJsonArray  jsonArray = jsonDocument.array();

    return jsonArray;
}


