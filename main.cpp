#include"common.h"
#include"BookAVLTree.h"
#include"Node.h"
#include"UserLinkList.h"
ifstream inFile;
ofstream outFile;

int main() {
    inFile.open("UserData.txt", ios::in);
    UserLinKList userList(inFile);//��userData�ж�ȡ�û���Ϣ�������û���Ϣ������
    outFile.open("UserData.txt");
    userList.menu();//�����¼�˵�
    userList.save(outFile);
    outFile.close();
    cout << "�û���Ϣ�ѱ��棬�˳�����ϵͳ��" << endl;
    system("pause");
    inFile.open("BookData.txt", ios::in);
    AVLBookTree BookAVLTree(inFile);//��BookData�ж�ȡͼ����Ϣ������ͼ����Ϣƽ�������
    BookAVLTree.menu();//����ͼ�����ϵͳ�˵�
    outFile.open("BookData.txt");
    BookAVLTree.save(outFile);
    outFile.close();
    cout << "�ļ��ѱ��棬�˳�����ϵͳ��" << endl;
    return 0;
}