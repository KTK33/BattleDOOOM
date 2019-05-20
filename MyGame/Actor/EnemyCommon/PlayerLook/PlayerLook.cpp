#include "PlayerLook.h"

float PlayerLook::PlayerDirection(Actor * player, Vector3 & position, Matrix & matrix)
{
	const auto to_target = player->Getpose().Translation() - position;
	const auto angle = Vector3::Angle(matrix.Forward(), to_target);
	const auto forward_cross_target = Vector3::Cross(matrix.Forward(), to_target);
	return (forward_cross_target.y >= 0.0f) ? angle : -angle;
}

float PlayerLook::Look(Actor * player, Vector3 & position, Matrix & matrix)
{
	//�^�[�Q�b�g�����ɏ�����������ς��� Clamp�Ŗ������p�x(-TurnAngle�`TurnAngle)����
	float angle = 0.0f;
	angle = MathHelper::Clamp(PlayerDirection(player, position, matrix), -2.5f, 2.5f);
	return angle;
}
