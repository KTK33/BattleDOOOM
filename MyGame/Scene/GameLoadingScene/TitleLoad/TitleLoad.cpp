#include "TitleLoad.h"
#include "../LoadingSceneInc.h"

TitleLoad::TitleLoad()
{
	next_ = SceneType::SCENE_TITLE;
}

void TitleLoad::start()
{
	Sprite::GetInstance().DeleteAll();
	Billboard::initialize();
	Sound::GetInstance().DeleteAll();
	SkeletalMesh::initialize();
	StaticMesh::initialize();
	CollisionMesh::initialize();
	Skybox::initialize();
	//�񓯊��J�n
	SetUseASyncLoadFlag(TRUE);
	//�^�C�g���Ŏg�p���郊�\�[�X�̃��[�h���s��
	LoadModel();
	LoadSound();
	LoadSprite();
	SetUseASyncLoadFlag(FALSE);

	//���[�h���郊�\�[�X���̐ݒ�
	mDL.setCount(GetASyncLoadNum());
}

void TitleLoad::update(float deltaTime)
{
	if (GetASyncLoadNum() <= 0)
	{
		isEnd_ = true;
	}
}

void TitleLoad::draw() const
{
	//���[�h��ʂ̕`��
	mDL.draw(0, GetASyncLoadNum());
}

void TitleLoad::end(){}

void TitleLoad::LoadModel()
{
	//���f���f�[�^�̓ǂݍ���
	SkeletalMesh::load(0, "asset/MODEL/Player/Model.mv1");
	SkeletalMesh::load(5, "asset/Weapon/Bullet1.mv1");
	StaticMesh::load(1, "asset/Weapon/Italian/Italian machine guns.mv1");
	StaticMesh::load(2, "asset/Weapon/Italian/Italian machine guns.mv2");
	SkeletalMesh::load(50, "asset/MODEL/ActionPlayer/ActionPlayer.mv1");
	StaticMesh::load(10, "asset/Weapon/ActionPlayer/dagger.mv1");
}

void TitleLoad::LoadSound()
{
	auto& sound = Sound::GetInstance();
	sound.LoadBGM("asset/Sound/BGM/TitleSceneBGM.mp3", BGM_ID::TITLE_BGM);
	sound.LoadSE("asset/Sound/SE/DamageEnemySE.mp3", SE_ID::DAMAGEENEMY_SE);
	sound.LoadSE("asset/Sound/SE/TitleKetteiSE.mp3", SE_ID::TITLEKETTEI_SE);
	sound.LoadSE("asset/Sound/SE/PauseCursorSE.mp3", SE_ID::PAUSECURSOR_SE);
	sound.LoadSE("asset/Sound/SE/PauseKetteiSE.mp3", SE_ID::PAUSEKETTEI_SE);
}

void TitleLoad::LoadSprite()
{
	auto& sprite = Sprite::GetInstance();
	sprite.Load("asset/UI/Fade/TitleBackBlack.png", SPRITE_ID::FADEBLACK);

	//�^�C�g����ʂ�UI
	sprite.Load("asset/UI/TitleScene/TitleBack.png", SPRITE_ID::TITLEBACK);
	sprite.Load("asset/UI/TitleScene/TitleName.png", SPRITE_ID::TITLENAME);
	sprite.Load("asset/UI/TitleScene/TitleNameBack.png", SPRITE_ID::TITLENAMEBACK);
	sprite.Load("asset/UI/TitleScene/PressStartUI.png", SPRITE_ID::TITLEPRESS_START);
	sprite.Load("asset/UI/TitleScene/TitleBackWhite.png", SPRITE_ID::TITLEBACKWHITE);
	sprite.Load("asset/UI/TitleScene/Choui.png", SPRITE_ID::TITLECHUI);
	sprite.Load("asset/UI/TitleScene/Jikyo.png", SPRITE_ID::TITLEJIKYO);

	//�Z���N�g��ʂ�UI
	sprite.Load("asset/UI/TitleScene/SelectModeBack.png", SPRITE_ID::SELECTBACK);
	sprite.Load("asset/UI/TitleScene/SelectShooting.png", SPRITE_ID::SELECT_SHOOTING);
	sprite.Load("asset/UI/TitleScene/SelectShooting_dec.png", SPRITE_ID::SELECT_SHOOTING_DEC);
	sprite.Load("asset/UI/TitleScene/SelectShootingex.png", SPRITE_ID::SELECT_SHOOTING_EX);
	sprite.Load("asset/UI/TitleScene/SelectAction.png", SPRITE_ID::SELECT_ACTION);
	sprite.Load("asset/UI/TitleScene/SelectAction_dec.png", SPRITE_ID::SELECT_ACTION_DEC);
	sprite.Load("asset/UI/TitleScene/SelectActionex.png", SPRITE_ID::SELECT_ACTION_EX);
	sprite.Load("asset/UI/TitleScene/SelectTitle.png", SPRITE_ID::SELECT_NAME);
	sprite.Load("asset/UI/TitleScene/SelectPurposeS.png", SPRITE_ID::SELECT_PUR_S);
	sprite.Load("asset/UI/TitleScene/SelectPurposeA.png", SPRITE_ID::SELECT_PUR_A);


	//�G�t�F�N�g
	sprite.Load("asset/UI/Effect/BulletHit.png", SPRITE_ID::EFFECT_BULLETHIT);
}