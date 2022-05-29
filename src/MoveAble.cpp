#include "MoveAble.h"

MoveAble::MoveAble(Resources::Objects object, Direction dir)
	: GameObj(object, dir), m_dir(dir)
	//m_animation(Resources::instance().animationData(object), object, dir, m_sprite)
{
}
