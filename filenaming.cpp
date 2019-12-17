#include "filenaming.hpp"


const std::unordered_map<fileTypes_ec, QString> typesToNamesUMap_ext_con(
{
    {	fileTypes_ec::config, "config" }
    , {	fileTypes_ec::translationConfig, "translationConfig" }
    , {	fileTypes_ec::log, "log" }
});

const std::unordered_map<fileTypes_ec, QString> typesToExtensionUMap_ext_con(
{
    {	fileTypes_ec::config, ".json" }
    , {	fileTypes_ec::translationConfig, ".json" }
    , {	fileTypes_ec::log, ".json" }
});

