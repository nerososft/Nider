#ifndef JSONHELPER_H
#define JSONHELPER_H
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include <QJsonArray>


class JsonHelper
{
public:
    JsonHelper();
    // QString >> QJson
    QJsonObject getJsonObjectFromString(const QString jsonString);
    // QJson >> QString
   QString  getStringFromJsonObject(const QJsonObject& jsonObject);

   QJsonArray getJsonArrayFromString(const QString jsonString);
};

#endif // JSONHELPER_H
