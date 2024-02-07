#include "../dxlib_ext/dxlib_ext.h"
#include "trl_player_command.h"

namespace trl {

    //----------------------------------------------------�W�����v�R�}���h---------------------------------------------------------------
    // J = �W�����v��
	// posA = �v���C���[�̃|�C���^
    void PlayerJamp(float& J,tnl::Vector3& posA, float& Y) {
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE)) {
			J = 15.0f;
		}
		posA.y += J;
		if (posA.y <= 0) {
			posA.y = 0;
			J = 0;
		}
		else {
			J -= 0.98f;
		}
		// �n�ʂ�艺�ɍs���Ȃ��悤�ɂ���
		if (posA.y < Y) {
			posA.y = Y;
		}
    }


	//--------------------------------------------�ǂƃv���C���[�̓����蔻��݂����Ȋ֐�-----------------------------------------------
	void WallCllision(tnl::Vector3& pos) {
		float n = 25;
		tnl::Vector3 MAP_MIN_POS = { -(n * 20),0,-(n * 20)};
		tnl::Vector3 MAP_MAX_POS = { (n * 20),0,(n * 20) };
		if (pos.x - n < MAP_MIN_POS.x) {
			pos.x = MAP_MIN_POS.x + n;
		};
		if (pos.z - n < MAP_MIN_POS.z) {
			pos.z = MAP_MIN_POS.z + n;
		};
		if (pos.x + n > MAP_MAX_POS.x) {
			pos.x = MAP_MAX_POS.x - n;
		};
		if (pos.z + n > MAP_MAX_POS.z) {
			pos.z = MAP_MAX_POS.z - n;
		};
	}
	

}



   

