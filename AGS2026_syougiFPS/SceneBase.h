#pragma once

class SceneBase {
public:
    virtual ~SceneBase() = default;
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual SceneBase* NextScene() = 0; // nullptr = 継続、別のポインタ = 遷移
};