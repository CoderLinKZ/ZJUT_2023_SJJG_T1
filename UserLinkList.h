#ifndef USERLINKLIST_H
#define USERLINKLIST_H
/*
 *  @inFile    useLinkList.h
 *  @brief   �洢�û�������
 *  @author  LinK_Z
 *  @date    2023/12/22
 *  @version V1.0
 */
#include "common.h"
#include "Node.h"

 /*������*/
class UserLinKList
{
	/*********************************************************************
	* ˽�г�Ա����
	* head     ������ͷ���
	*
	* ˽�г�Ա������
	* bool finduser(userInfo user)					//���û�������������û��� 
	*
	* ���캯��:UserLinKList()

	* ��������:~UserLinKList();
	*
	* ���г�Ա����:
	*********************************************************************/
private:
	UserLinkNode* head;							  //�û�����ͷ���
	bool checkInfo(string usr, string idx);		  //�˺���ϢУ�麯��(�����ڲ�����)
	int  login();								  //��¼�˺ź���
	int  signup();								  //ע���˺ź���
	int  updatePassword();						  //�������뺯��
	int  Deletuser();							  //ע���˺ź���
public:
	~UserLinKList();								//�ͷ�����
	UserLinKList(ifstream& inFile);					//���ļ���ʼ������

	void addUser(userInfo user);
	bool deleteUser(string username);
	bool findUser(string username, userInfo& user);

	void menu();								  //��¼�˵�����
	void save(ofstream& outFile);				  //��װ���ı����û���Ϣ����(�ⲿ����)
};
#endif //USERLINKLIST_H
