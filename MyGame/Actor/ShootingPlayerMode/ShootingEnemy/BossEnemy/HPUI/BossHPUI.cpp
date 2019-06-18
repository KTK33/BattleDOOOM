#include "BossHPUI.h"
#include "../Game/Define.h"
#include "../Texture/Sprite.h"
#include "../Game/GameData/ShootingMode/ShootingBossEnemyData.h"
#include "../Billboard/Billboard.h"

void BossHP::draw(int hp, Vector3 pos) const
{
	Billboard::bind((int)SPRITE_ID::BOSSHP_UI);
	Billboard::draw(pos, 20.0f,0.0f,0.0f);
	Billboard::bind((int)SPRITE_ID::BOSSHP_GAUGE);
	Billboard::Mobidraw(pos, Vector2(0, 0), Vector2(20.0f/BossHPVal * hp, 0), Vector2(20.0f / BossHPVal * hp, 1.2f), Vector2(0, 1.2f));
}
