#pragma once

#include <memory>

class ActorStateBase;
using ActorStatePtr = std::shared_ptr<ActorStateBase>;

template<class T, class... Args>
inline ActorStatePtr add_state(Args&&... args)
{
	return std::make_shared<T>(args...);
}
