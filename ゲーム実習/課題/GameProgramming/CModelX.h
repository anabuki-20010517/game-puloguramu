#ifndef CMODELX_H
#define CMODELX_H

#define MODEL_FILE "sample.blend.x"

#define SAFE_DELETE_ARRAY(a){if(a)delete[]a;a=0;}
#define ARRAY_SIZE(a)(sizeof(a)/sizeof(a[0]))
#include<vector>
#include"CMatrix.h"
#include"CVector.h"
class CModelX;
class CMesh{
	public:
		int mVertexNum;	//���_��
		CVector *mpVertex;	//���_�f�[�^
		int mFaceNum;	//�ʐ�
		int *mpVertexIndex;	//�ʂ��\�����钸�_�ԍ�
		int mNormalNum;	//�@����
		CVector *mpNormal;	//�@���f�[�^
		CMesh()
			:mVertexNum(0)
			, mpVertex(0)
			, mFaceNum(0)
			, mpVertexIndex(nullptr)
			, mNormalNum(0)
			, mpNormal(nullptr)
		{}
		~CMesh(){
			SAFE_DELETE_ARRAY(mpVertex);
			SAFE_DELETE_ARRAY(mpVertexIndex);
			SAFE_DELETE_ARRAY(mpNormal);
		}
		void Init(CModelX *model);
		void Render();

};


class CModelXFrame{
public:
	CMesh mMesh;
	std::vector<CModelXFrame*> mChild;
	CMatrix mTransformMatrix;
	char*mpName;
	int mIndex;
	CModelXFrame(CModelX* model);
	~CModelXFrame(){
		std::vector<CModelXFrame*>::iterator itr;
		for (itr = mChild.begin(); itr != mChild.end(); itr++){
			delete*itr;
		}
		SAFE_DELETE_ARRAY(mpName);
	}
	void Render();
};


class CModelX{
public:
	char*mpPointer;
	char mToken[1024];
	std::vector<CModelXFrame*>mFrame;	//�t���[���̔z��
		CModelX()
		:mpPointer(0)
	{}
		~CModelX(){
			if (mFrame.size()>0)
			{
				delete mFrame[0];
			}
		}
	void Load(char*file);
	void GetToken();
	void SkipNode();
	float GetFloatToken();
	int GetIntToken();
	void Render();
};
#endif