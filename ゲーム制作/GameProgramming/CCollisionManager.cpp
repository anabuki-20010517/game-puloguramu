#include"CCollisionManager.h"

CCollisionManager*CCollisionManager::mpInstance = 0;
CCollisionManager*CCollisionManager::Get()
{
	if (mpInstance == 0)
	{
		mpInstance = new CCollisionManager();
	}
	return mpInstance;

}
//�Փˏ���
/*
void CCollisionManager::Collision(){
	CCollider*task = (CCollider*)mHead.mpNext;
	while (task->mpNext){
		CCollider*next = (CCollider*)task->mpNext;
		while (next->mpNext){
			if (task->mpParent)
				task->mpParent->Collision(task, next);
			if (next->mpParent)
				next->mpParent->Collision(next, task);
			next = (CCollider*)next->mpNext;
		}
		task = (CCollider*)task->mpNext;
	}
}
*/
//Collision(�R���C�_�A�͈�)
//�R���C�_�̗D��x�{�͈́`�D��x�|�͈͂܂ł̃R���C�_�ƏՓ˔�������s����
void CCollisionManager::Collision(CCollider*c, int range){
	//���݈ʒu��擪�ɂ���
	CCollider*task = (CCollider*)mHead.mpNext;
	//�͈͂܂œǂݔ�΂�
	while (task->mpNext){
		if (task->mPriority <= c->mPriority + range)
		{
			break;
		}
		//���݈ʒu�����ɂ���
		task = (CCollider*)task->mpNext;
	}
	//�Ō�܂ŗ�����I������
	while (task->mpNext){
		if (task->mPriority <= c->mPriority - range)
		{
			break;
		}
		//�e�̏Փˏ������Ăяo��
		//�����̏Փˏ���
		if (c->mpParent&&c != task)
			c->mpParent->Collision(c, task);
		//���݈ʒu�����ɂ���
		task = (CCollider*)task->mpNext;
	}
}
