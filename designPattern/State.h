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

class Context
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

class Storage {//�洢״̬��
public:
	int n_state = 0;//��ʼ״̬��Ϊ0�����ȴ�״̬
}storage;


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
			int ord;
			std::cout << "�������ڴ˲���������ؾ����ࣨ��ֹ�������ͬ���ؾߡ�����д��Ӧ���Ŷ~��" << std::endl;
			std::cout << "1.11·������		2.�³�		3.����˹С��" << std::endl;
			std::cin >> ord;
			getchar();
			switch (ord) {
			case 1: {
				Flyweight* pw = Fac.GetFlyWeight("W");//��ȡW��Ӧ��ģ�飬�൱���������б���̶����ִ����·�
				std::cout << "11·�������ѳɹ������ؾ߿⣡" << std::endl;
				std::cout << "��ǰ�ɹ�������ؾ�������:" << Fac.countN() << "��!" << std::endl;
				delete pw;
			}break;
			case 2: {
				Flyweight* pc = Fac.GetFlyWeight("C");//��ȡC��Ӧ��ģ��
				std::cout << "�³��ѳɹ������ؾ߿⣡" << std::endl;
				std::cout << "��ǰ�ɹ�������ؾ�������:" << Fac.countN() << "��!" << std::endl;
				delete pc;
			}break;
			case 3: {
				Flyweight* pp = Fac.GetFlyWeight("P");
				std::cout << "����˹С���ѳɹ������ؾ߿⣡" << std::endl;
				std::cout << "��ǰ�ɹ�������ؾ�������:" << Fac.countN() << "��!" << std::endl;
				delete pp;
			}break;
			default: {
				cout << "����ָ�����" << endl;
			}
			}
			return true;
		}
		else if (subCmd == "state") {
			int ord = 0;
			if (storage.n_state == 0)
			{
				std::cout << "��ǰ�ؾߵ�״̬Ϊ�ȴ�״̬��" << std::endl;
			}
			else if (storage.n_state == 1)
			{
				std::cout << "��ǰ�ؾߵ�״̬Ϊ����״̬��" << std::endl;
			}
			std::cout << "����������ؾ�״̬Ϊ�����밴1����Ϊ�ȴ��밴0." << std::endl;
			cin >> ord;
			getchar();
			switch (ord) {
			case 0: {
				Vehicle_State* wait = new Waiting();
				Context* pContext = new Context(wait);
				storage.n_state = 0;//��Ϊ�ȴ�״̬
				pContext->Request();
				delete wait;
				delete pContext;
			}break;
			case 1: {
				Vehicle_State* run = new Running();
				Context* pContext = new Context(run);
				storage.n_state = 1;//��Ϊ����״̬
				pContext->Request();
				delete run;
				delete pContext;
			}break;
			default: {
				cout << "����ָ�����" << endl;
			}
			}
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
