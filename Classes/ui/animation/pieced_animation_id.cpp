#include "pieced_animation_id.h"

PiecedAnimationId * PiecedAnimationId::create(CompositeAnimationId * com, AnimationFigure f, AnimationPiece p, AnimationLevel l)
{
	PiecedAnimationId * obj = new PiecedAnimationId(com, f, p, l);

	return (PiecedAnimationId *)obj->autorelease();
}

PiecedAnimationId * PiecedAnimationId::create(PiecedMotionId *p, AnimationLevel l)
{
	PiecedAnimationId * obj = new PiecedAnimationId(p, l);

	return (PiecedAnimationId *)obj->autorelease();
}


PiecedAnimationId::PiecedAnimationId(CompositeAnimationId * com, AnimationFigure f, AnimationPiece p, AnimationLevel l)
{
	this->_compositeId = com;
	this->_piece = p;
	this->_figure = f;
	this->_level = l;
}

PiecedAnimationId::PiecedAnimationId(PiecedMotionId * p, AnimationLevel l)
{
	this->_compositeId = p->getCompositeId();
	this->_piece = p->getPiece();
	this->_figure = p->getFigure();
	this->_level = l;
}

PiecedAnimationId::~PiecedAnimationId()
{

}

std::string PiecedAnimationId::getFullPieceLevelStrings(AnimationLevelHD hd, AnimationLevelBody body, AnimationLevelRH rh, AnimationLevelLH lh, AnimationLevelSH sh)
{
	char result[13];
	sprintf(result, "%d%d%d%d%d", hd, body, rh, lh, sh);

	return result;
}

AnimationPiece PiecedAnimationId::getPiece()
{
	return this->_piece;
}

AnimationFigure PiecedAnimationId::getFigure()
{
	return this->_figure;
}

AnimationLevel PiecedAnimationId::getLevel()
{
	return this->_level;
}

CompositeAnimationId * PiecedAnimationId::getCompositeId()
{
	return this->_compositeId;
}

/*
Vector<PiecedAnimationId *>* PiecedAnimationId::retrieveAllByPiecedMotion(PiecedMotionId *pMotion)
{
	Vector<PiecedAnimationId *>* result = new Vector<PiecedAnimationId *>();
	AnimationLevel * levels = PiecedAnimationId::getAllPieceLevels(pMotion->getPiece());
	
	for (int i = 0; i < 1; i++)
	{
		result->insert(i, PiecedAnimationId::create(pMotion, levels[i]));
	}

	return result;
}
*/

std::string PiecedAnimationId::toString()
{
	char key[255];
	sprintf(key, "%s%s%s%s%s", _compositeId->getToken(), AnimationPieceStrings[_piece], AnimationLevelStrings[_level], AnimationActionStrings[_compositeId->getAction()], AnimationFigureStrings[_figure]);
	return key;
}

std::string PiecedAnimationId::generateKey()
{
	char key[10];
	sprintf(key, "%s%d%d", _compositeId->generateKey(), _piece, _level);
	return key;
}

PiecedAnimationId * PiecedAnimationId::clone()
{
	PiecedAnimationId * obj = PiecedAnimationId::create(_compositeId->clone(), _figure, _piece, _level);
	return (PiecedAnimationId *)obj->autorelease();
}


/*
AnimationLevel* PiecedAnimationId::getAllPieceLevels(AnimationPiece piece)
{
	switch (piece)
	{
		case AnimationPiece::Piece_HD:
			return new AnimationLevel[3] {AnimationLevel::AnimationLevel_HLM, AnimationLevel::AnimationLevel_MSK, AnimationLevel::AnimationLevel_HVY};
		case AnimationPiece::Piece_TR:
			return new AnimationLevel[1] {AnimationLevel::AnimationLevel_HVY};
		case AnimationPiece::Piece_LG:
			return new AnimationLevel[1] {AnimationLevel::AnimationLevel_HVY};
		case AnimationPiece::Piece_RA:
			return new AnimationLevel[1] {AnimationLevel::AnimationLevel_HVY};
		case AnimationPiece::Piece_LA:
			return new AnimationLevel[1] {AnimationLevel::AnimationLevel_HVY};
		case AnimationPiece::Piece_RH:
			return new AnimationLevel[1] {AnimationLevel::AnimationLevel_CLM};
		case AnimationPiece::Piece_LH:
			return new AnimationLevel[1] {AnimationLevel::AnimationLevel_HVY};
		case AnimationPiece::Piece_SH:
			return new AnimationLevel[1] {AnimationLevel::AnimationLevel_BSH};
		default:
			return new AnimationLevel[1] {AnimationLevel::AnimationLevel_HVY};
	}

}

*/