#include "CSceneGame.h"
//
#include "CCamera.h"
//
#include "CUtil.h"
#include"CRes.h"
#include"CModelX.h"
#include"glut.h"
#include<Windows.h>
CMatrix Matrix;
CSceneGame::~CSceneGame() {

}

void CSceneGame::Init() {
	CRes::sModelX.Load(MODEL_FILE);
	//テキストフォントの読み込みと設定
	mFont.LoadTexture("FontG.tga", 1, 4096 / 64);

}


void CSceneGame::Update() {
	//カメラのパラメータを作成する
	CVector e, c, u;//視点、注視点、上方向
	//視点を求める
	e = CVector(1.0f, 2.0f, 10.0f);
	//注視点を求める
	c = CVector();
	//上方向を求める
	u = CVector(0.0f, 1.0f, 0.0f);

	Camera.Set(e, c, u);
	Camera.Render();

	if (GetKeyState('K') & 0x8000){
		Matrix = Matrix*CMatrix().RotateX(1);
	}
	if (GetKeyState('L') & 0x8000){
		Matrix = Matrix*CMatrix().RotateY(1);
	}
	if (GetKeyState('I') & 0x8000){
		Matrix = Matrix*CMatrix().RotateX(-1);
	}
	if (GetKeyState('J') & 0x8000){
		Matrix = Matrix*CMatrix().RotateY(-1);
	}
	glMultMatrixf(Matrix.mF);
	CRes::sModelX.Render();
	//カメラクラスの設定



	//2D描画開始
	CUtil::Start2D(0, 800, 0, 600);

	mFont.DrawString("3D PROGRAMMING", 20, 20, 10, 12);

	//2Dの描画終了
	CUtil::End2D();

	return;
}

