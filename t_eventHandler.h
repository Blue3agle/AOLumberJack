#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <QObject>
#include <QString>
#include <QMdiSubWindow>

#include "t_logLine.h"

class t_eventHandler : public QObject
{
    Q_OBJECT
public:
    explicit t_eventHandler(QObject *parent = 0);

private:

protected:

signals:

public slots:
    virtual void handleEvent(t_logLine *log) = 0;
};

#endif // EVENTHANDLER_H
