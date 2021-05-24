#include"CMaterial.h"
#include<string.h>
#include"glut.h"
CMaterial::CMaterial()
:mVertexNum(0)
{
	memset(mName, 0, sizeof(mName));
	memset(mDiffuse, 0, sizeof(mDiffuse));

}
void CMaterial::Enabled(){
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mDiffuse);
	if (mTexture.mId)
	{
		//�e�N�X�`�����g�p�\�ɂ���
		glEnable(GL_TEXTURE_2D);
		//�e�N�X�`�����o�C���h
		glBindTexture(GL_TEXTURE_2D, mTexture.mId);
		//����ӂ��ʘA�W��L����
		glEnable(GL_BLEND);
		//�u�����h���@���w��
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
}
//�}�e���A���𖳌��ɂ���
void CMaterial::Disabled(){

	if (mTexture.mId)
	{
		//�A���t�@�u�����h�𖳌�
		glDisable(GL_BLEND);
		//�e�N�X�`���̃o�C���h������
		glBindTexture(GL_TEXTURE_2D, 0);
		//�e�N�X�`������
		glDisable(GL_TEXTURE_2D);
	}
}
