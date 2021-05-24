#ifndef CCHARACTER_H
#define CCHARACTER_H
#include"CTransform.h"
#include "CModel.h"
#include"CTask.h"
class CCollider;
class CCharacter :public CTransform,public CTask{
public:
	enum ETag
	{
		EZERO,			//�����l
		EPLAYER,		//�v���C���[
		EENEMY,			//�G
		EBULLETPLAYER,	//�v���C���[�e
		EBULLETENEMY,	//�G�e
	};
	ETag mTag;
	CModel*mpModel;
	void Render();
	~CCharacter();
	CCharacter();
	
	virtual void Collision(CCollider*m, CCollider*o){}
};

#endif