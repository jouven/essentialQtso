//reusable header
#ifndef ESSENTIALQTSO_ESSENTIAL_HPP
#define ESSENTIALQTSO_ESSENTIAL_HPP

#include <QCoreApplication>
#include <QTextStream>
#include <QMutex>
#include <QMutexLocker>
#include <QTimer>

#define QOUT_TS(X) {QMutexLocker qOutLockerTmp(&qtOutMutexRef_glo()); qtOutRef_ext() << X;}

//Connect the stdout to my qout textstream, not thread-safe
extern QTextStream &qtOutRef_ext();
//same as above (and somewhat more limited), but thread-safe
extern void qtCout_f(const QString& msg_par_con, const bool addEndl_par_con = false);
//Connect the stderr to my qerr textstream
extern QTextStream& qtErrRef_ext();
//so any QObject subclass can reference a parent
extern QCoreApplication* qtAppRef_ext;

extern int returnValue_ext;
//necessary for the macro use
extern QMutex& qtOutMutexRef_glo();

extern QTimer* qtCycleRef_ext;

#endif // ESSENTIALQTSO_ESSENTIAL_HPP
