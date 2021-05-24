#ifndef CENEMY_H
#define CENEMY_H
#include"CCharacter.h"
#include"CCollider.h"
class CEnemy :public CCharacter{
public:
	CEnemy(CModel*model, CVector position, CVector rotation, CVector scale);
	void Update();
	//�R���C�_
	CCollider mCollider1;
	CCollider mCollider2;
	CCollider mCollider3;

	void Collision(CCollider*m, CCollider*o);
	void TaskCollision();
};
#endif