#include "t_eventHandler_log.h"

t_eventHandler_log::t_eventHandler_log(MainWindow *mainWindow)
{
    this->mainWindow = mainWindow;
    this->mainWindow->addModule("Logviewer");
    QObject::connect(mainWindow->logParser, &t_parser::lineParsed
                     , this, t_eventHandler_log::handleEvent);

    this->setupPlayField();
    this->mainWindow->addPlayField(playField);
}

void t_eventHandler_log::setupPlayField()
{
    this->playField = new QMdiSubWindow();
    this->playField->setMinimumSize(300, 100);
    this->playField->setWindowTitle("Log");

    this->logTable = new QTableWidget(0,4, this->playField);

    this->logTable->setMinimumWidth(this->playField->width());
    this->logTable->setColumnWidth(0, 100);
    this->logTable->setColumnWidth(1, 50);
    this->logTable->setColumnWidth(2, 200);
    this->logTable->setColumnWidth(3, this->playField->width()-360);
    this->playField->setWidget(logTable);

}

void t_eventHandler_log::handleEvent(t_logLine *log)
{
    int row = this->logTable->rowCount();
    if(this->startTime == 0){
        this->startTime = log->getTime();
    }
    int offset = log->getTime() - this->startTime;

    this->logTable->insertRow(row);
    this->logTable->setItem(row, 0, new QTableWidgetItem(QString::number(log->getTime())));
    this->logTable->setItem(row, 1, new QTableWidgetItem(QString::number(offset)));
    this->logTable->setItem(row, 2, new QTableWidgetItem(log->getChannel()));
    this->logTable->setItem(row, 3, new QTableWidgetItem(log->getData()));
}
