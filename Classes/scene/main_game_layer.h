#ifndef  _MAINGAMELAYER_H_
#define  _MAINGAMELAYER_H_

#include "cocos2d.h"

using namespace std;
USING_NS_CC;

#include "ui\animation\dcc_decoder.h"
#include "ui\object\character.h"
#include "ui\base\palette.h"

namespace DoodleDiablo
{
	namespace Scenes
	{
		class MainGameLayer : public Layer
		{
		public:
			
			// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
			virtual bool init();

			// implement the "static create()" method manually
			CREATE_FUNC(MainGameLayer);


		private:

			Sprite* map;
			Sprite* player;
			Sprite* controlTarget;

			void loadStage(int stageId, int indexId);




			void b1Callback(cocos2d::Ref* pSender);
			void b2Callback(cocos2d::Ref* pSender);
			void b3Callback(cocos2d::Ref* pSender);
			void b4Callback(cocos2d::Ref* pSender);
			void b5Callback(cocos2d::Ref* pSender);

			void moveMap(int direction);


		};

	}
}
#endif // _MAINGAMELAYER_H_

