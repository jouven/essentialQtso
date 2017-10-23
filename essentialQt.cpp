#include "essentialQt.hpp"

QCoreApplication* qtAppRef_ext(nullptr);

int returnValue_ext = 0;

void qtCout_f(const QString &msg_par_con, const bool addEndl_par_con)
{
    static QMutex tmp;
    tmp.lock();
    if (addEndl_par_con)
    {
        qtOutRef_ext() << msg_par_con << endl;
    }
    else
    {
        qtOutRef_ext() << msg_par_con;
    }
    tmp.unlock();
}

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

QTimer* qtCycleRef_ext(nullptr);
