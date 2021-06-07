#ifndef ESSENTIALQTSO_ENUMCLASS_HPP
#define ESSENTIALQTSO_ENUMCLASS_HPP

#include "crossPlatformMacros.hpp"

#include <QString>
#include <QList>

enum class messageType_ec
{
    //empty value is used to know if a variable is not initialized
    empty = 0
    , information = 1
    , warning = 2
    , error = 3
    , debug = 4
    , question = 5
};

//mapping to QString
extern EXPIMP_ESSENTIALQTSO QString messageTypeToString_f(const messageType_ec messageType_par_con);
extern EXPIMP_ESSENTIALQTSO messageType_ec stringToMessageTypeTo_f(const QString& messageTypeString_par_con);
extern EXPIMP_ESSENTIALQTSO QList<QString> messageTypeStringValues_f();

#endif // ESSENTIALQTSO_ENUMCLASS_HPP
