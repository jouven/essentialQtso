#include "essentialQt.hpp"

#include <QFile>
#ifdef __ANDROID__
#include <QDir>
#endif

int returnValue_ext = 0;

//void qtCout_f(const QString &msg_par_con, const bool addEndl_par_con)
//{
//    static QMutex tmp;
//    tmp.lock();
//    if (addEndl_par_con)
//    {
//        qtOutRef_ext() << msg_par_con << endl;
//    }
//    else
//    {
//        qtOutRef_ext() << msg_par_con;
//    }
//    tmp.unlock();
//}

QTextStream& qtOutRef_ext()
{
    //Connect the stdout to my qout textstream
    static QTextStream qout_glo(stdout);
    return qout_glo;
}

QTextStream& qtErrRef_ext()
{
    //Connect the stderr to my qerr textstream
    static QTextStream qerr_glo(stderr);
    return qerr_glo;
}

QMutex& qtOutMutexRef_glo()
{
    static QMutex qoutMutex_glo;
    return qoutMutex_glo;
}

//QTimer* qtCycleRef_ext(nullptr);

std::pair<QString, bool> configFile_ext(QString(), false);

QString configFileDefaultPath_f()
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
    return QDir::currentPath() + "/" + QCoreApplication::applicationName() + "_config.json";
#else
    return QCoreApplication::applicationDirPath() + "/" + QCoreApplication::applicationName() + "_config.json";
#endif
}

void locateConfigFilePath_f(
        const QCommandLineParser& commandLineParser_par_con
        , bool checkFirstArgument_par_con)
{
    QString configFilePathOrErrorStr;
    bool configFileFound(false);

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
                    configFilePathOrErrorStr.append("Config file path is empty");
                    break;
                }

                if (not QFile::exists(configjsonAlternativePathStr))
                {
                    configFilePathOrErrorStr.append("Config file path doesn't exist " + configjsonAlternativePathStr);
                    break;
                }
                configFilePathOrErrorStr = configjsonAlternativePathStr;
                configFileFound = true;
                break;
            }
        }
    }

    //--configFile="somePath" case
    if (not configFileFound and commandLineParser_par_con.isSet("configFile"))
    {
        QString configjsonAlternativePathStr(commandLineParser_par_con.value("configFile"));
        while (true)
        {
            if (configjsonAlternativePathStr.isEmpty())
            {
                configFilePathOrErrorStr.append("Config file path is empty");
                break;
            }

            if (not QFile::exists(configjsonAlternativePathStr))
            {
                configFilePathOrErrorStr.append("Config file path doesn't exist " + configjsonAlternativePathStr);
                break;
            }
            configFilePathOrErrorStr = configjsonAlternativePathStr;
            configFileFound = true;
            break;
        }
    }

    if (not configFileFound)
    {
        if (not QFile::exists(configFileDefaultPath_f()))
        {
            configFilePathOrErrorStr.append("Config file path doesn't exist " + configFileDefaultPath_f());
        }
        else
        {
            configFilePathOrErrorStr = configFileDefaultPath_f();
            configFileFound = true;
        }
    }
    configFile_ext = {configFilePathOrErrorStr, configFileFound};
}

std::pair<QString, bool> configFilePath_f()
{
    return configFile_ext;
}


