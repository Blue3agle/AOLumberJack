#ifndef T_ENTITYLIST_H
#define T_ENTITYLIST_H

#include <QString>
#include <QMap>

#include "t_entity.h"
class t_entityList
{
public:
    t_entityList();
    t_entity* getEntity(QString);
private:
    QMap <QString, t_entity*>entities;
};

#endif // T_ENTITYLIST_H
