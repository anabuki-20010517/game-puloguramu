#ifndef CTRANSFORM_H
#define CTRANSFORM_H
#include"CVector.h"
class CTransform{
public:
	CVector mPosition; //�ʒu
	CVector mRotation; //��]
	CVector mScale; //�g��k��
	CMatrix mMatrixTranslate; //���s�ړ��s��
	CMatrix mMatrixRotate; //��]�s��
	CMatrix mMatrixScale; //�g��k���s��
	CMatrix mMatrix; //�����s��
	void Update();
};
#endif