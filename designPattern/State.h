#pragma once
#include <iostream>
#include"BaseClasses.h"
#include"TravelPlan.h"
#include"Flyweight.h"
using namespace std;
//״̬ģʽʵ��
class Context;
//�ؾ�״̬
class Vehicle_State : public DPObject
{
public:
	virtual void Handle(Context* pContext) = 0;
};

class Waiting : public Vehicle_State
{
public:
	virtual void Handle(Context* pContext)
	{
		std::cout << "��ǰ�ؾ�Ϊ�ȴ�״̬��" << std::endl;
	}
};

class Running : public Vehicle_State
{
public:
	virtual void Handle(Context* pContext)
	{
		std::cout << "��ǰ�ؾ�Ϊ����״̬��" << std::endl;
	}
};

class Context : public DPObject
{
public:
	Context(Vehicle_State* pState) : m_pState(pState) {}

	void Request()
	{
		if (m_pState)
		{
			m_pState->Handle(this);
		}
	}

	void ChangeState(Vehicle_State* pState)
	{
		m_pState = pState;
	}

private:
	Vehicle_State* m_pState;
};


class Vehicle : public CommandReceiver {
private:
	//��¼���ַ���
	std::string str;
	/*���캯��
	* ���캯��Ϊprivate������ʵ�ֵ�����tagΪ"Vehicle"
	* @return void
	*/
	Vehicle() : CommandReceiver("vehicle") {}
protected:
	/*ִ��ָ��
	* ���ظ���ִ��ָ��Ĵ��麯�����������������ִ����Ӧ����
	* @param cmd �û������ָ������
	* @return bool ָ���ʽ�Ƿ���ȷ
	*/
	bool executeCommand(std::string cmd) {
		std::string subCmd = sliceCommand(cmd);
		removeBlank(cmd);
		if (subCmd == "all") {
			FlyweightFactory Fac;//��������ֵ����һ������
			Flyweight* pw = Fac.GetFlyWeight("W");//��ȡW��Ӧ��ģ�飬�൱���������б���̶����ִ����·�
			Flyweight* pc = Fac.GetFlyWeight("C");//��ȡC��Ӧ��ģ��
			Flyweight* pp = Fac.GetFlyWeight("P");
			std::cout << "��ǰ�ɹ������ģ����:" << Fac.countN() << "��!" << std::endl;
			delete pw;
			delete pc;
			delete pp;
			return true;
		}
		else if (subCmd == "state") {
			int ord = 0;
			Vehicle_State* wait = new Waiting();
			Context* pContext = new Context(wait);
			pContext->Request();
			std::cout << "�������ı�״̬Ϊ�����밴1" << std::endl;
			cin >> ord;
			getchar();
			if (ord == 1)
			{
				Vehicle_State* run = new Running();
				pContext->ChangeState(run);
				pContext->Request();
				delete run;
			}
			delete wait;
			delete pContext;
			return true;
		}
		return false;
	}
	/*��ӡ����ָ��
	* ���ظ����麯��������level��ӡ��Ӧ��ʽ��ָ��Լ�������ָ��
	* @param level ��ǰReciver��Reciver���еĲ㼶
	* @return void
	*/
	virtual void printHelp(int level) {
		__super::printHelp(level);				//���ø����Ĭ��printHelp�������ݹ������ǰ���ӽ�������tag
		level++;								//����ָ����ʾ����һ��
		std::string head(level * 3, '-');
		std::cout << head + "all" << std::endl;	//�����ָ��
		std::cout << head + "state" << std::endl;
	}
public:
	//��Ǹ��ƹ��캯��Ϊɾ��������ʵ�ֵ���
	Vehicle(const Vehicle&) = delete;
	//��ǿ�����ֵ������Ϊɾ��������ʵ�ֵ���
	Vehicle& operator=(const Vehicle&) = delete;
	/*��ȡ��ǰ������������
	* ��ȡȫ��Ψһ��ǰ��������ʵ�������ã�����ʵ�ֵ�����
	* @return Mountain& ��ǰ������������
	*/
	static Vehicle& getInstance() {
		static Vehicle reciver;
		return reciver;
	}
};
