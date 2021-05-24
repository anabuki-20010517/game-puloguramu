#ifndef CTRIANGLE_H
#define CTRIANGLE_H

#include"CVector.h"
class CTriangle{
	public:
		CVector mV[3];
		CVector mN[3];//�@��
		void SetVertex(const CVector &v0, const CVector &v1, const CVector &v2);
		void SetNormal(const CVector &vn);
		void SetNormal(const CVector &v0, const CVector &v1, const CVector &v2);
		void Render();
		int mMaterialIdx;	//�}�e���A���ԍ�
	    CVector mUv[3];		//�e�N�X�`���}�b�s���O
		void Render(const CMatrix &m);
		};

#endif