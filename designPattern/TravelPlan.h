#pragma once
#include<string>
#include"BaseClasses.h"
/************************************************************************
*								�����ƻ�ģ��								*
*************************************************************************/
//���������ÿһ���ƻ���������
struct Description: public DPObject {
public:
	std::string content;
};

//·��������һ��Ŀ��λ�õ���ǰĿ��λ�õķ�ʽ
struct Path: public DPObject {
public:
	std::string vehicle;
};

//���㣨ÿһ���ƻ��е�Ŀ��λ�ã�
typedef CommandReceiver Spot;

//�ƻ�
struct Plan: public DPObject {
public:
	Path* path;
	Description* description;
	Spot* spot;
	~Plan() {
		if (path != nullptr) { delete path; }
		if (description != nullptr) { delete description; }
	}

};

//����ƻ�����
class AbstractPlanFactory: public DPObject {
public:
	virtual Path* makePath() = 0;
	virtual Description* makeDescription() = 0;
	virtual Spot* makeSpot() = 0;
};


//�ƻ�������
class PlanBuilder : public DPObject {
public:
	virtual void buildPlan() = 0;
	virtual void buildPath() = 0;
	virtual void buildDescription(std::string str) = 0;
	virtual void buildSpot(CommandReceiver* commandReciver) = 0;
	virtual Plan* getMacroPlan() = 0;
};



