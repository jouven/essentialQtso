#include "enumClass.hpp"

#include <QMap>
#include <unordered_map>

const std::unordered_map<messageType_ec, QString>& messageTypeToStringUMap_ref()
{
    static const std::unordered_map<messageType_ec, QString> messageTypeToStringUMap_sta_con(
    {
      {	messageType_ec::information, "information" }
      , {	messageType_ec::warning, "warning" }
      , {	messageType_ec::error, "error" }
      , {	messageType_ec::debug, "debug" }
      , {	messageType_ec::question, "question" }
    });
    return messageTypeToStringUMap_sta_con;
}

const QMap<QString, messageType_ec>& stringToMessageTypeMap_ref()
{
    static const QMap<QString, messageType_ec> stringToMessageTypeMap_sta_con(
    {
    //Keys are lower case because this way when reading from json we can "lower" w/e is
    //there and compare, allowing to ignore case
         {	"information", messageType_ec::information}
        , {	"warning", messageType_ec::warning}
        , {	"error", messageType_ec::error}
        , {	"debug", messageType_ec::debug}
        , {	"question", messageType_ec::question}
    });
    return stringToMessageTypeMap_sta_con;
}

QString messageTypeToString_f(const messageType_ec messageType_par_con)
{
    return messageTypeToStringUMap_ref().at(messageType_par_con);
}

messageType_ec stringToMessageTypeTo_f(const QString& messageTypeString_par_con)
{
    return stringToMessageTypeMap_ref().value(messageTypeString_par_con, messageType_ec::empty);
}

QList<QString> messageTypeStringValues_f()
{
    return stringToMessageTypeMap_ref().keys();
}
