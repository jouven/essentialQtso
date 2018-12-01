
#ifndef ESSENTIALQTSO_FILENAMING_HPP
#define ESSENTIALQTSO_FILENAMING_HPP

//just to keep all the apps files the same way

#include <QString>

#include <unordered_map>

enum class fileTypes_ec
{
    //don't use empty, it's just there as default/null value
    empty
    , config
    , translationConfig
    , log
};

//values are camelcase
extern const std::unordered_map<fileTypes_ec, QString> typesToNamesUMap_glo_sta_con;

//extensions start with a dot i.e. ".log"
extern const std::unordered_map<fileTypes_ec, QString> typesToExtensionUMap_glo_sta_con;

#endif // ESSENTIALQTSO_FILENAMING_HPP


