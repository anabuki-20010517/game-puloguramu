#ifndef CVECTOR_H
#define CVECTOR_H
#include "CMatrix.h"


class CVector{
public:
	CVector();
	CVector(float x, float y, float z);
	float mX, mY, mZ;
	//�e���̒l�ݒ�
	void Set(float x, float y, float z);
	CVector operator*(const CMatrix &m);
	//���Z�q�̃I�[�o�[���[�h
	CVector operator-(const CVector &v);
	//�x�N�g���̒�����Ԃ�
	float Length();
	float Dot(const CVector &v);
	CVector Cross(const CVector &v);
	CVector operator*(const float &f);
	CVector CVector::Normalize();
	CVector operator+(const CVector &v);
};

#endif