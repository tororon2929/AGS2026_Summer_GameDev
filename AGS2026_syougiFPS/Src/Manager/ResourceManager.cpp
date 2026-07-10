#include <DxLib.h>
#include "../Application.h"
#include "Resource.h"
#include "ResourceManager.h"

ResourceManager* ResourceManager::instance_ = nullptr;

void ResourceManager::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new ResourceManager();
	}
	instance_->Init();
}

ResourceManager& ResourceManager::GetInstance(void)
{
	return *instance_;
}

void ResourceManager::Init(void)
{

	// 推奨しませんが、どうしても使いたい方は
	using RES = Resource;
	using RES_T = RES::TYPE;
	static std::string PATH_IMG = Application::PATH_IMAGE;
	static std::string PATH_MDL = Application::PATH_MODEL;
	static std::string PATH_EFF = Application::PATH_EFFECT;
	static std::string PATH_ENM = Application::PATH_ENEMY;

	Resource* res;

	// 盤面モデル
	res = new RES(RES_T::MODEL, PATH_MDL + "PlayBpard.mv1");
	resourcesMap_.emplace(SRC::PlayBpard, res);
	// 盤面モデル
	res = new RES(RES_T::MODEL, PATH_MDL + "Ou.mv1");
	resourcesMap_.emplace(SRC::Ou, res);

	res = new RES(RES_T::MODEL, PATH_MDL + "Ou.mv1");
	resourcesMap_.emplace(SRC::Gyoku, res);

	res = new RES(RES_T::MODEL, PATH_MDL + "Fu.mv1");
	resourcesMap_.emplace(SRC::Fu, res);

	res = new RES(RES_T::MODEL, PATH_MDL + "Hisya.mv1");
	resourcesMap_.emplace(SRC::Hisha, res);

	res = new RES(RES_T::MODEL, PATH_MDL + "Kaku.mv1");
	resourcesMap_.emplace(SRC::Kaku, res);

	res = new RES(RES_T::MODEL, PATH_MDL + "Kin.mv1");
	resourcesMap_.emplace(SRC::Kin, res);

	res = new RES(RES_T::MODEL, PATH_MDL + "Gin.mv1");
	resourcesMap_.emplace(SRC::Gin, res);


	res = new RES(RES_T::IMG, PATH_IMG + "Title.png");
	resourcesMap_.emplace(SRC::Title, res);

	res = new RES(RES_T::IMG, PATH_IMG + "Myturn.png");
	resourcesMap_.emplace(SRC::Myturn, res);

	res = new RES(RES_T::IMG, PATH_IMG + "Enemyturn.png");
	resourcesMap_.emplace(SRC::Enemyturn, res);

	res = new RES(RES_T::IMG, PATH_IMG + "Win.png");
	resourcesMap_.emplace(SRC::Win, res);

	res = new RES(RES_T::IMG, PATH_IMG + "Lose.png");
	resourcesMap_.emplace(SRC::Lose, res);

	res = new RES(RES_T::MODEL, PATH_ENM + "Fu_Enemy.mv1");
	resourcesMap_.emplace(SRC::ENEMY_FU, res);


}

void ResourceManager::Release(void)
{
	for (auto& p : loadedMap_)
	{
		p.second.Release();
	}

	loadedMap_.clear();
}

void ResourceManager::Destroy(void)
{
	Release();
	for (auto& res : resourcesMap_)
	{
		res.second->Release();
		delete res.second;
	}
	resourcesMap_.clear();
	delete instance_;
}

const Resource& ResourceManager::Load(SRC src)
{
	Resource& res = _Load(src);
	if (res.type_ == Resource::TYPE::NONE)
	{
		return dummy_;
	}
	return res;
}

int ResourceManager::LoadModelDuplicate(SRC src)
{
	Resource& res = _Load(src);
	if (res.type_ == Resource::TYPE::NONE)
	{
		return -1;
	}

	int duId = MV1DuplicateModel(res.handleId_);
	res.duplicateModelIds_.push_back(duId);

	return duId;
}

ResourceManager::ResourceManager(void)
{
}

Resource& ResourceManager::_Load(SRC src)
{

	// 1. まずリソースがそもそも登録されているかチェック
	const auto& rPair = resourcesMap_.find(src);
	if (rPair == resourcesMap_.end())
	{
		// 登録されていない場合はダミーを返す
		return dummy_;
	}

	// 2. すでにロード済みかチェック（loadedMap_ から探す）
	const auto& lPair = loadedMap_.find(src);
	if (lPair != loadedMap_.end())
	{
		// すでにロードされていれば、登録されているリソースをそのまま返す
		return *rPair->second;
	}

	// 3. まだロードされていなければ、ここで実際に LoadGraph 等を呼ぶ
	rPair->second->Load();

	// 4. ロード済みマップに登録する
	loadedMap_.emplace(src, *rPair->second);

	return *rPair->second;
}
