#ifndef USERLINKLIST_H
#define USERLINKLIST_H
/*
 *  @inFile    useLinkList.h
 *  @brief   存储用户链表类
 *  @author  LinK_Z
 *  @date    2023/12/22
 *  @version V1.0
 */
#include "common.h"
#include "Node.h"

 /*类声明*/
class UserLinKList
{
	/*********************************************************************
	* 私有成员变量
	* head     单链表头结点
	*
	* 私有成员函数：
	* bool finduser(userInfo user)					//在用户数据链表查找用户名 
	*
	* 构造函数:UserLinKList()

	* 析构函数:~UserLinKList();
	*
	* 公有成员函数:
	*********************************************************************/
private:
	UserLinkNode* head;							  //用户链表头结点
	bool checkInfo(string usr, string idx);		  //账号信息校验函数(仅供内部调用)
	int  login();								  //登录账号函数
	int  signup();								  //注册账号函数
	int  updatePassword();						  //重置密码函数
	int  Deletuser();							  //注销账号函数
public:
	~UserLinKList();								//释放链表
	UserLinKList(ifstream& inFile);					//用文件初始化链表

	void addUser(userInfo user);
	bool deleteUser(string username);
	bool findUser(string username, userInfo& user);

	void menu();								  //登录菜单函数
	void save(ofstream& outFile);				  //封装过的保存用户信息函数(外部调用)
};
#endif //USERLINKLIST_H
