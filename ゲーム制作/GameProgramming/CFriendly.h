#ifndef FRIENDLY_H
#define FRIENDLY_H
#include"CCharacter.h"
#include"CCollider.h"
class CFriendly :public CCharacter{
public:
	CFriendly(CModel*model, CVector position, CVector rotation, CVector scale);
	void Update();
	//�R���C�_
	CCollider mCollider1;
	CCollider mCollider2;
	CCollider mCollider3;

	void Collision(CCollider*m, CCollider*o);
	void TaskCollision();
};
#endif