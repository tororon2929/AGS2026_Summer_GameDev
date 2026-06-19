#include "Bullet.h"

Bullet::Bullet(VECTOR pos, VECTOR dir)
{
	pos_ = pos;
	dir_ = dir;

}

void Bullet::Update() {
	pos_ = VAdd(pos_, VScale(dir_, 3.0f));
	life_--;
}

void Bullet::Draw() {
	DrawSphere3D(pos_, 2.0f, 10, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
}
