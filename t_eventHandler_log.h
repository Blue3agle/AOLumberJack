#ifndef EVENTHANDLER_LOG_H
#define EVENTHANDLER_LOG_H

#include <QObject>

//Libraries needed for playfield
#include <QTableWidget>


#include "t_eventHandler.h"
#include "MainWindow.h"

class t_eventHandler_log : public QObject
{
    Q_OBJECT

public:
    t_eventHandler_log(MainWindow *mainWindow);
private:
    MainWindow *mainWindow;
    QMdiSubWindow *playField;
    QTableWidget *logTable;

    int startTime = 0;

    void setupPlayField();

public slots:
    void handleEvent(t_logLine *log);
};

#endif // EVENTHANDLER_LOG_H
