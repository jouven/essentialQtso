
#ifndef ESSENTIALQTSO_FILENAMING_HPP
#define ESSENTIALQTSO_FILENAMING_HPP

#include "crossPlatformMacros.hpp"

#include <QString>

//just to keep all the apps files the same way

enum class fileTypes_ec
{
    //don't use empty, it's just there as default/null value
    empty
    , config
    , translationConfig
    , log
};

//values are camelcase
extern EXPIMP_ESSENTIALQTSO QString fileTypeToString_f(const fileTypes_ec fileType_par_con);

//extensions start with a dot i.e. ".log"
extern EXPIMP_ESSENTIALQTSO QString fileTypeToExtension_f(const fileTypes_ec fileType_par_con);

#endif // ESSENTIALQTSO_FILENAMING_HPP


