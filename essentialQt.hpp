
#ifndef ESSENTIALQTSO_ESSENTIAL_HPP
#define ESSENTIALQTSO_ESSENTIAL_HPP

#include "crossPlatformMacros.hpp"

#include "filenaming.hpp"

//#include <QCommandLineParser>
#include <QTextStream>
#include <QMutex>
#include <QMutexLocker>

//#include <utility>

extern EXPIMP_ESSENTIALQTSO int returnValue_ext;

//use this to use qtOutRef_ext in a thread-safe way (debug purposes)
#define QOUT_TS(X) {QMutexLocker qOutLockerTmp(&qtStdoutMutexRef_glo()); qtStdout_f() << X;}
#define QERR_TS(X) {QMutexLocker qOutLockerTmp(&qtStderrMutexRef_glo()); qtStderr_f() << X;}

//WARNING the "autoflushing" will only happen if the functions that do it are called from a thread with an execution loop

extern EXPIMP_ESSENTIALQTSO QTextStream& qtStdout_f();
//print the string to stdout-QTextStream
//autoflushes after 1s if no more text is outputed using this functions
extern EXPIMP_ESSENTIALQTSO void qtOut_f(const QString& text_par_con);
//same as above but adds a newline if necessary at the start, detects if last outputed text already did it (when using this functions only,
//doesn't detect multiple newline characters at the end/start)
//autoflushes after 1s if no more text is outputed using this functions
extern EXPIMP_ESSENTIALQTSO void qtOutLine_f(const QString& text_par_con);

//Connect the stderr to my qerr textstream, not thread-safe
extern EXPIMP_ESSENTIALQTSO QTextStream& qtStderr_f();
//print the string to stderr-QTextStream
//autoflushes after 1s if no more text is outputed using this functions
extern EXPIMP_ESSENTIALQTSO void qtErr_f(const QString& text_par_con);
//same as above but adds a newline if necessary at the start, detects if last outputed text already did it (when using this functions only,
//doesn't detect multiple newline characters at the end/start)
//autoflushes after 1s if no more text is outputed using this functions
extern EXPIMP_ESSENTIALQTSO void qtErrLine_f(const QString& text_par_con);

//by default the functions above are not threadsafe,
//except the flusing part because there is timer that controls the automatic flushing that needs to be "protected",
//these mutexes can be used to make it threadsafe when more than one thread tries to "stream out" at the same time
extern EXPIMP_ESSENTIALQTSO QMutex& qtStdoutMutexRef_glo();

extern EXPIMP_ESSENTIALQTSO QMutex& qtStderrMutexRef_glo();

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

extern EXPIMP_ESSENTIALQTSO QString executableName_f();

//return value example: config --> ".json"
//extern EXPIMP_ESSENTIALQTSO QString fileTypeExtension_f(const fileTypes_ec fileType_par_con);

//return value example: config --> /a/random/path/applicationname_config
//extension must be added if required
extern EXPIMP_ESSENTIALQTSO QString fileTypeBasePath_f(const fileTypes_ec fileType_par_con);

//returns a single path for the the fileType
//i.e. config --> /a/random/path/applicationname_config.json
//don't use for multiple file cases, use a combination of fileTypeBasePath_f + X + fileTypeExtension_f
extern EXPIMP_ESSENTIALQTSO QString fileTypePath_f(const fileTypes_ec fileType_par_con);

#endif // ESSENTIALQTSO_ESSENTIAL_HPP
