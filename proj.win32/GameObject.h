#ifndef  _GAME_OBJECT_H_
#define  _GAME_OBJECT_H_

#include "cocos2d.h"

namespace MyTestGame
{
	class GameObject : private cocos2d::Ref
	{
	public:
		GameObject();
		virtual ~GameObject();


	};
}

#endif // _GAME_OBJECT_H_

