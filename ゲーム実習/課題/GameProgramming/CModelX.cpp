#include"glut.h"
#include<stdio.h>
#include<string.h>
#include"CModelX.h"

int CModelX::GetIntToken(){
	GetToken();
	return atoi(mToken);
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
		mFaceNum = model->GetFloatToken();	//�搔�ǂݍ���
		//���_����1�ʂ�3���_
		mpVertexIndex = new int[mFaceNum * 3];
		for (int i = 0; i < mFaceNum * 3; i += 3){
			model->GetToken();	//���_�ǂݔ�΂�
			mpVertexIndex[i] = model->GetIntToken();
			mpVertexIndex[i + 1] = model->GetIntToken();
			mpVertexIndex[i + 2] = model->GetIntToken();
		}
		model->GetToken();
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
		printf("NormalNum:%d\n", mNormalNum);
		for (int i = 0; i < mNormalNum; i ++)
		{
			printf("%f	", mpNormal[i].mX);
			printf("%f	", mpNormal[i].mY);
			printf("%f\n", mpNormal[i].mZ);
		}
		/*
		printf("FaceNum:%d\n", mFaceNum);
		for (int i = 0; i < mFaceNum*3; i+=3)
		{
			printf("%d ", mpVertexIndex[i]);
			printf("%d ", mpVertexIndex[i+1]);
			printf("%d\n", mpVertexIndex[i+2]);
		}
		printf("VertexNum:%d\n", mVertexNum);
		for (int i = 0; i < mVertexNum; i++)
		{
			printf("%10f", mpVertex[i].mX);
			printf("%10f", mpVertex[i].mY);
			printf("%10f\n", mpVertex[i].mZ);
		}*/

	}


void CModelX::Load(char*file){
	//�t�@�C���T�C�Y�擾
	FILE*fp;	//�t�@�C���|�C���^�ϐ��̍쐬
	fp = fopen(file, "rb");	//�t�@�C���I�[�v��

	if (fp == NULL){	//�G���[�`�F�b�N
		printf("fopem error:%s\n", file);
		return;
	}

	//�t�@�C���̍Ō�Ɉړ�
	fseek(fp, 0L, SEEK_END);
	//�t�@�C���T�C�Y�̎擾
	int size = ftell(fp);
	//�t�@�C���T�C�Y+�o�C�g���̗̈���m��
	char*buf = mpPointer = new char[size + 1];

	//�t�@�C���̐퓬�Ɉړ�
	fseek(fp, 0L, SEEK_SET);
	//�m�ۂ����̈�Ƀt�@�C���T�C�Y���̃f�[�^��ǂݍ���
	fread(buf, size, 1, fp);
	//�Ŋ���\0��ݒ肷��
	buf[size] = '\0';
	fclose(fp);

	while (*mpPointer != '\0'){
		GetToken();
		if (strcmp(mToken, "Frame") == 0){
			new CModelXFrame(this);
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
	//���݂̃t���[���z���v�f�����擾���ݒ肷��
	mIndex = model->mFrame.size();
	//CModelX�̃t���[���z��ɒǉ�����
	model->mFrame.push_back(this);
	//�ϊ��s���P�ʍs��ɂ���
	mTransformMatrix.Identity();
	//���̒P����擾����
	model->GetToken();
	//�t���[�������G���A���m�ۂ���
	mpName = new char[strlen(model->mToken) + 1];
	//�t���[�����̃R�s�[
	strcpy(mpName, model->mToken);
	//���̒P��̎擾
	model->GetToken();

	//�������Ȃ��Ȃ�����I���
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