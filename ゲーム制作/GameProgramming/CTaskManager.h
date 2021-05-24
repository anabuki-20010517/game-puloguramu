#ifndef CTASKMANAGER_H
#define CTASKMANAGER_H
#include"CTask.h"
class CTaskManager{
private:
	//�^�X�N�}�l�[�W���[�̃C���X�^���X
	static CTaskManager*mpInstance;
protected:
	//�f�t�H���g�R���X�g���N�^
	CTaskManager();
public:
	//�C���X�^���X�̎擾
	static CTaskManager*Get();

	CTask mHead;//�擪�^�X�N
	CTask mTail;//�ŏI�^�X�N

	virtual~CTaskManager();
	//Add(�^�X�N�̃|�C���^)
	void Add(CTask*addTask);
	void Update();
	void Render();
	//���X�g����폜
	void Remove(CTask*task);
	void Delete();
	void TaskCollision();
};

#endif