#include "ShootingCamera.h"
#include "../Graphics/Graphics3D.h"

#include "../Input/GamePad/GamePad.h"
#include "../Input/KeyBoard/Keyboard.h"
#include "../Math/Vector2.h"
#include "../Actor/Camera/TPSCamera.h"
#include "../Actor/Camera/CameraSpring/CameraSpring.h"
#include "../Scene/GameData/GameDataManager.h"
#include "../Texture/Sprite.h"
#include "../Actor/ShootingPlayerMode/UIActor/PlaySceneUI/GameClearUIh.h"
#include "../Actor/ShootingPlayerMode/UIActor/PlaySceneUI/GameOverUI.h"

ShootingCamera::ShootingCamera(IWorld * world, std::weak_ptr<Actor> m_Player) :
	Actor(world, "Camera", Vector3::Zero),
	mAimPosMove{ 0,0 },
	mplayer{m_Player},
	mGetplayer_{nullptr},
	mFinishCamera{20.0f,20.0f,20.0f},
	malreadyCreate{false}
{}

void ShootingCamera::update(float deltaTime)
{
	//�v���C���[�̌���
	mGetplayer_ = world_->find_actor(ActorGroup::Player, "Player").get();
	if (mGetplayer_ == nullptr) return;

	//�v���C���[�����ʂ��A�{�X�����񂾂�I����������
	if (GameDataManager::getInstance().GetPlayerDead() == true || 
		GameDataManager::getInstance().GetDeadBossEnemy() == true)
	{
		//�Q�[���I�����ݒ�
		PlayerGameFinish();
	}
	else
	{
		//�퓬���̃J�����̐ݒ�
		CameraSet(deltaTime);
	}

	//�J�����ɒl��ݒ�
	TPSCamera::GetInstance().SetRange(0.5f, 1000.0f);
	TPSCamera::GetInstance().Position.Set(position_);
	TPSCamera::GetInstance().Target.Set(mtarget_);
	TPSCamera::GetInstance().Up.Set(Vector3::Up);
	TPSCamera::GetInstance().Update();

	//�΂�
	CameraSpring::move(position_, velocity_, position_,1.0f, 0.2f, 0.8f);
}

void ShootingCamera::draw() const{}

void ShootingCamera::CameraSet(float deltaTime)
{
	//�J�����̃^�[�Q�b�g���v���C���[�̑O�����ɐݒ�
	mtarget_ = position_ + mGetplayer_->Getrotation().Forward() * 50;

	//�^�[�Q�b�g�ɓ��͏������Z
	mtarget_.x += mGetplayer_->Getrotation().Right().x * mAimPosMove.x;
	mtarget_.y += mAimPosMove.y;
	mtarget_.z += mGetplayer_->Getrotation().Right().z * mAimPosMove.x;

	//�|�[�Y���ł͂Ȃ��A�A�C�e���{�b�N�X���J���Ă��Ȃ��Ƃ�
	if (world_->GetPauseCheck() == false && GameDataManager::getInstance().GetItemBoxOpen() == false)
	{
		//�G�C�����̑���
		Aim_Input();
	}

	if (GameDataManager::getInstance().GetSightCheck() == true){
		//�G�C����
		In_Aim();
	}
	else{
		//�G�C���O
		Out_Aim();
	}
}

void ShootingCamera::Aim_Input()
{
	//�Q�[���p�b�h�̓��͐��O�Ȃ�L�[�{�[�h����
	if (GetJoypadNum() == 0){
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::UP))
		{
			mAimPosMove.y += 1.0f * (GameDataManager::getInstance().GetAIMSPD() * 0.2f);
		}
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::DOWN))
		{
			mAimPosMove.y -= 1.0f* (GameDataManager::getInstance().GetAIMSPD() * 0.2f);
		}
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::RIGHT))
		{
			mAimPosMove.x += 1.0f * (GameDataManager::getInstance().GetAIMSPD() * 0.2f);
		}
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::LEFT))
		{
			mAimPosMove.x -= 1.0f* (GameDataManager::getInstance().GetAIMSPD() * 0.2f);
		}
	}
	else{
		//�Q�[���p�b�h�ł̉E�X�e�B�b�N�̑���
		mAimPosMove += GamePad::GetInstance().RightStick() * (GameDataManager::getInstance().GetAIMSPD() * 0.2f);
	}
}

void ShootingCamera::Out_Aim()
{
	//�J�����̃|�W�V�����̐ݒ�
	position_ = Vector3(
		mGetplayer_->Getposition().x + 10 * mGetplayer_->Getrotation().Backward().x + 5 * mGetplayer_->Getrotation().Right().x,
		mGetplayer_->Getposition().y + 18,
		mGetplayer_->Getposition().z + 10 * mGetplayer_->Getrotation().Backward().z + 5 * mGetplayer_->Getrotation().Right().z);

	//�^�[�Q�b�g�̏ꏊ�����X�ɍX�V
	mtarget_ = Vector3::Lerp(mtarget_, position_ + mGetplayer_->Getrotation().Forward(), 0.1f);

	//�J�����̈ړ��͈͂̐���
	mAimPosMove = Vector2::Clamp(mAimPosMove, Vector2(0, -30), Vector2(0, 30));
}

