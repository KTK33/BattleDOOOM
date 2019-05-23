#include "DrawLoadScene.h"
#include "../Graphics/Graphics3D.h"

void DrawLoadScene::setCount(int count)
{
	mCount = count;
}

void DrawLoadScene::draw(int sceneNum, int loadnum) const
{
	Graphics3D::clear_color(0, 0, 0);
	int id[2] = {};
	id[0] = LoadGraph("asset/UI/LoadScene/LoadGauge.png");
	id[1] = LoadGraph("asset/UI/LoadScene/LoadFream.png");
	DrawGraph(210, 800, id[1], FALSE);
	DrawRectGraphF(215, 805, 0, 0, 1490 / mCount * (mCount - loadnum), 40, id[0], false);
	// 読み込んだ画像のグラフィックハンドルを削除
	if (loadnum <= 0)
	{
		for (int i = 0; i < 2; i++)
		{
			DeleteGraph(id[i]);
		}
	}
}
