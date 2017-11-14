#include "essentialQt.hpp"

#include <QFile>

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
        QString executablePathConfigFileTmp(QCoreApplication::applicationDirPath() + "/" + QCoreApplication::applicationName() + "_config.json");
        if (not QFile::exists(executablePathConfigFileTmp))
        {
            configFilePathOrErrorStr.append("Config file path doesn't exist " + executablePathConfigFileTmp);
        }
        else
        {
            configFilePathOrErrorStr = executablePathConfigFileTmp;
            configFileFound = true;
        }
    }
    configFile_ext = {configFilePathOrErrorStr, configFileFound};
}

std::pair<QString, bool> configFilePath_f()
{
    return configFile_ext;
}