void ShootingCamera::In_Aim()
{
	//�J�����̃|�W�V�����̐ݒ�
	position_ = Vector3(
		mGetplayer_->Getposition().x + 4 * mGetplayer_->Getrotation().Backward().x + 2.5f * mGetplayer_->Getrotation().Right().x,
		mGetplayer_->Getposition().y + 16,
		mGetplayer_->Getposition().z + 4 * mGetplayer_->Getrotation().Backward().z + 2.5f * mGetplayer_->Getrotation().Right().z);

	//�^�[�Q�b�g�̏ꏊ�����X�ɍX�V
	mtarget_ = Vector3::Lerp(mtarget_, position_ + mGetplayer_->Getrotation().Forward() * 1, 0.1f);

	//�v���C���[�Ƀ^�[�Q�b�g�̃|�W�V������n��
	mplayer.lock()->receiveMessage(EventMessage::SIGHT_POSITION, reinterpret_cast<void*>(&mtarget_));

	//�J�����̈ړ��ƈꏏ�Ƀv���C���[����]������
	In_Aim_Rotation();

	//�G�C���ꏊ�̏㉺����
	mAimPosMove = Vector2::Clamp(mAimPosMove, Vector2(15, -20), Vector2(15, 15));
}

void ShootingCamera::In_Aim_Rotation()
{
	float rote = 0.0f;

	//�Q�[���p�b�h�̓��͐��O�Ȃ�L�[�{�[�h����
	if (GetJoypadNum() == 0) {
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::RIGHT)) 
		{
			rote = 1.0f* (GameDataManager::getInstance().GetAIMSPD() * 0.25f);
		}
		else if (Keyboard::GetInstance().KeyStateDown(KEYCODE::LEFT))
		{
			rote = -1.0f * (GameDataManager::getInstance().GetAIMSPD() * 0.25f);
		}
	}
	else
	{
		//�Q�[���p�b�h�̉E�X�e�B�b�N��X����
		rote = GamePad::GetInstance().RightStick().x * (GameDataManager::getInstance().GetAIMSPD() * 0.25f);
	}
	//�v���C���[�ɉ�]��n��
	mplayer.lock()->receiveMessage(EventMessage::SIGHT_ROTATION, reinterpret_cast<void*>(&rote));
}

void ShootingCamera::PlayerGameFinish()
{
	//�v���C���[�����S���Q�[���I�[�o�[�ցA�{�X���S���Q�[���N���A��
	if (GameDataManager::getInstance().GetPlayerDead() == true)
	{
		GameOver();
	}
	else if (GameDataManager::getInstance().GetDeadBossEnemy() == true)
	{
		GameClear();
	}

	//�J�����̃|�W�V�����̐ݒ�
	position_ = Vector3(
		mGetplayer_->Getposition().x + mFinishCamera.x * mGetplayer_->Getrotation().Forward().x + 1 * mGetplayer_->Getrotation().Right().x,
		mGetplayer_->Getposition().y + mFinishCamera.y,
		mGetplayer_->Getposition().z + mFinishCamera.z * mGetplayer_->Getrotation().Forward().z + 1 * mGetplayer_->Getrotation().Right().z);

	//�J�����̃^�[�Q�b�g�̐ݒ�
	mtarget_ = mGetplayer_->Getposition() + 10 * mGetplayer_->Getrotation().Forward();
}

void ShootingCamera::GameOver()
{
	//�J���������X�Ɉ����Ă����悤�ɂ���
	mFinishCamera += Vector3::One * 0.25f;

	//�J�����̈����͈͂̐���
	mFinishCamera = Vector3::Clamp(mFinishCamera, Vector3::Zero, Vector3(100, 100, 100));

	//��x�����Q�[���I�[�o�[�A�N�^�[�̐���
	if (!malreadyCreate)
	{
		world_->add_actor(ActorGroup::GameFinishUI, new_actor<GameOverUI>(world_));
		malreadyCreate = true;
	}
}

void ShootingCamera::GameClear()
{
	//�J���������X�Ɉ����Ă����悤�ɂ���
	mFinishCamera += Vector3::One * 0.25f;

	//�J�����̈����͈͂̐���
	mFinishCamera = Vector3::Clamp(mFinishCamera, Vector3::Zero, Vector3(100, 100, 100));

	//��x�����Q�[���N���A�A�N�^�[�̐���
	if (!malreadyCreate)
	{
		world_->add_actor(ActorGroup::GameFinishUI, new_actor<GameClearUI>(world_));
		malreadyCreate = true;
	}
}
