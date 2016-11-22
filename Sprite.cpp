#include "Sprite.h"

Sprite::Sprite() {}

Sprite::Sprite(Position pos, SDL_Rect destination, SDL_Texture* tex)
{
	this->pos = pos;
	destinationRenderTarget = destination;	//XYWH
	Source = nullRect;
	texture = tex;
}

void Sprite::UpdateRect()
{
	SDL_Rect d = { (int)pos.getX(),(int)pos.getY(),201,160 };
	destinationRenderTarget = d;
}

Sprite::~Sprite()
{

}
