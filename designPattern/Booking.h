#pragma once
#include<string>
#include<vector>
#include<iostream>
#include"BaseClasses.h"
#include"TravelPlan.h"

//��Ʊ���ඨ��
class Ticket_officer :public DPObject
{
public:
	void Action()
	{
		std::cout << "Ticket_officer->Action" << std::endl;
	}
	std::string name;
	Ticket_officer(std::string in_name) { name = in_name; }
};
//����������
class Command :public DPObject
{
public:
	virtual void Execute() = 0;
	std::string instruction;
};

class ConcreteCommand : public Command
{
public:
	ConcreteCommand(Ticket_officer* pReceiver) : m_pReceiver(pReceiver) {}
	void Execute()
	{
		m_pReceiver->Action();
	}
private:
	Ticket_officer* m_pReceiver;
};


class AbstractBookingFactory : public DPObject {
public:
	virtual Ticket_officer* make_Ticket_officer() = 0;
	virtual ConcreteCommand* make_ConcreteCommand() = 0;
	virtual Description* makeDescription() = 0;
	virtual Spot* makeSpot() = 0;
};
