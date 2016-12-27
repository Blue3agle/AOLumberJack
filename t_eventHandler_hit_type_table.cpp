#include "t_eventHandler_hit_type_table.h"

t_eventHandler_hit_type_table::t_eventHandler_hit_type_table(MainWindow *mainWindow)
{
    this->mainWindow = mainWindow;
    this->mainWindow->addModule("Hit type table");
    QObject::connect(mainWindow->logParser, &t_parser::lineParsed
                     , this, t_eventHandler_hit_type_table::handleEvent);

    this->setupPlayField();
    this->mainWindow->addPlayField(playField);

}

void t_eventHandler_hit_type_table::setupPlayField(){

    this->playField = new QMdiSubWindow();
    this->playField->setMinimumSize(300, 100);
    this->playField->setWindowTitle("Hit Type Counter");

    this->hitTable = new QTableWidget(0,5, this->playField);

    this->hitTable->setColumnWidth(0, 100);
    this->hitTable->setColumnWidth(1, 50);
    this->hitTable->setColumnWidth(2, 50);
    this->hitTable->setColumnWidth(3, 50);
    this->hitTable->setColumnWidth(4, 50);
    this->hitTable->setColumnWidth(5, 50);
    this->hitTable->setHorizontalHeaderItem(0, new QTableWidgetItem("Toon"));
    this->hitTable->setHorizontalHeaderItem(1, new QTableWidgetItem("Normal"));
    this->hitTable->setHorizontalHeaderItem(2, new QTableWidgetItem("Nano"));
    this->hitTable->setHorizontalHeaderItem(3, new QTableWidgetItem("Crit"));
    this->hitTable->setHorizontalHeaderItem(4, new QTableWidgetItem("Glance"));
    this->hitTable->setHorizontalHeaderItem(5, new QTableWidgetItem("Miss"));
    this->playField->setWidget(hitTable);

}

void t_eventHandler_hit_type_table::handleEvent(t_logLine *log){
    QString data = "";
    //If it has "with nanobots " remove "with nanobots " and append " Nanobots hit."
    if (log->getData().indexOf(" with nanobots ")>-1)
    {
        data = log->getData().replace(" with nanobots ", "");
        data.append(" Nanobot hit.");
    } else data = log->getData();
    QRegularExpressionMatch match = pattern.match(data);
    if(match.hasMatch()){
        QString source = match.captured("source");
        QString target = match.captured("target");
        int value = match.captured("value").toInt();
        this->aggDamage[source] += value;
        int time = log->getTime();

        if (target == "you")
            target = "You";

        if (this->firstLine == true)
        {
            this->startTime = time;
            this->firstLine = false;
        }


        int offset = time - this->startTime;

        if(!this->graphLines.contains(source)){
            this->addGraph(source);
        }
        this->graphLines[source]->addData(offset, this->aggDamage[source]);
/*
        if(!this->graphLines.contains(target)){
            this->addGraph(target);
        }
        this->graphLines[target]->addData(offset, value * -1);
*/
        this->chart->xAxis->setRangeUpper(offset);
        this->chart->replot();

    }
}
}
