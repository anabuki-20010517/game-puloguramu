#ifndef CTASK_H
#define CTASK_H
class CTask{
public:
	CTask*mpNext;//���̃|�C���^
	CTask*mpPrev;//�O�̃|�C���^
	int mPriority; //�D��x
	bool mEnabled; //�L���t���O
	CTask()
		:mpNext(0), mpPrev(0), mPriority(0), mEnabled(true){}
	virtual ~CTask(){}
	virtual void Update(){}
	virtual void Render(){}
	virtual void TaskCollision(){}
};
#endif