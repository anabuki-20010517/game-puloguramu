#include"glut.h"
#include<stdio.h>
#include<string.h>
#include"CModelX.h"
#include"CMaterial.h"

int CModelX::GetIntToken(){
	GetToken();
	return atoi(mToken);
}
CSkinWeights::CSkinWeights(CModelX*model)
:mpFrameName(0)
, mFrameIndex(0)
, mIndexNum(0)
, mpIndex(0)
, mpWeight(0)
{
	model->GetToken();
	model->GetToken();
	//フレーム名エリア確保、設定
	mpFrameName = new char[strlen(model->mToken) + 1];
	strcpy(mpFrameName, model->mToken);
	//頂点番号取得
	mIndexNum = model->GetIntToken();
	if (mIndexNum > 0){
		mpIndex = new int[mIndexNum];
		mpWeight = new float[mIndexNum];
		//頂点番号取得
		for (int i = 0; i < mIndexNum; i++)mpIndex[i] = model->GetIntToken();
		//頂点ウェイト取得
		for (int i = 0; i < mIndexNum; i++)mpWeight[i] = model->GetFloatToken();
	}
	//オフセット行列取得
	for (int i = 0; i < 16; i++){
		mOffset.mF[i] = model->GetFloatToken();
	}
	model->GetToken();

#ifdef _DEBUG
	printf("SkinWeights:%s\n", mpFrameName);
	for (int i = 0; i < mIndexNum; i++) {
		printf("%d", mpIndex[i]);
		printf("%10f\n", mpWeight[i]);
	}
	mOffset.Print();
#endif
}

CAnimation::CAnimation(CModelX*model)
:mpFrameName(0)
, mFrameIndex(0)
, mKeyNum(0)
, mpKey(nullptr)
{
	model->GetToken();
	if (strchr(model->mToken, '{')){
		model->GetToken();

	}
	else{ model->GetToken();
	model->GetToken();
	}
	model->GetToken();
	mpFrameName = new char[strlen(model->mToken) + 1];
	strcpy(mpFrameName, model->mToken);
	mFrameIndex = model->FindFreame(model->mToken)->mIndex;
	model->GetToken();

	CMatrix*key[4] = { 0, 0, 0, 0 };
	float*time[4] = { 0, 0, 0, 0 };

	while (*model->mpPointer != '\0'){
		model->GetToken();
		if (strchr(model->mToken, '}'))break;
		if (strcmp(model->mToken, "AnimationKey") == 0){
			model->GetToken();
			int type = model->GetIntToken();
			mKeyNum = model->GetIntToken();
			switch (type){
			case 0:
				key[type] = new CMatrix[mKeyNum];
				time[type] = new float[mKeyNum];
				for (int i = 0; i < mKeyNum; i++){
					time[type][i] = model->GetFloatToken();
					model->GetToken();
					float w = model->GetFloatToken();
					float x = model->GetFloatToken();
					float y = model->GetFloatToken();
					float z = model->GetFloatToken();
					key[type][i].SetQuaternion(x, y, z, w);
				}
				break;
			case 1:
				key[type] = new CMatrix[mKeyNum];
				time[type] = new float[mKeyNum];
				for (int i = 0; i < mKeyNum; i++){
					time[type][i] = model->GetFloatToken();
					model->GetToken();
					float x = model->GetFloatToken();
					float y = model->GetFloatToken();
					float z = model->GetFloatToken();
					key[type][i].mM[0][0] = x;
					key[type][i].mM[1][1] = y;
					key[type][i].mM[2][2] = z;

				}
				break;
			case 2:
				key[type] = new CMatrix[mKeyNum];
				time[type] = new float[mKeyNum];
				for (int i = 0; i < mKeyNum; i++){
					time[type][i] = model->GetFloatToken();
					model->GetToken();
					float x = model->GetFloatToken();
					float y = model->GetFloatToken();
					float z = model->GetFloatToken();
					key[type][i].Translate(x, y, z);
				}
				break;
			case 4:
				mpKey = new CAnimationKey[mKeyNum];
				for (int i = 0; i < mKeyNum; i++){
					mpKey[i].mTime = model->GetFloatToken();
					model->GetToken();
					for (int j = 0; j < 16; j++){
						mpKey[i].mMatrix.mF[j] = model->GetFloatToken();
						}
					}
					break;
				}
				model->GetToken();
		}else{
			model->SkipNode();
		}
		
		
	}
	if (mpKey == 0){
		mpKey = new CAnimationKey[mKeyNum];
		for (int i = 0;i < mKeyNum; i++){
			mpKey[i].mTime = time[2][i];
			//行列さくせい Size*Rotation*Position
			mpKey[i].mMatrix = key[1][i] * key[0][i] * key[2][i];
		}
	}
	for (int i = 0; i < ARRAY_SIZE(key); i++){
		SAFE_DELETE_ARRAY(time[i]);
		SAFE_DELETE_ARRAY(key[i]);
	}
#ifdef _DEBUG
	printf("Animation:%s\n", mpFrameName);
	mpKey[0].mMatrix.Print();
#endif

}

