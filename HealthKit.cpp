#include "HealthKit.h"
HealthKit::HealthKit(Vector2 position, std::string spriteName, ColliderType colliderType, int sortingOrder, bool isStatic, bool isTrigger) : Prop(position, spriteName, colliderType, sortingOrder, isStatic, isTrigger)
{
	tag = Tag::DEFAULT;
}
