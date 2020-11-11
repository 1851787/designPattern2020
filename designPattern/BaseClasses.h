#pragma once
#include<string>
#include<vector>
#include<iostream>
/*������ϵ�ĸ���
* ��Ŀ�г��ֵ���������̳��Դ��࣬����Ϊ����
*/
class DPObject {};

/************************************************************************************
*																					*
*							CommandReciverָ�������								*
*																					*
*	��ģ��ĸ���ָ�����������һ�ö����������Ŀ�ж������MainReciverΪ���ڵ㣬��	*
*	MacroCommandReciver����������Ϊ��֧�ڵ㣬��CommandReciver����������ΪҶ�ӽڵ�	*
*************************************************************************************/

/*ָ��������������
* ��Ŀ�г��ֵ�����ָ������߾��̳��Դ���
* ���뱻���ز���ʹ�õĴ��麯��Ϊbool executeCommand(std::string cmd)
*/
class CommandReciver : public DPObject {
protected:
	/*ִ��ָ��
	* ���ղ���û�û�����cmd������cmd����ִ����Ӧ�Ĳ������ڲ�����cin
	* @param cmd �û������ָ������
	* @return bool ָ���ʽ�Ƿ���ȷ
	*/
	virtual bool executeCommand(std::string cmd) = 0;
	/*�Ƴ��ַ���ǰ�ո�
	* ����һ���ַ��������ã��Ƴ���ǰ���ո����޶���ո�ֱ�ӷ���
	* @param cmd ��������ַ���
	* @return void
	*/
	void removeBlank(std::string& cmd) {
		for (int i = 0; i < cmd.size(); i++) {
			if (cmd[i] != ' ') {
				cmd = cmd.substr(i);
				return;
			}
		}
	}
	/*ָ����Ƭ
	* ����һ���ַ��������ã����ݿո�ָ����Ϊ����ֵsubCmd������cmd�����֣���ָ��Ϊ�շ��ؿ��ַ���
	* @param cmd ��Ƭǰ����Ƭ���ַ���/��Ƭ��ո����ַ���
	* @return std::string ��Ƭ��ո�ǰ��֧����
	*/
	std::string sliceCommand(std::string& cmd) {
		std::string subCmd = "";
		for (int i = 0; i < cmd.size(); i++) {
			if (cmd[i] == ' ') {
				subCmd = cmd.substr(0, i);
				cmd = cmd.substr(i);
				return subCmd;
			}
		}
		subCmd = cmd;
		cmd = "";
		return subCmd;
	}
public:
	//��ǩ������ǰCommandReciver��Ψһ��ʶ��
	std::string tag;
	/*��ӡ����ָ��
	* ����level��ӡ��Ӧ��ʽ��ָ�Ĭ�ϴ�ӡtag
	* @param level ��ǰReciver��Reciver���еĲ㼶
	* @return void
	*/
	virtual void printHelp(int level) {
		std::string head(level * 3, '-');
		std::cout << head + tag << std::endl;
	}
	/*����ָ��
	* ��ǰReciver�յ���ָ�����Ƚ���������д���Ĭ�ϴ���ʽ���Ƴ�ָ��ǰ�ո�
	* @param cmd �û������ָ������
	* @return void
	*/
	virtual void handleCommand(std::string cmd) {
		removeBlank(cmd);
		if (!executeCommand(cmd)) {
			std::cout << "��Чָ�����������ָ���ʽ" << std::endl;
			std::cout << "���һ����Чָ���µĿ���ָ��Ϊ��" << std::endl;
			printHelp(0);
		}
	}
	/*���캯��
	* ���캯����Ҫtag��ΪΨһ��ʶ��
	* @param tag_in ��ǩ
	* @return void
	*/
	CommandReciver(std::string tag_in) {
		tag = tag_in;
	}
};
/*��ָ��������������
* �̳���ָ�������������࣬�ڲ�ά��һ��vector�����ӽ�����
*/
class MacroCommandReciver : public CommandReciver {
private:
	//�ӽ������б�
	std::vector<CommandReciver*> reciverList;
	/*������ָ��
	* ������ָ���д�ƥ���tag������tagƥ���ӽ�������������ָ���ӽ�������ָ��
	* @param subCmd ��ƥ��ı�ǩ
	* @return CommandReciver* ָ���ӽ�������ָ�루������Ӧ�ӽ���������nullptr��
	*/
	CommandReciver* resolveSubCommand(std::string& subCmd) {
		for (std::vector<CommandReciver*>::iterator i = reciverList.begin(); i != reciverList.end(); i++) {
			if (subCmd == (*i)->tag) {
				return (*i);
			}
		}
		return nullptr;
	}
public:
	/*���캯��
	* ���캯����Ҫtag��ΪΨһ��ʶ��
	* @param tag_in ��ǩ
	* @return void
	*/
	MacroCommandReciver(std::string tag_in) : CommandReciver(tag_in) {};
	/*��ӡ����ָ��
	* ����level��ӡ��Ӧ��ʽ��ָ�Ĭ���ȴ�ӡtag���ٵݹ�����ӽ�������printHelp������VLR
	* @param level ��ǰReciver��Reciver���еĲ㼶
	* @return void
	*/
	virtual void printHelp(int level) {
		std::string head(level * 3, '-');
		std::cout << head + tag << std::endl;
		level++;
		for (int i = 0; i < reciverList.size(); i++) {
			reciverList[i]->printHelp(level);
		}
	}
	/*����ӽ�����
	* ����ά��reciverList�����Ѵ���ͬtag�ӽ����������ʧ�ܣ�������ӵ��б�β
	* @param p_reciver ָ�����ӵ��ӽ�������ָ��
	* @return bool �Ƿ���ӳɹ�
	*/
	virtual bool addReciver(CommandReciver* p_reciver) {
		for (std::vector<CommandReciver*>::iterator i = reciverList.begin(); i != reciverList.end(); i++) {
			if (tag == (*i)->tag) {
				return false;
			}
		}
		reciverList.push_back(p_reciver);
		return true;
	}
	/*�Ƴ��ӽ�����
	* ����ά��reciverList�����Ѵ���ͬtag�ӽ��������Ƴ�������ʧ��
	* @param tag ���Ƴ����ӽ������ı�ǩ
	* @return bool �Ƿ���ӳɹ�
	*/
	virtual bool removeReciver(std::string tag) {
		for (std::vector<CommandReciver*>::iterator i = reciverList.begin(); i != reciverList.end(); i++) {
			if (tag == (*i)->tag) {
				reciverList.erase(i);
				return true;
			}
		}
		return false;
	}
	/*�Ƴ��ӽ�����
	* ����ά��reciverList�����Ѵ���ͬtag�ӽ��������Ƴ�������ʧ��
	* @param p_reciver ָ����Ƴ����ӽ�������ָ��
	* @return bool �Ƿ���ӳɹ�
	*/
	virtual bool removeReciver(CommandReciver* reciver) { return removeReciver(reciver->tag); }
	/*����ָ��
	* ��ǰReciver�յ���ָ�����Ƚ���������д���Ĭ�ϴ���ʽ��ƥ���ӽ���������ƥ��ʧ����ִ��ָ��
	* @param cmd �û������ָ������
	* @return void
	*/
	virtual void handleCommand(std::string cmd) {
		removeBlank(cmd);
		std::string subCmd = sliceCommand(cmd);
		CommandReciver* childReciver = resolveSubCommand(subCmd);
		if (childReciver == nullptr) {
			if (!executeCommand(subCmd + cmd)) {
				std::cout << "��Чָ�����������ָ���ʽ" << std::endl;
				std::cout << "���һ����Чָ���µĿ���ָ��Ϊ��" << std::endl;
				printHelp(0);
			}
		}
		else {
			childReciver->handleCommand(cmd);
		}
	}
};