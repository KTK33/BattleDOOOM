#include "DrawLoadScene.h"
#include "../Graphics/Graphics3D.h"

void DrawLoadScene::setCount(int count)
{
	mCount = count;
}

void DrawLoadScene::draw(int sceneNum, int loadnum) const
{
	Graphics3D::clear_color(0, 0, 0);

	int handle = NULL;
	if (sceneNum == 1)
	{
		handle = LoadGraph("asset/UI/LoadScene/ShootingOpe.png");
		DrawGraph(0, 0, handle, FALSE);
	}
	else if (sceneNum == 2)
	{
		handle = LoadGraph("asset/UI/LoadScene/ActionOpe.png");
		DrawGraph(0, 0, handle, FALSE);
	}

	int id[2] = {};
	id[0] = LoadGraph("asset/UI/LoadScene/LoadGauge.png");
	id[1] = LoadGraph("asset/UI/LoadScene/LoadFream.png");
	DrawGraph(210, 1000, id[1], FALSE);
	DrawRectGraphF(215, 1005, 0, 0, 1490 / mCount * (mCount - loadnum), 40, id[0], false);
	// 読み込んだ画像のグラフィックハンドルを削除
	if (loadnum <= 0)
	{
		DeleteGraph(handle);

		for (int i = 0; i < 2; i++)
		{
			DeleteGraph(id[i]);
		}
	}
}
