#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include "CScene.h"
#include"CVector.h"
#include"CModel.h"
#include"CCharacter.h"
#include"CPlayer.h"
#include"CColliderTriangle.h"
#include"CColliderMesh.h"

/*
�Q�[���̃V�[��
*/
class CSceneGame : public CScene {
public:
	CModel mModel;
	//�����������̃I�[�o�[���C�h
	void Init();
	//�X�V�����̃I�[�o�[���C�h
	void Update();
	CVector mEye;
	CModel mBackGround;
	CPlayer mPlayer;
	
	CColliderTriangle mColliderTriangle;
	CColliderTriangle mColliderTriangle2;
	CColliderMesh mColliderMesh;
	CMatrix mBackGroundMatrix;
};


#endif
