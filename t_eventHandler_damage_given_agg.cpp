#include "t_eventHandler_damage_given_agg.h"

t_eventHandler_damage_given_agg::t_eventHandler_damage_given_agg(MainWindow *mainWindow)
{
    this->mainWindow = mainWindow;
    this->mainWindow->addModule("AggDamageGivenGraph");

    this->setupPlayField();
    this->mainWindow->addPlayField(playField);

    //(.+) hit (.+) for (\d+) points of (\w+) damage\. ?(Critical|Glancing|Nanobots)?
    this->pattern.setPattern("(?<source>.+?) hit (?<target>.+) for (?<value>\\d+) points of (?<type>.+?) damage.(?<hitType> Critical| Glancing])?");

    QObject::connect(mainWindow->logParser, &t_parser::lineParsed
                     , this, t_eventHandler_damage_given_agg::handleEvent);

    QObject::connect(this->chart, &QCustomPlot::selectionChangedByUser
                     , this, t_eventHandler_damage_given_agg::graphSelectionChanged);
}

void t_eventHandler_damage_given_agg::setupPlayField()
{
    this->playField = new QMdiSubWindow();
    this->playField->setMinimumSize(400, 200);
    this->playField->setWindowTitle("Damage given aggregate");
    this->chart = new QCustomPlot();

    this->chart->xAxis->grid()->setSubGridVisible(true);
    this->chart->xAxis->setTicks(true);
    this->chart->xAxis->setTickLength(60);
    this->chart->xAxis->setSubTickLength(10);
    QSharedPointer<QCPAxisTickerFixed> intTicker(new QCPAxisTickerFixed);
    intTicker->setTickStep(1.0);
    intTicker->setScaleStrategy(QCPAxisTickerFixed::ssMultiples);
    this->chart->xAxis->setTicker(intTicker);

    this->chart->yAxis->grid()->setSubGridVisible(true);
    this->chart->yAxis->setRangeUpper(20000);
    this->chart->yAxis->setScaleType(QCPAxis::stLogarithmic);
    this->chart->yAxis->setNumberFormat("eb"); // e = exponential, b = beautiful decimal powers
    this->chart->yAxis->setNumberPrecision(0); // makes sure "1*10^4" is displayed only as "10^4"
    QSharedPointer<QCPAxisTickerLog> logTicker(new QCPAxisTickerLog);
    this->chart->yAxis->setTicker(logTicker);

    this->chart->legend->setVisible(true);
    this->chart->legend->setFont(QFont("Verdana",7));
    this->chart->legend->setIconSize(12,8);
    this->chart->legend->setAntialiased(true);
    this->chart->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft|Qt::AlignTop);

    this->chart->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables | QCP::iSelectLegend);

    this->playField->setWidget(this->chart);
}

void t_eventHandler_damage_given_agg::handleEvent(t_logLine *log)
{
    QString data = "";
    //If it has "with nanobots " remove "with nanobots " and append " Nanobots hit."
    if (log->getData().indexOf(" with nanobots ")>-1)
    {
        data = log->getData().replace(" with nanobots ", "");
        data.append(" Nanobot hit.");
    } else data = log->getData();
    this->pattern.setPattern("(?<source>.+?) hit (?<target>.+) for (?<value>\\d+) points of (?<type>.+?) damage.(?<hitType> Critical| Glancing |Nanobot])?");
    QRegularExpressionMatch match = pattern.match(data);
    if(match.hasMatch()){
        QString source = match.captured("source");
        QString hitType = match.captured("hitType");
        switch(hitType.trimmed()){
            case "Critical":
                this->AddCrit(source);
                break;
            case "Glancing":
                this->AddGlance(source);
                break;
            case "Nanobot":
                this->AddNanobot(source);
                break;
            else:
                this->addNormal(source);
        }
    }
}

void t_eventHandler_damage_given_agg::addGraph(QString entity)
{
    //Add graph for t_entity
    this->graphLines[entity] = chart->addGraph();
    this->graphLines[entity]->setName(entity);
    this->graphLines[entity]->addToLegend();
    QPen Pen;
    Pen.setColor(QColor(rand()%230, rand()%230, rand()%230));
    this->graphLines[entity]->setPen(Pen);

}

void t_eventHandler_damage_given_agg::graphSelectionChanged()
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
