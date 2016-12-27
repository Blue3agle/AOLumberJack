#include "t_entityList.h"

t_entityList::t_entityList()
{

}

t_entity* t_entityList::getEntity(QString name)
{
    if (!this->entities.contains(name))
    {
        this->entities.insert(name, new t_entity);
    }
    return this->entities[name];
}
