#include "essentialQt.hpp"

#include <QCoreApplication>
#include <QFile>
#ifdef __ANDROID__
#include <QDir>
#endif

#include <QTimer>

int returnValue_ext = 0;

//Connect the stdout to my qout textstream
QTextStream& qtStdout_f()
{
    static QTextStream qout_glo(stdout);
    return qout_glo;
}

void flushQtStdout_f()
{
    qtStdout_f().flush();
}

QTimer* stdoutflushTimerPtr(nullptr);
void flushQtStdoutTimer_f()
{
    if (stdoutflushTimerPtr == nullptr)
    {
        stdoutflushTimerPtr = new QTimer(qApp);
        stdoutflushTimerPtr->setSingleShot(true);
        QObject::connect(stdoutflushTimerPtr, &QTimer::timeout, flushQtStdout_f);
        stdoutflushTimerPtr->start(1000);
    }
    else
    {
        stdoutflushTimerPtr->start(1000);
    }
}

bool stdoutLastCharacterPrintedWasNewLine(true);
void qtOut_f(const QString& text_par_con)
{
    qtStdout_f() << text_par_con;
    stdoutLastCharacterPrintedWasNewLine = text_par_con.endsWith('\n');
    flushQtStdoutTimer_f();
}

void addNewLineToText_f(QString& text_par)
{
    if (stdoutLastCharacterPrintedWasNewLine and text_par.startsWith('\n'))
    {
        text_par.remove(0,1);
    }
    if (not stdoutLastCharacterPrintedWasNewLine and not text_par.startsWith('\n'))
    {
        text_par.prepend('\n');
    }
}

void qtOutLine_f(const QString& text_par_con)
{
    QString textTmp(text_par_con);
    addNewLineToText_f(textTmp);
    qtStdout_f() << textTmp;
    stdoutLastCharacterPrintedWasNewLine = text_par_con.endsWith('\n');
    flushQtStdoutTimer_f();
}

QTextStream& qtStderr_f()
{
    //Connect the stderr to my qerr textstream
    static QTextStream qerr_glo(stderr);
    return qerr_glo;
}

void flushQtStderr_f()
{
    qtStderr_f().flush();
}

QTimer* stderrflushTimerPtr(nullptr);
void flushQtStderrTimer_f()
{
    if (stderrflushTimerPtr == nullptr)
    {
        stderrflushTimerPtr = new QTimer(qApp);
        stderrflushTimerPtr->setSingleShot(true);
        QObject::connect(stdoutflushTimerPtr, &QTimer::timeout, flushQtStderr_f);
        stderrflushTimerPtr->start(1000);
    }
    else
    {
        stderrflushTimerPtr->start(1000);
    }
}

bool stderrLastCharacterPrintedWasNewLine(true);
void qtErr_f(const QString& text_par_con)
{
    qtStderr_f() << text_par_con;
    stderrLastCharacterPrintedWasNewLine = text_par_con.endsWith('\n');
    flushQtStderrTimer_f();
}

void qtErrLine_f(const QString& text_par_con)
{
    QString textTmp(text_par_con);
    addNewLineToText_f(textTmp);
    qtStderr_f() << textTmp;
    stderrLastCharacterPrintedWasNewLine = text_par_con.endsWith('\n');
    flushQtStderrTimer_f();
}

QMutex& qtOutMutexRef_glo()
{
    static QMutex qoutMutex_glo;
    return qoutMutex_glo;
}

//QTimer* qtCycleRef_ext(nullptr);

std::pair<QString, bool> configFile_ext(QString(), false);

QString appDirectoryPath_f()
{
    //the way android deploys programs, APK, AFAIK it's pretty railroaded,
    //The "executable", which is a .so file, ends on a "library" folder and doesn't allow writing...
    //solution? write on the folder where the app is call/run, which is writable and is per each app.
    //For my sole test this is /data/data/org.qtproject.*packagename*/
    //and after researching a bit of "android config paths" this path
    //falls into that category...
    //I don't know if just copying libraries and launching is feasible like on windows/*nix because
    //C++ on android works by proxy loading and external library in Java
#ifdef __ANDROID__
    return QDir::currentPath();
#else
    return QCoreApplication::applicationDirPath();
#endif
}

