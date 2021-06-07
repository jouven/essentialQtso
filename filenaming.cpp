#include "filenaming.hpp"

#include <unordered_map>

const std::unordered_map<fileTypes_ec, QString>& fileTypesToStringUMap_ref()
{
    static const std::unordered_map<fileTypes_ec, QString> fileTypesToStringUMap_ext_con(
    {
        {	fileTypes_ec::config, "config" }
        , {	fileTypes_ec::translationConfig, "translationConfig" }
        , {	fileTypes_ec::log, "log" }
    });
    return fileTypesToStringUMap_ext_con;
}

const std::unordered_map<fileTypes_ec, QString>& fileTypesToExtensionUMap_ref()
{
    static const std::unordered_map<fileTypes_ec, QString> fileTypesToExtensionUMap_ext_con(
    {
        {	fileTypes_ec::config, ".json" }
        , {	fileTypes_ec::translationConfig, ".json" }
        , {	fileTypes_ec::log, ".log" }
    });
    return fileTypesToExtensionUMap_ext_con;
}

QString fileTypeToString_f(const fileTypes_ec fileType_par_con)
{
    return fileTypesToStringUMap_ref().at(fileType_par_con);
}

QString fileTypeToExtension_f(const fileTypes_ec fileType_par_con)
{
    return fileTypesToExtensionUMap_ref().at(fileType_par_con);
}
