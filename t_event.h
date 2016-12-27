#ifndef EVENT_H
#define EVENT_H

#include <QString>

class t_event
{
public:
    t_event();
protected:
    int timestamp;
    QString channel;
    QString *source;
    QString *target;

};

#endif // EVENT_H
