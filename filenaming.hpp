
#ifndef ESSENTIALQTSO_FILENAMING_HPP
#define ESSENTIALQTSO_FILENAMING_HPP

#include "crossPlatformMacros.hpp"

#include <QString>

#include <unordered_map>

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
extern EXPIMP_ESSENTIALQTSO const std::unordered_map<fileTypes_ec, QString> typesToNamesUMap_ext_con;

//extensions start with a dot i.e. ".log"
extern EXPIMP_ESSENTIALQTSO const std::unordered_map<fileTypes_ec, QString> typesToExtensionUMap_ext_con;

#endif // ESSENTIALQTSO_FILENAMING_HPP


