
#ifndef ESSENTIALQTSO_ESSENTIAL_HPP
#define ESSENTIALQTSO_ESSENTIAL_HPP

#include "crossPlatformMacros.hpp"

#include "filenaming.hpp"

#include <QCommandLineParser>
#include <QTextStream>
#include <QMutex>
#include <QMutexLocker>

#include <utility>

extern EXPIMP_ESSENTIALQTSO int returnValue_ext;

//use this to use qtOutRef_ext in a thread-safe way
#define QOUT_TS(X) {QMutexLocker qOutLockerTmp(&qtOutMutexRef_glo()); qtOutRef_ext() << X;}

//Connect the stdout to my qout textstream, not thread-safe
extern EXPIMP_ESSENTIALQTSO QTextStream& qtOutRef_ext();

//Connect the stderr to my qerr textstream, not thread-safe
extern EXPIMP_ESSENTIALQTSO QTextStream& qtErrRef_ext();

//necessary for the QOUT_TS macro
extern EXPIMP_ESSENTIALQTSO QMutex& qtOutMutexRef_glo();

//extern QTimer* qtCycleRef_ext;

//windows/*nix same as QCoreApplication::applicationDirPath()
//in android QDir::currentPath(), since the "executable" in android is in a non-writable path
//return the path from where there program is called
extern EXPIMP_ESSENTIALQTSO QString appDirectoryPath_f();
//above + + "/" + QCoreApplication::applicationName()
//base file name-path for the process/application,
//i.e /a/random/path/applicationname
//used to load/save additional files
//configFileDefaultPath_f uses it
extern EXPIMP_ESSENTIALQTSO QString appFilePath_f();

//return value example: config --> ".json"
extern EXPIMP_ESSENTIALQTSO QString fileTypeExtension_f(const fileTypes_ec fileType_par_con);

//return value example: config --> /a/random/path/applicationname_config
//extension must be added if required
extern EXPIMP_ESSENTIALQTSO QString fileTypeBasePath_f(const fileTypes_ec fileType_par_con);

//returns a single path for the the fileType
//i.e. config --> /a/random/path/applicationname_config.json
//don't use for multiple file cases, use a combination of fileTypeBasePath_f + X + fileTypeExtension_f
extern EXPIMP_ESSENTIALQTSO QString fileTypePath_f(const fileTypes_ec fileType_par_con);

//check for the config file (updates configFilePath_f):
//1 if checkFirstArgument_par_con = true, the first argument will be check if it's a file and exists
//2 if checkFirstArgument_par_con = false, it will check for --configFile="somepath"
//3 otherwise configFileDefaultPath_f will be checked
//it's NOT check if the file is a valid config file, just checks existence
extern EXPIMP_ESSENTIALQTSO void locateConfigFilePath_f(
        const QCommandLineParser& commandLineParser_par_con
        //there is this argument because it can be ambiguous
        //positional arguments might be used for other stuff that might be paths
        //but not the config path
        , bool checkFirstArgument_par_con);

//if the bool is false, QString is an error message
//else it's the filePath
//if QString is empty, it hasn't been initialized
extern EXPIMP_ESSENTIALQTSO std::pair<QString, bool> configFilePath_f();

#endif // ESSENTIALQTSO_ESSENTIAL_HPP