CAnimationSet::CAnimationSet(CModelX*model)

:mpName(nullptr)
{
	model->mAnimationSet.push_back(this);
	model->GetToken();

	mpName = new char[strlen(model->mToken) + 1];
	strcpy(mpName, model->mToken);
	model->GetToken();
	while (*model->mpPointer != '\0')
	{
		model->GetToken();
		if (strchr(model->mToken, '}'))break;
		if (strcmp(model->mToken, "Animation") == 0){
			mAnimation.push_back(new CAnimation(model));
			//model->SkipNode();
		}
	}
#ifdef _DEBUG
	printf("AnimationSet:%s\n", mpName);
#endif

}

void CMesh::Init(CModelX*model){
	model->GetIntToken();
	if (!strchr(model->mToken, '{')){
		model->GetToken();

	}
	mVertexNum = model->GetIntToken();
	mpVertex = new CVector[mVertexNum];

	for (int i = 0; i < mVertexNum; i++){
		mpVertex[i].mX = model->GetFloatToken();
		mpVertex[i].mY = model->GetFloatToken();
		mpVertex[i].mZ = model->GetFloatToken();
	}
	mFaceNum = model->GetFloatToken();	//画数読み込み
	//頂点数は1面に3頂点
	mpVertexIndex = new int[mFaceNum * 3];
	for (int i = 0; i < mFaceNum * 3; i += 3){
		model->GetToken();	//頂点読み飛ばし
		mpVertexIndex[i] = model->GetIntToken();
		mpVertexIndex[i + 1] = model->GetIntToken();
		mpVertexIndex[i + 2] = model->GetIntToken();
	}
	while (model->mpPointer != '\0'){
		model->GetToken();
		if (strchr(model->mToken, '}'))
			break;

		else if (strcmp(model->mToken, "MeshMaterialList") == 0){
			model->GetToken();
			mMaterialNum = model->GetIntToken();
			mMaterialIndexNum = model->GetIntToken();
			//マテリアルインデックスの作成
			mpMaterialIndex = new int[mMaterialIndexNum];
			for (int i = 0; i < mMaterialIndexNum; i++){
				mpMaterialIndex[i] = model->GetIntToken();
			}
			for (int i = 0; i < mMaterialNum; i++){
				model->GetToken();
				if (strcmp(model->mToken, "Material") == 0){
					mMaterial.push_back(new CMaterial(model));
				}
			}
			model->GetToken();
		}

		if (strcmp(model->mToken, "MeshNormals") == 0){
			model->GetToken();
			mNormalNum = model->GetIntToken();
			CVector *pNormal = new CVector[mNormalNum];
			for (int i = 0; i < mNormalNum; i++){
				pNormal[i].mX = model->GetFloatToken();
				pNormal[i].mY = model->GetFloatToken();
				pNormal[i].mZ = model->GetFloatToken();
			}

			mNormalNum = model->GetIntToken() * 3;
			int ni;
			mpNormal = new CVector[mNormalNum];
			for (int i = 0; i < mNormalNum; i += 3)
			{
				model->GetToken();
				ni = model->GetIntToken();
				mpNormal[i] = pNormal[ni];

				ni = model->GetIntToken();
				mpNormal[i + 1] = pNormal[ni];

				ni = model->GetIntToken();
				mpNormal[i + 2] = pNormal[ni];
			}
			delete[] pNormal;
			model->GetToken();
		}
		else if (strcmp(model->mToken, "SkinWeights") == 0){
			mSkinWeights.push_back(new CSkinWeights(model));
		}
		else{
			model->SkipNode();
		}
		printf("NormalNum:%d\n", mNormalNum);
		for (int i = 0; i < mNormalNum; i++)
		{
			printf("%f	", mpNormal[i].mX);
			printf("%f	", mpNormal[i].mY);
			printf("%f\n", mpNormal[i].mZ);
		}
	}

	
		/*else if (strcmp(model->mToken, "MeshMaterialList") == 0){
			model->GetToken();
			mMaterialNum = model->GetIntToken();
			mMaterialIndexNum = model->GetIntToken();
			//マテリアルインデックスの作成
			mpMaterialIndex = new int[mMaterialIndexNum];
			for (int i = 0; i < mMaterialIndexNum; i++){
				mpMaterialIndex[i]model->GetIntToken();
			}
			for (int i = 0; i < mMaterialNum; i++){
				model->GetToken();
				if (strcmp(model->mToken, "Material") == 0){
					mMaterial.push_back(new CMaterial(model));
				}
			}
			model->GetToken();
		}*/
	}



