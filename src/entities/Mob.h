#ifndef MOB_H
#define MOB_H
#include <entities/Entity.h>


class Mob : public Entity
{
	// Inherited via Entity
	virtual void update() override;
};
#endif // !NPCENTITY_H
