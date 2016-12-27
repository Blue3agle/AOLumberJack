#include "t_eventHandler_damage_taken.h"

t_eventHandler_damage_taken::t_eventHandler_damage_taken(MainWindow *mainWindow)
{
    this->mainWindow = mainWindow;
    this->mainWindow->addModule("DamageTakenGraph");

    this->setupPlayField();
    this->mainWindow->addPlayField(playField);

    //(.+) hit (.+) for (\d+) points of (\w+) damage\. ?(Critical|Glancing|Nanobots)?
    this->pattern.setPattern("(?<source>.+?) hit (?<target>.+) for (?<value>\\d+) points of (?<type>.+?) damage.(?<hitType> Critical| Glancing])?");

    QObject::connect(mainWindow->logParser, &t_parser::lineParsed
                     , this, t_eventHandler_damage_taken::handleEvent);

    QObject::connect(this->chart, &QCustomPlot::selectionChangedByUser
                     , this, t_eventHandler_damage_taken::graphSelectionChanged);
}

void t_eventHandler_damage_taken::setupPlayField()
{
    this->playField = new QMdiSubWindow();
    this->playField->setMinimumSize(400, 200);
    this->playField->setWindowTitle("Damage taken");
    this->chart = new QCustomPlot();
    this->chart->yAxis->setRangeUpper(20000);
    this->chart->yAxis->grid()->setSubGridVisible(true);


    this->chart->legend->setVisible(true);
    this->chart->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables | QCP::iSelectLegend);

    this->chart->legend->setFont(QFont("Verdana",7));
    this->chart->legend->setIconSize(12,8);
    this->chart->legend->setAntialiased(true);
    this->chart->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft|Qt::AlignTop);

    this->playField->setWidget(this->chart);
}

void t_eventHandler_damage_taken::handleEvent(t_logLine *log)
{
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
        int time = log->getTime();

        if (target == "you")
            target = "You";

        if (this->firstLine == true)
        {
            this->startTime = time;
            this->firstLine = false;
        }

        int offset = time - this->startTime;

        if(!this->graphLines.contains(target)){
            this->addGraph(target);
        }
        this->graphLines[target]->addData(offset, value);

        this->chart->xAxis->setRangeUpper(offset);
        this->chart->replot();

    }
}

void t_eventHandler_damage_taken::addGraph(QString entity)
{
    //Add graph for t_entity
    this->graphLines[entity] = chart->addGraph();
    this->graphLines[entity]->setName(entity);
    this->graphLines[entity]->addToLegend();
    QPen Pen;
    Pen.setColor(QColor(rand()%230, rand()%230, rand()%230));
    this->graphLines[entity]->setPen(Pen);

}

void t_eventHandler_damage_taken::graphSelectionChanged()
{
    for (int i=0; i<this->chart->graphCount(); ++i)
    {
      QCPGraph *graph = this->chart->graph(i);
      QCPPlottableLegendItem *item = this->chart->legend->itemWithPlottable(graph);
      if (item->selected() || graph->selected())
      {
        item->setSelected(true);
        graph->setSelection(QCPDataSelection(graph->data()->dataRange()));
      }
    }
}
