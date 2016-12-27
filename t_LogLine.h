#ifndef LOGLINE_H
#define LOGLINE_H

#include <QString>

class t_logLine
{
public:
    t_logLine(int timeStamp, QString Channel, QString data);

    int getTime();
    QString getChannel();
    QString getData();

private:
    int timeStamp;
    QString channel;
    QString data;
};

#endif // LOGLINE_H
