#pragma once
auto& titleRes = ResourceManager::GetInstance().Load(ResourceManager::SRC::Title);
titleGraphHandle_ = titleRes.handleId_;

boardModelHandle_ = ResourceManager::GetInstance().LoadModelDuplicate(ResourceManager::SRC::PlayBpard);