#ifndef CBILLBOARD_H
#define CBILLBOARD_H
#include"CCharacter.h"
/*
�r���{�[�h�N���X
��ɃJ�����̕��������l�p�`
*/
class CBillBoard :public CCharacter{
public:
	CTriangle mT[2];
	CMaterial mMaterial;
	CBillBoard();
	CBillBoard(CVector pos, float w, float h);
	void Set(CVector pos, float w, float h);
	void Update();
	void Render();
	void Render(CMaterial*mpMaterial);
};

#endif