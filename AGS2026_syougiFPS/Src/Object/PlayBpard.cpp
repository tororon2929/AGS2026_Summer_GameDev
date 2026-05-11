#include "PlayBpard.h"
#include "../Manager/ResourceManager.h"
#include <DxLib.h>

PlayBpard::PlayBpard() : m_handle(-1) {}
PlayBpard::~PlayBpard() {}

void PlayBpard::Initialize() {
    // 既にマネージャーが作られているので安全に呼べる
    const Resource& res = ResourceManager::GetInstance().Load(ResourceManager::SRC::PlayBpard);
    m_handle = res.handleId_;

   
}

void PlayBpard::Draw() {
    if (m_handle != -1) {
        // 座標(0,0,0)に配置
        MV1SetPosition(m_handle, VGet(0.0f, 0.0f, 0.0f));
        // スケール調整（大きすぎたら 1.0f にしてください）
        MV1SetScale(m_handle, VGet(10.0f, 10.0f, 10.0f));

        MV1DrawModel(m_handle);
    }
}