QString appFilePath_f()
{
    return appDirectoryPath_f() + "/" + QCoreApplication::applicationName();
}

QString fileTypeExtension_f(const fileTypes_ec fileType_par_con)
{
    QString resultTmp;
    if (fileType_par_con == fileTypes_ec::empty)
    {
    }
    else
    {
        resultTmp = typesToExtensionUMap_ext_con.at(fileType_par_con);
    }
    return resultTmp;
}

QString fileTypePath_f(const fileTypes_ec fileType_par_con)
{
    QString resultTmp;
    if (fileType_par_con == fileTypes_ec::empty)
    {
    }
    else
    {
        resultTmp = fileTypeBasePath_f(fileType_par_con) + typesToExtensionUMap_ext_con.at(fileType_par_con);
    }
    return resultTmp;
}

void locateConfigFilePath_f(
        const QCommandLineParser& commandLineParser_par_con
        , bool checkFirstArgument_par_con
        , bool required_par_con)
{
    QString configFilePathOrErrorStr;
    bool configFileFound(false);
    constexpr fileTypes_ec fileTypeTmp_constexpr(fileTypes_ec::config);

    //first argument case
    if (checkFirstArgument_par_con)
    {
        const QStringList parsedPositionalArgs(commandLineParser_par_con.positionalArguments());
        if (parsedPositionalArgs.size() > 0)
        {
            QString configjsonAlternativePathStr(parsedPositionalArgs.at(0));
            while (true)
            {
                if (configjsonAlternativePathStr.isEmpty())
                {
                    configFilePathOrErrorStr.append("\nConfig file path is empty");
                    break;
                }

                if (not QFile::exists(configjsonAlternativePathStr))
                {
                    configFilePathOrErrorStr.append("\nConfig file path doesn't exist " + configjsonAlternativePathStr);
                    break;
                }
                configFilePathOrErrorStr = configjsonAlternativePathStr;
                configFileFound = true;
                break;
            }
        }
    }

    //--configFile="somePath" case
    if (not configFileFound and (required_par_con or commandLineParser_par_con.isSet("configFile")))
    {
        QString configjsonAlternativePathStr(commandLineParser_par_con.value("configFile"));
        while (true)
        {
            if (configjsonAlternativePathStr.isEmpty())
            {
                configFilePathOrErrorStr.append("\nConfig file path is empty");
                break;
            }

            if (not QFile::exists(configjsonAlternativePathStr))
            {
                configFilePathOrErrorStr.append("\nConfig file path doesn't exist " + configjsonAlternativePathStr);
                break;
            }
            configFilePathOrErrorStr = configjsonAlternativePathStr;
            configFileFound = true;
            break;
        }
    }

    if (not configFileFound)
    {
        if (not QFile::exists(fileTypePath_f(fileTypeTmp_constexpr)))
        {
            configFilePathOrErrorStr.append("\nConfig file path doesn't exist " + fileTypePath_f(fileTypeTmp_constexpr));
        }
        else
        {
            configFilePathOrErrorStr = fileTypePath_f(fileTypeTmp_constexpr);
            configFileFound = true;
        }
    }

    if (required_par_con and not configFileFound)
    {
        configFilePathOrErrorStr.append("\nNo --configFile argument provided");
    }

    configFile_ext = {configFilePathOrErrorStr, configFileFound};
}

std::pair<QString, bool> configFilePath_f()
{
    return configFile_ext;
}


QString fileTypeBasePath_f(const fileTypes_ec fileType_par_con)
{
    QString resultTmp;
    if (fileType_par_con == fileTypes_ec::empty)
    {
    }
    else
    {
        resultTmp = appFilePath_f() + "_" + typesToNamesUMap_ext_con.at(fileType_par_con);
    }
    return resultTmp;
}


