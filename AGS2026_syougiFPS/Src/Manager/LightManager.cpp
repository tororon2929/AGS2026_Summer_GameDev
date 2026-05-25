#include "DxLib.h" // DXライブラリ等を使う場合はここを有効に
#include "LightManager.h"
LightManager::LightManager() {
    // 盤面が暗いとのことなので、初期値をかなり明るめに設定します
    brightness = 2.0f;        // 全体倍率を少し底上げ
    ambientIntensity = 0.6f;  // 影になる部分も明るく
    diffuseIntensity = 1.1f;  // 直接当たる光を強く

    // 真上から少し手前に向けて照らす（盤面が綺麗に見えます）
    direction = Vector3(0.0f, -5.5f, 0.5f).normalize();
}

void LightManager::setBrightness(float b) { brightness = b; }
void LightManager::setAmbient(float a) { ambientIntensity = a; }
void LightManager::setDirection(float x, float y, float z) { direction = Vector3(x, y, z).normalize(); }

void LightManager::applyLighting() {
    float fAmb = ambientIntensity * brightness;
    float fDif = diffuseIntensity * brightness;

    // DXライブラリのライト設定を更新
    // 全体を照らす環境光（Ambient）
    SetLightAmbColor(GetColorF(fAmb, fAmb, fAmb, 1.0f));
    // 直接当たる光（Diffuse）
    SetLightDifColor(GetColorF(fDif, fDif, fDif, 1.0f));
    // 光の向き
    SetLightDirection(VGet(direction.x, direction.y, direction.z));

}