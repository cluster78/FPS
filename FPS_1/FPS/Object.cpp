#include "pch.h"
#include "Object.h"

Object::Object(int _x, int _y) : x(_x), y(_y) { }
Object::~Object() { m_refMap = nullptr; }	//2_소멸자에서 맵데이터 삭제 추가.

//void Object::Render() { }
void Object::Init() {}
void Object::Update(float a_fDelta) { }
void Object::Explosived(class Bomb* a_refBomb) {}
void Object::Interaction(class Hero* a_refHero) {}
