#pragma once
#include <memory>
#include <DxLib.h>
#include "Collider.h"
#include "Quaternion.h"


class Transform
{
public:

	Transform(void);
	Transform(int model);

	~Transform(void);

	int modelId;

	VECTOR scl;

	VECTOR rot;

	VECTOR pos;
	VECTOR localPos;

	MATRIX matScl;
	MATRIX matRot;
	MATRIX matPos;
};

