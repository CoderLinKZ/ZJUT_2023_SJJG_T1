#ifndef NODE_H
#define NODE_H
/*
 *  @inFile  Node.h
 *  @brief   存储用户链表结点和图书信息平衡树结点的头文件
 *  @author  LinK_Z
 *  @date    2023/12/22
 *  @version V1.0
 */
#include "common.h"
using namespace std;

struct userInfo {//用户数据类型结构体
    string username;//用户名
    string password;//密码
};

struct bookInfo {//图书数据类型结构体
    string bookname;    //图书名称
    string booknum;     //图书编号
    int bookstates;     //图书状态(1 - 新, 0 - 旧）
    int bookBorrow;     //图书借阅状态(1 - 出借, 0 - 在库）
};

struct UserLinkNode	//用户链表结点类型						        
{
    userInfo data;									//数据域：存放用户数据
    UserLinkNode* next;								//指针域：下一个结点的指针
    UserLinkNode() :next(NULL) {}					//构造函数
    UserLinkNode(userInfo d) :data(d), next(NULL) {}//重载构造函数
};

class AVLNode //定义图书信息二叉平衡树结点类
{
    /*********************************************************************
    * 私有成员变量
    * bf       节点因子
    * *lChild  左孩子指针
    * *rChild  右孩子指针
    * user     用户信息
    *
    * 构造函数:AVLNode(string usn, string pwd);
    *
    * 析构函数:~AVLNode();
    *
    * 公有成员函数:
    *         AVLNode* getLChild();                获取左孩子
    *         AVLNode* getRChild();                获取右孩子
    *         int getBF();                         获取平衡因子
    *         void setLChild(AVLNode* newNode);    添加左孩子
    *         void setRChild(AVLNode* newNode);    添加右孩子
    *********************************************************************/
private:
    int bf = 0;  //结点平衡因子
    AVLNode* lChild = nullptr;//左右孩子指针
    AVLNode* rChild = nullptr;  
    bookInfo book;  //用户信息

public:
    AVLNode(string usn, string pwd, int state, int borrow);  //图书信息平衡二叉树结点构造函数

    bookInfo& getBook();              //获取当前结点存储的图书信息
    AVLNode* getLChild();             //获取左孩子
    AVLNode* getRChild();             //获取右孩子
    int getBF();  //获取平衡因子
    void setBf(int bf);  //设置平衡因子
    void setLChild(AVLNode* newNode);  //添加左孩子
    void setRChild(AVLNode* newNode);  //添加右孩子
    ~AVLNode();  //释放结点
};

#endif //AVL_NODE_H