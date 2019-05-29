#pragma once
//�Q�[���V�X�e����̃p�����[�^

static const float BGMVOLUME = 0.5f;
static const float SEVOLUME = 0.5f;

static int constexpr WINDOW_WIDTH = 1920;
static int constexpr WINDOW_HEIGHT = 1080;

static int constexpr SPACE_DEPTH = 5 - 1;//�[�x��0�`n�͈̔͂����

static int constexpr GRID_X = 10;
static int constexpr GRID_Y = 10;

static constexpr int SEGMENT_VERTEX_COUNT = 2;

///�V���[�e�B���O���[�h

//�v���C���[�̍ő�g�o
static constexpr int ShootingPlayerHPVal = 10;

//��x�ɃZ�b�g�ł���e��
static constexpr int SetGunPoint = 7;

//�e���E�����Ƃ��Ɏ擾�ł���e��
static const int GetBulletPoint = 5;

//�񕜃A�C�e�����E�����Ƃ��̉񕜗�
static const int GetHpPoint = 3;

//�G�̗��Ƃ��A�C�e���̊���(0�`100) �l���傫���قǒe�������₷���A0�ɋ߂��قǉ񕜃A�C�e���������₷���@100�ɋ߂��قǒe�������₷��
static const int GetItemRate = 70;

//�U���A�b�v�A�C�e�����g�����Ƃ��̌p������(�b)
static const int AttackUpTime = 30;

//�m�[�}���G��HP
static const int NormalHPVal = 3;

//�{�X�G��HP
static const int BossHPVal = 10;

///�A�N�V�������[�h

//�v���C���[��HP
static const int ActionPlayerHPVal = 10;

//�Ԏ���HP
static const int RedSamuraiHPVal = 5;