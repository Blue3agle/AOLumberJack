#ifndef ENTITY_H
#define ENTITY_H


#include <QString>
#include <QLinkedList>
#include <QMap>
#include <QLineSeries>

QT_CHARTS_USE_NAMESPACE

#include "t_event.h"

class t_entity
{
public:
    t_entity();

private:
    QString name;
    t_entity *owner;
    QLinkedList<t_event*> EventList;

};

#endif // ENTITY_H
