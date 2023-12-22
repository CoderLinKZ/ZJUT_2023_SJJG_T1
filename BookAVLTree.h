/*
 *  @file    BookAVLTree.h
 *  @brief   存储图书信息链表类
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
   * 私有成员变量
   * root    根节点
   * depth   二叉树的深度
   * sign    操作是否成功标志位
   *
   * 构造函数:AVLBookTree(ifstream& inFile);
   *
   * 析构函数:~AVLBookTree();
   *
   * 私有成员函数:
   *       void printAVL(AVLNode* node, int sign = 0);                        打印二叉树
   *       void deleteNode(AVLNode* node, string usn, AVLNode* p = nullptr);     删除结点
   *       void add(AVLNode* T, AVLNode* newNode, AVLNode* parent = nullptr);       添加结点
   *       void updatePassword(string usn, string pwd, AVLNode* T);           更新密码
   *       void login(string usn, string pwd, AVLNode* T);                    登录
   *       void save(ofstream& outFile, AVLNode* T);                          将图书信息存入文件
   * 公共成员函数:
   *       void save(ofstream& outFile);                                      将图书信息存入文件(外部调用)
   *       void print();                                                      封装后的打印函数
   *       bool getSign();                                                    判断操作是否成功
   *       void reSign();                                                     重置标志
   *       int  getHeight(AVLNode* T);                                        获取树的高度
   *       void deleteNode(string usn);                                       封装后的删除结点函数
   *       void add(string usn, string pwd);                                  封装后的添加结点函数
   *       void RRotate(AVLNode* node, AVLNode* parent);                         右旋
   *       void LRotate(AVLNode* node, AVLNode* parent);                         左旋
   *********************************************************************/
private:
    AVLNode* root = nullptr;  //指向树根
    int depth = 0;  //二叉树的深度
    bool sign = false;  //记录操作是否成功

    // 一个数组，打印用，数组长度不低于二叉树的高度，设为一百
    // 标记当前的节点是父节点的左孩子还是右孩子
    int vec_left[100] = { 0 };

    void printAVL(AVLNode* node, int sign = 0);  //打印二叉树
    
    void add(AVLNode* T, AVLNode* newNode, AVLNode* parent = nullptr);  //添加结点(内部调用)
    void deleteNode(AVLNode* node, string num, AVLNode* p = nullptr);   //根据结点编号删除结点(内部调用)
    void save(ofstream& outFile, AVLNode* T);//将图书信息存入文件

public:
    AVLBookTree(ifstream& inFile);  //使用文件对象初始化二叉树
    ~AVLBookTree();  //二叉树的释放

    void menu();
    void save(ofstream& outFile);  //封装后的写入函数(供外部调用)
    void print();  //封装后的打印函数(供外部调用)

    bool getSign();  //判断操作是否成功
    void reSign();  //重置标志

    void add(string name, string num, int state, int borrow);  //封装后的添加结点函数
    void updataInfo(string num);                               //根据编号更新图书状态
    void deleteNode(string num);                               //封装后的删除结点函数
    int getHeight(AVLNode* T);                                 //获取树的高度
   
    void RRotate(AVLNode* node, AVLNode* parent);  //右旋
    void LRotate(AVLNode* node, AVLNode* parent);  //左旋
};


#endif //BOOKAVLTREE_H
