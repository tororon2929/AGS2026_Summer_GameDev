#include "Stage.h"
#include "../Manager/ResourceManager.h"

Stage::Stage()
{
}

Stage::~Stage()
{
}

void Stage::Init()
{
	modelId_ = ResourceManager::GetInstance().LoadModelDuplicate(
		ResourceManager::SRC::PlayBpard);

	MV1SetPosition(modelId_, VGet(0.0f, 0.0f, 0.0f));
}

void Stage::Draw()
{
	if (modelId_ != -1)
	{
		MV1DrawModel(modelId_);
	}
}

void Stage::Release()
{
	if (modelId_ != -1)
	{
		MV1DeleteModel(modelId_);
		modelId_ = -1;
	}
}