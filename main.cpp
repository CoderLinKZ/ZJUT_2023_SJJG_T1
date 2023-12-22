#include"common.h"
#include"BookAVLTree.h"
#include"Node.h"
#include"UserLinkList.h"
ifstream inFile;
ofstream outFile;

int main() {
    inFile.open("UserData.txt", ios::in);
    UserLinKList userList(inFile);//从userData中读取用户信息，构建用户信息单链表
    outFile.open("UserData.txt");
    userList.menu();//进入登录菜单
    userList.save(outFile);
    outFile.close();
    cout << "用户信息已保存，退出管理系统！" << endl;
    system("pause");
    inFile.open("BookData.txt", ios::in);
    AVLBookTree BookAVLTree(inFile);//从BookData中读取图书信息，构建图书信息平衡二叉树
    BookAVLTree.menu();//进入图书管理系统菜单
    outFile.open("BookData.txt");
    BookAVLTree.save(outFile);
    outFile.close();
    cout << "文件已保存，退出管理系统！" << endl;
    return 0;
}