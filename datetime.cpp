#include "datetime.hpp"

#include <QString>

#include <cstdlib>

QString formatedTime_f(const int_fast64_t milliseconds_par_con)
{
    QString resultTmp("00:00");
    while (milliseconds_par_con not_eq 0)
    {
        QString millisecondsStrTmp(QString::number(milliseconds_par_con));
        QString secondsStrTmp;
        QString minutesStrTmp;
        QString hoursStrTmp;
        QString daysStrTmp;

        int_fast64_t secondsTmp(0);
        if (milliseconds_par_con < 1000)
        {
            resultTmp = millisecondsStrTmp;
            break;
        }
        else
        {
            resultTmp.clear();
            millisecondsStrTmp = millisecondsStrTmp.mid(millisecondsStrTmp.size() - 3);
            secondsTmp = milliseconds_par_con / 1000;
        }

        int_fast64_t quotTmp(0);
        if (secondsTmp > 0)
        {
            auto divisionSecondsResultTmp(std::lldiv(secondsTmp, 60));
            secondsStrTmp = QString::number(divisionSecondsResultTmp.rem);
            quotTmp = divisionSecondsResultTmp.quot;
            if (secondsStrTmp.size() == 1)
            {
                secondsStrTmp.prepend('0');
            }
        }

        if (quotTmp > 0)
        {
            auto divisionMinutesResultTmp(std::lldiv(quotTmp, 60));
            minutesStrTmp = QString::number(divisionMinutesResultTmp.rem);
            quotTmp = divisionMinutesResultTmp.quot;
            if (minutesStrTmp.size() == 1)
            {
                minutesStrTmp.prepend('0');
            }
        }

        if (quotTmp > 0)
        {
            auto divisionHoursResultTmp(std::lldiv(quotTmp, 24));
            hoursStrTmp = QString::number(divisionHoursResultTmp.rem);
            if (divisionHoursResultTmp.quot > 0)
            {
                daysStrTmp = QString::number(divisionHoursResultTmp.quot);
            }
        }

        //23 23:24:00.000
        if (millisecondsStrTmp not_eq "000")
        {
            resultTmp = millisecondsStrTmp;
            if (not secondsStrTmp.isEmpty())
            {
                resultTmp.prepend('.');
            }
        }
        if (not secondsStrTmp.isEmpty())
        {
            resultTmp.prepend(secondsStrTmp);
        }
        else
        {
            resultTmp.prepend("00");
        }

        if (not minutesStrTmp.isEmpty())
        {
            resultTmp.prepend(minutesStrTmp + ":");
        }
        else
        {
            resultTmp.prepend("00:");
        }

        if (not hoursStrTmp.isEmpty())
        {
            resultTmp.prepend(hoursStrTmp + ":");
        }

        if (not daysStrTmp.isEmpty())
        {
            resultTmp.prepend(daysStrTmp + "d ");
        }

        break;
    }
    return resultTmp;
}

