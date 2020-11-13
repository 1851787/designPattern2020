#pragma once
#include <iostream>
#include"BaseClasses.h"
#include"TravelPlan.h"
using namespace std;
#define  free_ptr(p) \
	if(p) delete p; p = NULL;//�ͷ�ָ��
/*
����ģʽ������Զ�̬�ĸı�������Ϊ����̬�޸Ĳ���
*/
//����������ɽ
class Mountaineering : public DPObject
{
public:
	virtual ~Mountaineering() {};
	virtual void choose() = 0;
};
//����ģʽ
class Walking : public Mountaineering {
public:
	void choose() {
		std::cout << "You have chose the walking strategy" << std::endl;
	};
};
//�³�ģʽ
class Cable_car : public Mountaineering {
public:
	void choose() {
		std::cout << "You have chose the Cable car strategy" << std::endl;
	};
};
//С��ģʽ
class Puddle_jumper : public Mountaineering {
public:
	void choose() {
		std::cout << "You have chose the puddle_jumper strategy" << std::endl;
	};
};
//��ɽ������
class MountainMode : public DPObject {
public:
	MountainMode(Mountaineering* mountain) : m_mountain(mountain) {};
	~MountainMode() { free_ptr(m_mountain); }
	void choose() {
		m_mountain->choose();
	};
private:
	Mountaineering* m_mountain;
};


class Mountain : public CommandReceiver {
private:
	//��¼���ַ���
	std::string str;
	/*���캯��
	* ���캯��Ϊprivate������ʵ�ֵ�����tagΪ"choose"
	* @return void
	*/
	Mountain() : CommandReceiver("mountain") {}
protected:
	/*ִ��ָ��
	* ���ظ���ִ��ָ��Ĵ��麯�����������������ִ����Ӧ����
	* @param cmd �û������ָ������
	* @return bool ָ���ʽ�Ƿ���ȷ
	*/
	bool executeCommand(std::string cmd) {
		std::string subCmd = sliceCommand(cmd);
		removeBlank(cmd);
		if (subCmd == "choose") {
			int ord = 0;
			std::cout << "��ӭ������ɽ��ѡһ����ɽ�ķ�ʽ�ɣ�(�������Ӧ���.)" << std::endl;
			std::cout << "1.11·������ɽ	2.���³���ɽ	3.�ﻶ���С����ɽŶ~" << std::endl;
			std::cin >> ord;
			getchar();
			switch (ord) {
			case 1: {
				MountainMode* walk = new MountainMode(new Walking());
				walk->choose();
				free_ptr(walk);
			}break;
			case 2: {
				MountainMode* cable_car = new MountainMode(new Cable_car());
				cable_car->choose();
				free_ptr(cable_car);
			}break;
			case 3: {
				MountainMode* puddle_jumper = new MountainMode(new Puddle_jumper());
				puddle_jumper->choose();
				free_ptr(puddle_jumper);
			}break;
			default:
			{
				std::cout << "Sorry���������˴���ı������ͷ������" << std::endl;
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
		std::cout << head + "choose" << std::endl;	//�����ָ��
	}
public:
	//��Ǹ��ƹ��캯��Ϊɾ��������ʵ�ֵ���
	Mountain(const Mountain&) = delete;
	//��ǿ�����ֵ������Ϊɾ��������ʵ�ֵ���
	Mountain& operator=(const Mountain&) = delete;
	/*��ȡ��ǰ������������
	* ��ȡȫ��Ψһ��ǰ��������ʵ�������ã�����ʵ�ֵ�����
	* @return Mountain& ��ǰ������������
	*/
	static Mountain& getInstance() {
		static Mountain reciver;
		return reciver;
	}
};


class MountainPlanFactory : public AbstractPlanFactory {
public:
	/*����·��
	* @return Path* ���ɵ�·��
	*/
	Path* makePath() {
		Path* path = new Path();
		path->vehicle = "car";
		return path;
	}
	/*��������
	* @return Path* ���ɵ�����
	*/
	Description* makeDescription() {
		Description* des = new Description();
		des->content = "��ѩɽģ��ʵ���˲���ģʽ����������Strategy.h";
		return des;
	}
	/*����Ŀ��ص�
	* @return Path* ���ɵ�Ŀ��ص�
	*/
	Spot* makeSpot() {
		Spot& spot = Mountain::getInstance();
		return &spot;
	}
};
