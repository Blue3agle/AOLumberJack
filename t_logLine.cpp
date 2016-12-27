#include "t_logLine.h"

t_logLine::t_logLine(int timeStamp, QString channel, QString data)
{
    this->timeStamp = timeStamp;
    this->channel = channel;
    this->data = data;
}

int t_logLine::getTime(){
    return this->timeStamp;
}

QString t_logLine::getChannel(){
    return this->channel;
}

QString t_logLine::getData(){
    return this->data;
}
