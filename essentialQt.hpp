//reusable header
#ifndef ESSENTIALQTSO_ESSENTIAL_HPP
#define ESSENTIALQTSO_ESSENTIAL_HPP

#include <QCommandLineParser>
#include <QTextStream>
#include <QMutex>
#include <QMutexLocker>

#include <utility>

//use this to use qtOutRef_ext in a thread-safe way
#define QOUT_TS(X) {QMutexLocker qOutLockerTmp(&qtOutMutexRef_glo()); qtOutRef_ext() << X;}

//Connect the stdout to my qout textstream, not thread-safe
extern QTextStream &qtOutRef_ext();
////same as above (and somewhat more limited), but thread-safe
//extern void qtCout_f(const QString& msg_par_con, const bool addEndl_par_con = false);
//Connect the stderr to my qerr textstream
extern QTextStream& qtErrRef_ext();

extern int returnValue_ext;
//necessary for the QOUT_TS macro
extern QMutex& qtOutMutexRef_glo();

//extern QTimer* qtCycleRef_ext;

//default path, even if a config file doesn't exist, it's necessary when saving
extern QString configFileDefaultPath_f();

//check for the config file (updates configFile_f):
//1 if checkFirstArgument_par_con = true, the first argument will be check if it's a file and exists
//2 if checkFirstArgument_par_con = false, it will check for --configFile="somepath"
//3 otherwise configFileDefaultPath_f will be checked
//it's NOT check if the file is a valid config file, just checks existence
extern void locateConfigFilePath_f(
        const QCommandLineParser& commandLineParser_par_con
        //there is this argument because it can be ambiguous
        //positional arguments might be used for other stuff that might be paths
        //but not the config path
        , bool checkFirstArgument_par_con);

//if the bool is false, QString is an error message
//else it's the filePath
//if QString is empty, it hasn't been initialized
extern std::pair<QString, bool> configFilePath_f();

#endif // ESSENTIALQTSO_ESSENTIAL_HPP
