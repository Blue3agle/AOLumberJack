#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//REMOVE below statement to remove debug messages!
#define DEBUGMESSAGES

#include <QMainWindow>
#include <QMdiSubWindow>

#include "t_parser.h"
#include "t_entityList.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setup();
    void run();
    void addModule(QString name);
    void addPlayField(QMdiSubWindow *window);


    t_parser *logParser;

    t_entityList *entities;
    QList<QObject *> handlerList;

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