void CModelX::Load(char*file){
	//ファイルサイズ取得
	FILE*fp;	//ファイルポインタ変数の作成
	fp = fopen(file, "rb");	//ファイルオープン

	if (fp == NULL){	//エラーチェック
		printf("fopem error:%s\n", file);
		return;
	}

	//ファイルの最後に移動
	fseek(fp, 0L, SEEK_END);
	//ファイルサイズの取得
	int size = ftell(fp);
	//ファイルサイズ+バイト分の領域を確保
	char*buf = mpPointer = new char[size + 1];

	//ファイルの戦闘に移動
	fseek(fp, 0L, SEEK_SET);
	//確保した領域にファイルサイズ分のデータを読み込む
	fread(buf, size, 1, fp);
	//最期に\0を設定する
	buf[size] = '\0';
	fclose(fp);

	while (*mpPointer != '\0'){
		GetToken();
		if (strcmp(mToken, "Frame") == 0){
			new CModelXFrame(this);
		}
		else if (strcmp(mToken, "AnimationSet") == 0){
			new CAnimationSet(this);
		}
		/*
		if (strcmp(mToken,"AnimationSet") == 0){
		printf("%s", mToken);
		GetToken();
		printf("%s\n", mToken);
		}
		}*/
	}
		SAFE_DELETE_ARRAY(buf);
}


void CModelX::GetToken(){
	char* p = mpPointer;
	char* q = mToken;
	while (*p != '\0'&& strchr(" \t\r\n,;\"", *p))p++;
	if (*p == '{' || *p == '}'){
		*q++ = *p++;
	}
	else{
		while (*p != '\0'&& !strchr(" \t\r\n,;\"}", *p))
			*q++ = *p++;
	}
	*q = '\0';
	mpPointer = p;

	if (!strcmp("//", mToken)){
		while (*p != '\0'&& !strchr("\r\n", *p))p++;
		mpPointer = p;
		GetToken();
	}
}

void CModelX::SkipNode(){
	while (*mpPointer != '\0'){
		GetToken();
		if (strchr(mToken, '{'))break;
	}
	int count = 1;
	while (*mpPointer != '\0'&&count > 0){
		GetToken();
		if (strchr(mToken,'{'))count++;
		else if (strchr(mToken, '}'))count--;
	}
}

CModelXFrame::CModelXFrame(CModelX*model){
	//現在のフレーム配列ん要素数を取得し設定する
	mIndex = model->mFrame.size();
	//CModelXのフレーム配列に追加する
	model->mFrame.push_back(this);
	//変換行列を単位行列にする
	mTransformMatrix.Identity();
	//次の単語を取得する
	model->GetToken();
	//フレーム名分エリアを確保する
	mpName = new char[strlen(model->mToken) + 1];
	//フレーム名のコピー
	strcpy(mpName, model->mToken);
	//次の単語の取得
	model->GetToken();

	//文字がなくなったら終わり
	while (*model->mpPointer != '\0'){
		model->GetToken();
		if (strchr(model->mToken, '}'))break;
		if (strcmp(model->mToken, "Frame") == 0){
			mChild.push_back(
				new CModelXFrame(model));
		}
		else if (strcmp(model->mToken, "FrameTransformMatrix") == 0){
			model->GetToken();
			for (int i = 0; i < ARRAY_SIZE(mTransformMatrix.mF); i++){
				mTransformMatrix.mF[i] = model->GetFloatToken();
			}
			model->GetToken();
		}
		else if (strcmp(model->mToken, "Mesh") == 0){
			mMesh.Init(model);
		}
		else{
			model->SkipNode();
		}
	}
#ifdef _DEBUG
	//printf("%s\n", mpName);
	//mTransformMatrix.Print();
#endif
}

float CModelX::GetFloatToken(){
	GetToken();
	return atof(mToken);
}

void CMesh::Render(){
	//頂点データ、法線データの配列を有効にする
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	//頂点データ、法線データの場所を指定する
	glVertexPointer(3, GL_FLOAT, 0, mpVertex);
	glNormalPointer(GL_FLOAT, 0, mpNormal);
	//頂点のインデックスの場所を指定して図形を描写する
	for (int i = 0; i < mFaceNum; i++){
		mMaterial[mpMaterialIndex[i]]->Enabled();
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (mpVertexIndex + i * 3));
	}
	//頂点データ、法線データの配列を無効にする
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

}

void CModelXFrame::Render(){
	if (mMesh.mFaceNum != 0)
		mMesh.Render();
}

void CModelX::Render(){
	for (int i = 0; i < mFrame.size(); i++){
		mFrame[i]->Render();
	}
}

CModelXFrame*CModelX::FindFreame(char*name){
	std::vector<CModelXFrame*>::iterator itr;
	for (itr = mFrame.begin(); itr != mFrame.end(); itr++){
		if (strcmp(name, (*itr)->mpName) == 0){
			return *itr;
		}
	}
	return NULL;
}