#include "pieced_motion_id.h"

PiecedMotionId * PiecedMotionId::create(CompositeAnimationId * compositeId, AnimationPiece p, AnimationFigure f)
{
	PiecedMotionId * obj = new PiecedMotionId(compositeId, p, f);

	return (PiecedMotionId *)obj->autorelease();
}

PiecedMotionId::PiecedMotionId(CompositeAnimationId * compositeId, AnimationPiece p, AnimationFigure f)
{
	this->_compositeId = compositeId;
	this->_piece = p;
	this->_figure = f;

}
PiecedMotionId::~PiecedMotionId()
{

}

AnimationGenera PiecedMotionId::getGenera()
{
	return this->_compositeId->getGenera();
}

AnimationPiece PiecedMotionId::getPiece()
{
	return this->_piece;
}

AnimationFigure PiecedMotionId::getFigure()
{
	return this->_figure;
}

AnimationAction PiecedMotionId::getAction()
{
	return this->_compositeId->getAction();
}

CompositeAnimationId * PiecedMotionId::getCompositeId()
{
	return this->_compositeId;
}

std::string PiecedMotionId::toString()
{
	char key[255];
	sprintf(key, "%s%s", this->_compositeId->toString(), AnimationPieceStrings[getPiece()]);
	return key;
}

std::string PiecedMotionId::generateKey()
{
	char key[20];
	sprintf(key, "%s%d", this->_compositeId->generateKey(), getPiece());
	return key;
}

PiecedMotionId * PiecedMotionId::clone()
{
	PiecedMotionId * obj = PiecedMotionId::create(_compositeId->clone(), _piece, _figure);
	return (PiecedMotionId *)obj->autorelease();
}
