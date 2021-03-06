#pragma once
#include "BaseClasses.h"
#include "Booking.h"
#include "caculate.h"
/************************************************************************************
*																					*
*							Booking预定票模块        								*
*																					*
*************************************************************************************/

class Booking :public DPObject
{
public:
	Ticket_officer* ticket_officer;
	ConcreteCommand* concreteCommand;
	Description_Booking* description;
	CommandReceiver* spot;

	Ticket_officer* make_Ticket_officer()
	{
		Ticket_officer* ticket_officer = new Ticket_officer("游乐园售票处");
		return ticket_officer;
	}
	ConcreteCommand* make_ConcreteCommand()
	{
		ConcreteCommand* concreteCommand = new ConcreteCommand(ticket_officer);
		return concreteCommand;
	}
	Description_Booking* makeDescription(std::string cmd) {
		Description_Booking* des = new Description_Booking();
		if (cmd == "man") 
		{
			des->content = "男士票";
			des->identifier = 1000;
		}
		if (cmd == "woman")
		{
			des->content = "女士票";
			des->identifier = 500;
		}
		if (cmd == "child")
		{
			des->content = "儿童票";
			des->identifier = 100;
		}
		return des;
	}

	~Booking()
	{
		if (ticket_officer != nullptr) { delete ticket_officer; }
		if (concreteCommand != nullptr) { delete concreteCommand; }
		if (description != nullptr) { delete description; }
	}
};

class Ticket_Buyer :public CommandReceiver
{
private:
	Ticket_Buyer() :CommandReceiver("booking") {}

	std::vector<Booking*> bookingList;

	void createBooking(std::string cmd)
	{
		Booking* book = new Booking();
		book->concreteCommand = book->make_ConcreteCommand();
		book->ticket_officer = book->make_Ticket_officer();
		book->description = book->makeDescription(cmd);
		bookingList.push_back(book);
	}
	std::string getDescription(int pos) {
		if (pos >= bookingList.size() || pos < 0) {
			return "尚未设置该位置的预订";
		}
		return bookingList[pos]->description->content;
	}
protected:
	bool executeCommand(std::string cmd)
	{
		std::string subCmd = sliceCommand(cmd);
		removeBlank(cmd);
		if (subCmd == "create") {
			if (cmd == "man") {
				createBooking(cmd);
				std::cout << "成功预定男士票" << std::endl;
				return true;
			}
			else if (cmd == "woman") {
				createBooking(cmd);
				std::cout << "成功预定女士票" << std::endl;
				return true;
			}
			else if (cmd == "child") {
				createBooking(cmd);
				std::cout << "成功预定儿童票" << std::endl;
				return true;
			}
			return false;
		}
		if (subCmd == "getDescription") {
			std::string paramTag1 = sliceCommand(cmd);		//通过切片子指令，获得第一个参数的标签
			removeBlank(cmd);								//移除多余空格
			if (paramTag1 == "-p") {
				int pos = std::stoi(cmd);
				std::cout << getDescription(pos) << std::endl;
				return true;
			}
			cmd = paramTag1 + " " + cmd;
		}
		if (subCmd == "getChain") {
			std::string paramTag1 = sliceCommand(cmd);		//责任链初步实现
			removeBlank(cmd);
			if (paramTag1 == "-p") {
				int pos = std::stoi(cmd);
				child_play(bookingList[pos]->description);
				woman_play(bookingList[pos]->description);
				man_play(bookingList[pos]->description);
				return true;
			}
			cmd = paramTag1 + " " + cmd;
		}
		if (subCmd == "sum")
		{
			int sum_ticket = 0;
			for (int i = 0; i < bookingList.size(); i++)
			{
				if (bookingList[i]->description->content == "男士票") sum_ticket += 30;
				if (bookingList[i]->description->content == "女士票") sum_ticket += 20;
				if (bookingList[i]->description->content == "儿童票") sum_ticket += 10;
			}
			std::cout << "预定的票总价为" << sum_ticket << std::endl;
			return true;
		}
		return false;
	}
	void child_play(Description_Booking* des)
	{
		if (des->identifier > 0 && des->identifier <= 300) std::cout << "儿童票在一级设施游玩" << std::endl;
	}
	void woman_play(Description_Booking* des)
	{
		if (des->identifier > 300 && des->identifier <= 800) std::cout << "女士票在二级设施游玩" << std::endl;
	}
	void man_play(Description_Booking* des)
	{
		if (des->identifier > 800) std::cout << "男士票在三级设施游玩" << std::endl;
	}
public:
	Ticket_Buyer(const Ticket_Buyer&) = delete;
	Ticket_Buyer& operator=(const Ticket_Buyer&) = delete;

	static Ticket_Buyer& getInstance()
	{
		static Ticket_Buyer reciver;
		return reciver;
	}
	virtual void printHelp(int level) {
		__super::printHelp(level);				//调用父类的默认printHelp函数，递归输出当前及子接收器的tag
		level++;								//将子指令显示到下一层
		std::string head(level * 3, '-');
		std::cout << head + "create" << std::endl;								//输出子指令
		std::cout << head + "---" + "man" << std::endl;					//输出子指令
		std::cout << head + "---" + "woman" << std::endl;					//输出子指令
		std::cout << head + "---" + "child" << std::endl;					//输出子指令
		std::cout << head + "getDescription -p:票在列表中的位置" << std::endl;//输出子指令
		std::cout << head + "sum 票价求和" << std::endl;//输出子指令
		std::cout << head + "getChain 获得责任链 -p:票在列表中的位置" << std::endl;//输出子指令
	}

	~Ticket_Buyer()
	{
		for (int i = 0; i < bookingList.size(); i++)
		{
			if (bookingList[i] != nullptr) {
				delete bookingList[i];
			}
		}
	}
};






