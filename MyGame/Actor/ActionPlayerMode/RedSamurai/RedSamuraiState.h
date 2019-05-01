#pragma once

class RedSamuraiState {
public:
	enum State
	{
		NONE,
		RedSamuraiIdel,
		RedSamuraiForWard,
		RedSamuraiBackWard,
		RedSamuraiRight,
		RedSamuraiLeft,
		RedSamuraiAttack,
		RedSamuraiDead,
	};
};
