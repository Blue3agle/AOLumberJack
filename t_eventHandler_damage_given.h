#ifndef EVENTHANDLER_DAMAGE_GIVEN_H
#define EVENTHANDLER_DAMAGE_GIVEN_H

#include <QObject>
#include <QString>

#include "t_logLine.h"

//Libraries needed for playfield
#include <QMdiSubWindow>
#include "qcustomplot.h"

//Libraries needed for handler
#include <QRegularExpression>
#include <QRegularExpressionMatch>

#include "MainWindow.h"

class t_eventHandler_damage_given : public QObject
{
    Q_OBJECT

public:
    explicit t_eventHandler_damage_given(MainWindow *mainWindow);
private:
    MainWindow *mainWindow;
    QMdiSubWindow *playField;

    QRegularExpression pattern;


    bool firstLine = true;
    int startTime = 0;

    QCustomPlot *chart;
    QMap<QString, QCPGraph*> graphLines;
    QMap<QString, QVector<double> >graphDataX;
    QMap<QString, QVector<double> >graphDataY;


    void setupPlayField();
    void addGraph(QString);

public slots:
    void handleEvent(t_logLine *log);
    void graphSelectionChanged();

};

#endif // EVENTHANDLER_DAMAGE_H
