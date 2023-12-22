#ifndef NODE_H
#define NODE_H
/*
 *  @inFile  Node.h
 *  @brief   �洢�û��������ͼ����Ϣƽ��������ͷ�ļ�
 *  @author  LinK_Z
 *  @date    2023/12/22
 *  @version V1.0
 */
#include "common.h"
using namespace std;

struct userInfo {//�û��������ͽṹ��
    string username;//�û���
    string password;//����
};

struct bookInfo {//ͼ���������ͽṹ��
    string bookname;    //ͼ������
    string booknum;     //ͼ����
    int bookstates;     //ͼ��״̬(1 - ��, 0 - �ɣ�
    int bookBorrow;     //ͼ�����״̬(1 - ����, 0 - �ڿ⣩
};

struct UserLinkNode	//�û�����������						        
{
    userInfo data;									//�����򣺴���û�����
    UserLinkNode* next;								//ָ������һ������ָ��
    UserLinkNode() :next(NULL) {}					//���캯��
    UserLinkNode(userInfo d) :data(d), next(NULL) {}//���ع��캯��
};

class AVLNode //����ͼ����Ϣ����ƽ���������
{
    /*********************************************************************
    * ˽�г�Ա����
    * bf       �ڵ�����
    * *lChild  ����ָ��
    * *rChild  �Һ���ָ��
    * user     �û���Ϣ
    *
    * ���캯��:AVLNode(string usn, string pwd);
    *
    * ��������:~AVLNode();
    *
    * ���г�Ա����:
    *         AVLNode* getLChild();                ��ȡ����
    *         AVLNode* getRChild();                ��ȡ�Һ���
    *         int getBF();                         ��ȡƽ������
    *         void setLChild(AVLNode* newNode);    �������
    *         void setRChild(AVLNode* newNode);    ����Һ���
    *********************************************************************/
private:
    int bf = 0;  //���ƽ������
    AVLNode* lChild = nullptr;//���Һ���ָ��
    AVLNode* rChild = nullptr;  
    bookInfo book;  //�û���Ϣ

public:
    AVLNode(string usn, string pwd, int state, int borrow);  //ͼ����Ϣƽ���������㹹�캯��

    bookInfo& getBook();              //��ȡ��ǰ���洢��ͼ����Ϣ
    AVLNode* getLChild();             //��ȡ����
    AVLNode* getRChild();             //��ȡ�Һ���
    int getBF();  //��ȡƽ������
    void setBf(int bf);  //����ƽ������
    void setLChild(AVLNode* newNode);  //�������
    void setRChild(AVLNode* newNode);  //����Һ���
    ~AVLNode();  //�ͷŽ��
};

#endif //AVL_NODE_H