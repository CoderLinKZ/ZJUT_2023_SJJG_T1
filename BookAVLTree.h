/*
 *  @file    BookAVLTree.h
 *  @brief   �洢ͼ����Ϣ������
 *  @author  LinK_Z
 *  @date    2023/12/22
 *  @version V1.0
 */
#ifndef BOOKAVLTREE_H
#define BOOKAVLTREE_H
#include "common.h"
#include "Node.h"

class AVLBookTree {
    /*********************************************************************
   * ˽�г�Ա����
   * root    ���ڵ�
   * depth   �����������
   * sign    �����Ƿ�ɹ���־λ
   *
   * ���캯��:AVLBookTree(ifstream& inFile);
   *
   * ��������:~AVLBookTree();
   *
   * ˽�г�Ա����:
   *       void printAVL(AVLNode* node, int sign = 0);                        ��ӡ������
   *       void deleteNode(AVLNode* node, string usn, AVLNode* p = nullptr);     ɾ�����
   *       void add(AVLNode* T, AVLNode* newNode, AVLNode* parent = nullptr);       ��ӽ��
   *       void updatePassword(string usn, string pwd, AVLNode* T);           ��������
   *       void login(string usn, string pwd, AVLNode* T);                    ��¼
   *       void save(ofstream& outFile, AVLNode* T);                          ��ͼ����Ϣ�����ļ�
   * ������Ա����:
   *       void save(ofstream& outFile);                                      ��ͼ����Ϣ�����ļ�(�ⲿ����)
   *       void print();                                                      ��װ��Ĵ�ӡ����
   *       bool getSign();                                                    �жϲ����Ƿ�ɹ�
   *       void reSign();                                                     ���ñ�־
   *       int  getHeight(AVLNode* T);                                        ��ȡ���ĸ߶�
   *       void deleteNode(string usn);                                       ��װ���ɾ����㺯��
   *       void add(string usn, string pwd);                                  ��װ�����ӽ�㺯��
   *       void RRotate(AVLNode* node, AVLNode* parent);                         ����
   *       void LRotate(AVLNode* node, AVLNode* parent);                         ����
   *********************************************************************/
private:
    AVLNode* root = nullptr;  //ָ������
    int depth = 0;  //�����������
    bool sign = false;  //��¼�����Ƿ�ɹ�

    // һ�����飬��ӡ�ã����鳤�Ȳ����ڶ������ĸ߶ȣ���Ϊһ��
    // ��ǵ�ǰ�Ľڵ��Ǹ��ڵ�����ӻ����Һ���
    int vec_left[100] = { 0 };

    void printAVL(AVLNode* node, int sign = 0);  //��ӡ������
    
    void add(AVLNode* T, AVLNode* newNode, AVLNode* parent = nullptr);  //��ӽ��(�ڲ�����)
    void deleteNode(AVLNode* node, string num, AVLNode* p = nullptr);   //���ݽ����ɾ�����(�ڲ�����)
    void save(ofstream& outFile, AVLNode* T);//��ͼ����Ϣ�����ļ�

public:
    AVLBookTree(ifstream& inFile);  //ʹ���ļ������ʼ��������
    ~AVLBookTree();  //���������ͷ�

    void menu();
    void save(ofstream& outFile);  //��װ���д�뺯��(���ⲿ����)
    void print();  //��װ��Ĵ�ӡ����(���ⲿ����)

    bool getSign();  //�жϲ����Ƿ�ɹ�
    void reSign();  //���ñ�־

    void add(string name, string num, int state, int borrow);  //��װ�����ӽ�㺯��
    void updataInfo(string num);                               //���ݱ�Ÿ���ͼ��״̬
    void deleteNode(string num);                               //��װ���ɾ����㺯��
    int getHeight(AVLNode* T);                                 //��ȡ���ĸ߶�
   
    void RRotate(AVLNode* node, AVLNode* parent);  //����
    void LRotate(AVLNode* node, AVLNode* parent);  //����
};


#endif //BOOKAVLTREE_H
