#ifndef T_EVENTHANDLER_HIT_TYPE_TABLE_H
#define T_EVENTHANDLER_HIT_TYPE_TABLE_H

#include <QObject>

//Libraries needed for playfield
#include <QMdiSubWindow>
#include <QTableWidget>

//Libraries needed for handler
#include <QRegularExpression>
#include <QRegularExpressionMatch>

#include "MainWindow.h"

class t_eventHandler_hit_type_table : public QObject
{
    Q_OBJECT
public:
    explicit t_eventHandler_hit_type_table(MainWindow *mainWindow);

private:
    MainWindow *mainWindow;
    QMdiSubWindow *playField;

    QRegularExpression pattern;

    QTableWidget *hitTable;

    void setupPlayField();
signals:

public slots:
    void handleEvent(t_logLine *log);

};

#endif // T_EVENTHANDLER_HIT_TYPE_TABLE_H
