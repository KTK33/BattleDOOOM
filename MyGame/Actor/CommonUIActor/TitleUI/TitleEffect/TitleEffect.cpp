#include "TitleEffect.h"
#include "../Sound/Sound.h"

TitleEffect::TitleEffect(IWorld * world):
	Actor(world,"TitleEffect",Vector3::Zero),
	meff{ (int)EFFECT_ID::TITLE_THUNDER },
	mTimer{180},
	mEffectPos{ GetCameraTarget()}
{
	meff.stop();
	meff.set_endTime(70);
	meff.play();
	Sound::GetInstance().PlaySE(SE_ID::THUNDER_SE);
}

void TitleEffect::update(float deltaTime)
{
	//エフェクトの設定
	meff.set_position(mEffectPos);
	meff.set_scale(Vector3(1.0f, 1.0f, 1.0f));
	meff.set_rotation(Vector3::Zero);
	meff.update(deltaTime);

	mTimer--;
	if (mTimer <= 0) //3秒ごとに雷エフェクトの表示
	{
		mEffectPos = GetCameraTarget() + rotation_.Right() * Random::rand(6.0f,6.0f);
		meff.play();
		meff.set_endTime(70);
		Sound::GetInstance().PlaySE(SE_ID::THUNDER_SE);
		mTimer = 180;
	}
}

void TitleEffect::draw() const
{
	meff.draw();
}
