#pragma once

namespace trl {
    // ジャンプ用の関数
    void PlayerJamp(float& J,tnl::Vector3& posA, float& Y);
    // 壁の判定
    void WallCllision(tnl::Vector3& pos);
    
}