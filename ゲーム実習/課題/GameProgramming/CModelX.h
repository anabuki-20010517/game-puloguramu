#ifndef CMODELX_H
#define CMODELX_H

#define MODEL_FILE "sample.blend.x"

#define SAFE_DELETE_ARRAY(a){if(a)delete[]a;a=0;}
#define ARRAY_SIZE(a)(sizeof(a)/sizeof(a[0]))
#include<vector>
#include"CMatrix.h"
#include"CVector.h"
class CModelX;
class CMaterial;
class CSkinWeights{
public:
	char*mpFrameName;
	int mFrameIndex;
	int mIndexNum;
	int*mpIndex;
	float*mpWeight;
	CMatrix mOffset;

	CSkinWeights(CModelX*model);

	~CSkinWeights(){
		SAFE_DELETE_ARRAY(mpFrameName);
		SAFE_DELETE_ARRAY(mpIndex);
		SAFE_DELETE_ARRAY(mpWeight);

	}
};

class CAnimationKey{
public:
	float mTime;
	CMatrix mMatrix;
};


class CAnimation{
public:
	char*mpFrameName;
	int mFrameIndex;
	int mKeyNum;
	CAnimationKey *mpKey;	//キー数
	CAnimation(CModelX*model);	//キーの配列
	
	~CAnimation(){
		SAFE_DELETE_ARRAY(mpFrameName);
		SAFE_DELETE_ARRAY(mpKey)
	}
};


class CAnimationSet{
public:
	char *mpName;
	std::vector<CAnimation*>mAnimation;
	CAnimationSet(CModelX*model); 

	~CAnimationSet(){
		SAFE_DELETE_ARRAY(mpName);
		for (int i = 0; i < mAnimation.size(); i++){
			delete mAnimation[i];
		}

	}
};


class CMesh{
	public:
		int mVertexNum;	//頂点数
		CVector *mpVertex;	//頂点データ
		int mFaceNum;	//面数
		int *mpVertexIndex;	//面を構成する頂点番号
		int mNormalNum;	//法線数
		CVector *mpNormal;	//法線データ
		int mMaterialNum;
		int mMaterialIndexNum;
		int *mpMaterialIndex;
		std::vector<CMaterial*>mMaterial;
		std::vector<CSkinWeights*>mSkinWeights;
		CMesh()
			:mVertexNum(0)
			, mpVertex(0)
			, mFaceNum(0)
			, mpVertexIndex(nullptr)
			, mNormalNum(0)
			, mpNormal(nullptr)
			, mMaterialNum(0)
			, mMaterialIndexNum(0)
			, mpMaterialIndex(nullptr)
		{}
		~CMesh(){
			SAFE_DELETE_ARRAY(mpVertex);
			SAFE_DELETE_ARRAY(mpVertexIndex);
			SAFE_DELETE_ARRAY(mpNormal);
			SAFE_DELETE_ARRAY(mpMaterialIndex);
			for (int i = 0; i < mSkinWeights.size(); i++){
				delete mSkinWeights[i];
			}
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
	std::vector<CModelXFrame*>mFrame;	//フレームの配列
	std::vector<CAnimationSet*>mAnimationSet;
		CModelX()
		:mpPointer(0)
	{}
		~CModelX(){
			if (mFrame.size()>0)
			{
				delete mFrame[0];
			}
			for (int i = 0; i < mAnimationSet.size(); i++){
				delete mAnimationSet[i];
			}
		}
	void Load(char*file);
	void GetToken();
	void SkipNode();
	float GetFloatToken();
	int GetIntToken();
	void Render();
	CModelXFrame*FindFreame(char*name);

};





#endif