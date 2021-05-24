#include"CTaskManager.h"

CTaskManager::CTaskManager()
{
	mHead.mpNext = &mTail;
	mTail.mpPrev = &mHead;
}
CTaskManager::~CTaskManager(){

}
void CTaskManager::Add(CTask*addTask){
	CTask*task = mHead.mpNext;

	//�D��x�̍������ɓ�������
	while (addTask->mPriority < task->mPriority)
	{
		task = task->mpNext;
	}
	//addTask�̎���task
	addTask->mpNext = task;
	//addTask�̑O��task�̑O��
	addTask->mpPrev = task->mpPrev;
	//addTask�̑O�̎���addTask��
	addTask->mpPrev->mpNext = addTask;
	//task�̑O��addTask��
	task->mpPrev = addTask;

}
void CTaskManager::Update(){
	CTask*task = mHead.mpNext;
	while (task->mpNext){
		task->Update();
		task = task->mpNext;
	}
	

	}

void CTaskManager::Render(){
	CTask*task = mHead.mpNext;
	while (task->mpNext){
		task->Render();
		task = task->mpNext;
	}
}
void CTaskManager::Remove(CTask*task){
	task->mpPrev->mpNext = task->mpNext;
	task->mpNext->mpPrev = task->mpPrev;

}
void CTaskManager::Delete(){
	CTask*task = mHead.mpNext;
	while (task->mpNext){
		CTask*del = task;
		task = task->mpNext;
		if (del->mEnabled == false){
			delete del;
		}

	}
}
CTaskManager*CTaskManager::mpInstance = 0;
CTaskManager*CTaskManager::Get()
{
	if (mpInstance == 0)
	{
		mpInstance = new CTaskManager();
	}
	return mpInstance;
}
void CTaskManager::TaskCollision()
{
	CTask*task = mHead.mpNext;
	while (task->mpNext){
		task->TaskCollision();
		task = task->mpNext;
	}
}