#include "MainWindow.h"
#include "ui_mainwindow.h"

#include "t_eventhandler_log.h"
#include "t_eventHandler_damage_given.h"
#include "t_eventHandler_damage_given_agg.h"
#include "t_eventHandler_damage_taken.h"
#include "t_eventHandler_damage_taken_agg.h"
#include "t_eventHandler_hit_type_table.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setup();
    this->run();
}

void MainWindow::setup()
{
    this->entities = new t_entityList();

//    this->logParser = new t_parser("C:/Users/regis/AppData/Local/Funcom/Anarchy Online/cd94a273/Anarchy Online Beta/Prefs/xBlueEagle/Char586965293/Chat/Windows/Window7/Log.txt");
    this->logParser = new t_parser("H:/Documents/QT/AOLumberJack/data/BigLog.txt");
    /*this->handlerList.append(new t_eventHandler_damage_given(this));
    this->handlerList.append(new t_eventHandler_damage_given_agg(this));
    this->handlerList.append(new t_eventHandler_damage_taken(this));
    this->handlerList.append(new t_eventHandler_damage_taken_agg(this));*/
    this->handlerList.append(new t_eventHandler_log(this));
    this->handlerList.append(new t_eventHandler_hit_type_table(this));


    ui->playground->tileSubWindows();
}

void MainWindow::run()
{

}

void MainWindow::addModule(QString name)
{
    ui->moduleList->addItem(name);
}

void MainWindow::addPlayField(QMdiSubWindow *window)
{
    this->ui->playground->addSubWindow(window);
}

MainWindow::~MainWindow()
{
    delete ui;
}
