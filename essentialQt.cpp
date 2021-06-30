#include "essentialQt.hpp"

#include <QCoreApplication>
#include <QFile>
#include <QFileInfo>
#ifdef __ANDROID__
#include <QDir>
#endif

#include <QTimer>
#include <QThread>

int returnValue_ext = 0;

//Connect the stdout to my qout textstream
QTextStream& qtStdout_f()
{
    static QTextStream qout_glo(stdout);
    return qout_glo;
}

QTimer* stdoutflushTimerPtr(nullptr);
void flushQtStdout_f()
{
    QMutexLocker qOutLockerTmp(&qtStdoutMutexRef_glo());
    qtStdout_f().flush();
    stdoutflushTimerPtr->deleteLater();
    stdoutflushTimerPtr = nullptr;
}

void flushQtStdoutTimer_f()
{
    QThread* currentThread(QThread::currentThread());
    //timer requires an event loop
    if (currentThread->eventDispatcher() not_eq nullptr)
    {
        QMutexLocker qOutLockerTmp(&qtStdoutMutexRef_glo());
        if (stdoutflushTimerPtr == nullptr)
        {
            stdoutflushTimerPtr = new QTimer;
            stdoutflushTimerPtr->setSingleShot(true);
            QObject::connect(stdoutflushTimerPtr, &QTimer::timeout, flushQtStdout_f);
            stdoutflushTimerPtr->start(1000);
        }
        else
        {
            stdoutflushTimerPtr->start(1000);
        }
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

QTimer* stderrflushTimerPtr(nullptr);
void flushQtStderr_f()
{
    QMutexLocker qOutLockerTmp(&qtStderrMutexRef_glo());
    qtStderr_f().flush();
    stderrflushTimerPtr->deleteLater();
    stderrflushTimerPtr = nullptr;
}

void flushQtStderrTimer_f()
{
    QThread* currentThread(QThread::currentThread());
    //timer requires an event loop
    if (currentThread->eventDispatcher() not_eq nullptr)
    {
        QMutexLocker qOutLockerTmp(&qtStderrMutexRef_glo());
        if (stderrflushTimerPtr == nullptr)
        {
            stderrflushTimerPtr = new QTimer;
            stderrflushTimerPtr->setSingleShot(true);
            QObject::connect(stderrflushTimerPtr, &QTimer::timeout, flushQtStderr_f);
            stderrflushTimerPtr->start(1000);
        }
        else
        {
            stderrflushTimerPtr->start(1000);
        }
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

QMutex& qtStdoutMutexRef_glo()
{
    static QMutex qStdoutMutex_glo;
    return qStdoutMutex_glo;
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
    return appDirectoryPath_f() + "/" + executableName_f();
}

QString fileTypePath_f(const fileTypes_ec fileType_par_con)
{
    QString resultTmp;
    if (fileType_par_con == fileTypes_ec::empty)
    {
    }
    else
    {
        resultTmp = fileTypeBasePath_f(fileType_par_con) + fileTypeToExtension_f(fileType_par_con);
    }
    return resultTmp;
}

QString fileTypeBasePath_f(const fileTypes_ec fileType_par_con)
{
    QString resultTmp;
    if (fileType_par_con == fileTypes_ec::empty)
    {
    }
    else
    {
        resultTmp = appFilePath_f() + "_" + fileTypeToString_f(fileType_par_con);
    }
    return resultTmp;
}



QString executableName_f()
{
    static QString executableName_sta(QFileInfo(QCoreApplication::applicationFilePath()).fileName());
    return executableName_sta;
}

QMutex& qtStderrMutexRef_glo()
{
    static QMutex qStderrMutex_glo;
    return qStderrMutex_glo;
}
