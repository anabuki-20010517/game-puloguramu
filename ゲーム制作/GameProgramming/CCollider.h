#ifndef CCOLLIDER_H
#define CCOLLIDER_H
#include"CCharacter.h"
#include"CTransform.h"
class CCollider :public CTransform,public CTask{
public:
	CCharacter*mpParent;//	�e
	CMatrix*mpMatrix;//�e�s��
	float mRadius;//���a
	CCollider(CCharacter*parent, CMatrix*matrix, CVector position, float radius);
	void Render();
	~CCollider();
	//�Փ˔���
	static bool Collision(CCollider*m, CCollider*o);
	enum EType{
		ESPHERE,
		ETRIANGLE,
		ELINE,
	};
	EType mType;
	CVector mV[3];
	CCollider();
	//CollisionTriangleLine(�O�p�R���C�_�A�����R���C�_�A�����l�j
	//�����l�F�Փ˂��ĂȂ��ʒu�܂Ŗ߂�
	static bool CollisonTriangleLine(CCollider*triangle, CCollider*line, CVector*abjust);
	static bool CollidionTriangleSphere(CCollider*triangle, CCollider*sphere, CVector*adjust);
	void ChangePriority();

	enum ETag
	{
		EBODY,
		ESEARCH,
	};
	ETag mTag;
};

#endif