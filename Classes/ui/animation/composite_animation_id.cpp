
#include "composite_animation_id.h"

CompositeAnimationId * CompositeAnimationId::create(AnimationGenera g, char* token, AnimationAction a, AnimationFigure f)
{
	CompositeAnimationId * obj = new CompositeAnimationId(g, token, a, f);
	return (CompositeAnimationId *)obj->autorelease();
}

CompositeAnimationId * CompositeAnimationId::clone()
{
	CompositeAnimationId * obj = new CompositeAnimationId(_genera, _token, _action, _figure);
	return (CompositeAnimationId *)obj->autorelease();
}


CompositeAnimationId::CompositeAnimationId(AnimationGenera g, char* token, AnimationAction a, AnimationFigure f)
{
	this->_genera = g;
	this->_token = token;
	this->_figure = f;
	this->_action = a;
}

CompositeAnimationId::~CompositeAnimationId()
{

}

AnimationGenera CompositeAnimationId::getGenera()
{
	return this->_genera;
}
AnimationFigure CompositeAnimationId::getFigure()
{
	return this->_figure;
}
AnimationAction CompositeAnimationId::getAction()
{
	return this->_action;
}

char* CompositeAnimationId::getToken()
{
	return this->_token; 
}

std::string CompositeAnimationId::toString()
{
	char * key = new char[255];
	sprintf(key, "%s%s%s", _token, AnimationActionStrings[_action], AnimationFigureStrings[_figure]);

	std::string str = key;
	delete(key);

	return str;
}

std::string CompositeAnimationId::generateKey()
{
	char key[7];
	sprintf(key, "%s%d%d", _token, _action, _figure);
	std::string str = key;
	
	return str;
}