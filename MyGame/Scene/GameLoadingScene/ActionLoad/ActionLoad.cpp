#include "ActionLoad.h"
#include "../LoadingSceneInc.h"

ActionLoad::ActionLoad()
{
	next_ = SceneType::SCENE_ACTION_PLAY;
}

void ActionLoad::start()
{
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

void ActionLoad::update(float deltaTime)
{
	if (GetASyncLoadNum() <= 0)
	{
		isEnd_ = true;
	}
}

void ActionLoad::draw() const
{
	//���[�h��ʂ̕`��
	mDL.draw(1, GetASyncLoadNum());
}

void ActionLoad::end(){}

void ActionLoad::LoadModel()
{
	//�X�e�[�W���f���̓ǂݍ���
	CollisionMesh::load(0, "asset/stage/Stage/arena.mv1");
	//�X�J�C�{�b�N�X���f���̓ǂݍ���
	Skybox::load(0, "asset/skybox/skydome.mv1");

	//���f���f�[�^�̓ǂݍ���
	SkeletalMesh::load(50, "asset/MODEL/ActionPlayer/ActionPlayer.mv1");
	SkeletalMesh::load(51, "asset/MODEL/RedSamurai/RedSamurai.mv1");
	StaticMesh::load(10, "asset/Weapon/ActionPlayer/dagger.mv1");
	StaticMesh::load(11, "asset/Weapon/Samurai/katana.mv1");
	StaticMesh::load(12, "asset/Weapon/Arrow/Bow.mv1");
	StaticMesh::load(13, "asset/Weapon/Arrow/Quiver.mv1");
	SkeletalMesh::load(52, "asset/Weapon/Arrow/Arrow.mv1");
}

void ActionLoad::LoadSound()
{
}

void ActionLoad::LoadSprite()
{
	auto& sprite = Sprite::GetInstance();
	//�A�N�V�������[�h��UI
	sprite.Load("asset/UI/ActionModePause/PauseBack.png", SPRITE_ID::ACTIONPAUSE_BACK);
	sprite.Load("asset/UI/ActionModePause/Operation.png", SPRITE_ID::ACTIONPAUSE_OPERATION);
	sprite.Load("asset/UI/ActionModePause/OperationUI.png", SPRITE_ID::ACTIONPAUSE_OPERATION_UI);
	sprite.Load("asset/UI/ActionModePause/TitleBackUI.png", SPRITE_ID::ACTIONPAUSE_TITLEBACK);
	sprite.Load("asset/UI/ActionModePause/cursor.png", SPRITE_ID::ACTIONPAUSE_CURSOR);

	sprite.Load("asset/UI/ActionMode/APlayerHPFrame.png", SPRITE_ID::ACTION_PLAYER_HPFRAME);
	sprite.Load("asset/UI/ActionMode/APlayerHPGauge.png", SPRITE_ID::ACTION_PLAYER_HPGAUGE);
	sprite.Load("asset/UI/ActionMode/RedSamuraiHPFrame.png", SPRITE_ID::REDSAMURAI_HPFRAME);
	sprite.Load("asset/UI/ActionMode/RedSamuraiHPGauge.png", SPRITE_ID::REDSAMURAI_HPGAUGE);
}