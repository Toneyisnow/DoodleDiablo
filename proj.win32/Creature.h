#ifndef  _CREATURE_H_
#define  _CREATURE_H_

#include "cocos2d.h"
#include "GameObject.h"

using namespace std;

namespace MyTestGame
{

    class Creature : MyTestGame::GameObject
	{
	public:
		Creature();
		virtual ~Creature();

		void SetRoutePoint();


	private:

		vector<Point> routePoints;
	};

}
#endif // _CREATURE_H_

