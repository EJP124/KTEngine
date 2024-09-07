#include "Precompiled.h"
#include "AnimationBuilder.h"

using namespace KTEngine;
using namespace KTEngine::Graphics;

namespace
{
	template<class T>
	inline void PushKey(Keyframes<T>& Keyframes, const T& value, float t, EaseType e)
	{
		ASSERT(Keyframes.empty() || Keyframes.back().time <= t, "AnimationBuilder : cannot add keyframe back in time");
		Keyframes.emplace_back(value, t, e);
	}
}

AnimationBuilder& AnimationBuilder::AddPositionKey(const Math::Vector3& pos, float time, EaseType easeType)
{
	PushKey(mWorkingCopy.mPositionKeys, pos, time, easeType);
	mWorkingCopy.mDuration = Math::Max(mWorkingCopy.mDuration, time);
	return *this;
}
AnimationBuilder& AnimationBuilder::AddRotationKey(const Math::Quaternion& rot, float time, EaseType easeType)
{
	PushKey(mWorkingCopy.mRotationKeys, rot, time, easeType);
	mWorkingCopy.mDuration = Math::Max(mWorkingCopy.mDuration, time);
	return *this;
}
AnimationBuilder& AnimationBuilder::AddScaleKey(const Math::Vector3& scale, float time, EaseType easeType)
{
	PushKey(mWorkingCopy.mScaleKeys, scale, time, easeType);
	mWorkingCopy.mDuration = Math::Max(mWorkingCopy.mDuration, time);
	return *this;
}

AnimationBuilder& AnimationBuilder::AddEventKey(AnimationCallback cb, float time)
{
	PushKey(mWorkingCopy.mEventKeys, cb, time, EaseType::Linear);
	mWorkingCopy.mDuration = Math::Max(mWorkingCopy.mDuration, time);
	return *this;
}

[[nodiscard]] Animation AnimationBuilder::Build()
{
	ASSERT(!mWorkingCopy.mPositionKeys.empty()
		|| !mWorkingCopy.mRotationKeys.empty()
		|| !mWorkingCopy.mScaleKeys.empty()
		|| !mWorkingCopy.mEventKeys.empty(),
		"AnimationBuilder: no animation keys were added");
	return std::move(mWorkingCopy);
}