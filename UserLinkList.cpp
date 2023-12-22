#include "common.h"
#include "UserLinkList.h"

UserLinKList::UserLinKList(ifstream &inFile)
{
	string tempstr;		// 读取字符串
	UserLinkNode *temp; // 新结点指针

	if (inFile.is_open())
	{
		cout << "开始从UserData文件读入用户信息......" << endl;
		std::string line;
		while (getline(inFile, line))
		{
			std::istringstream iss(line);
			std::string username, password;

			if (getline(iss, username, '@') && getline(iss, password))
			{ // 利用输入流格式从文件中提取出用户名和密码
				userInfo user;
				user.username = username;
				user.password = password;
				addUser(user);
			}
		}
		inFile.close();
	}
	else
	{
		std::cerr << "打开UserData文件时发生错误：" << endl;
	}
}

UserLinKList::~UserLinKList() {
}

// 增加用户
void UserLinKList::addUser(userInfo user)
{
	UserLinkNode *newNode = new UserLinkNode(user);
	newNode->next = head;
	head = newNode;
}

// 删除用户
bool UserLinKList::deleteUser(string username)
{
	UserLinkNode *current = head;
	UserLinkNode *prev = NULL;

	while (current != NULL && current->data.username != username)
	{
		prev = current;
		current = current->next;
	}

	if (current == NULL)
	{
		return false; // 用户不存在，删除失败
	}
	else
	{
		if (prev == NULL)
		{
			head = current->next;
		}
		else
		{
			prev->next = current->next;
		}

		delete current;
		return true; // 删除成功
	}
}

// 按照字符串查找用户
bool UserLinKList::findUser(string username, userInfo &user)
{
	UserLinkNode *current = head;

	while (current != NULL && current->data.username != username)
	{
		current = current->next;
	}

	if (current == NULL)
	{
		return false; // 查找失败，返回
	}
	else
	{
		user = current->data; // 返回引用参数为查找到的信息结构体
		return true;		  // 查找成功返回查找到的节点
	}
}

bool UserLinKList::checkInfo(string usr, string pwd)
{
	userInfo user = {usr, pwd};
	userInfo idx = {usr, pwd};
	if (!findUser(usr, idx))
	{
		cout << "账号不存在，请重新检查后输入！" << endl;
		return false;
	}
	else
	{
		if (idx.password != pwd)
		{
			cout << "密码输入错误，请重新检查后输入！" << endl;
			return false;
		}
		else
			return true;
	}
}

void UserLinKList::menu()
{
	int op = -1;//操作选择标志位
	int num = -1;
	
	while (num != 0)
	{
		system("cls");
		cout << "--------用户登录系统--------\n\n";
		cout << "        0:退出\n\n";
		cout << "        1:用户登录\n";
		cout << "        2:用户注册\n";
		cout << "        3:用户密码修改\n";
		cout << "        4:用户注销\n";
		cout << "----------------------------\n\n";
		cout << "        请输入您的选择:";
		cin >> op;
		switch (op)
		{
		case 0:
			num = 0;
			break;
		case 1:
		{
			system("cls");
			cout << "----------登录----------\n\n";
			num = login();
			break;
		}
		case 2:
		{
			system("cls");
			string nName, nPwd;
			cout << "--------用户注册--------\n";
			signup();
			break;
		}
		case 3:
		{
			system("cls");
			cout << "--------用户密码修改--------\n\n";
			updatePassword();
			break;
		}
		case 4:
		{
			system("cls");
			cout << "--------用户注销--------\n";
			Deletuser();
			break;
		default:
			continue;
		}
		if (num == 0) {//说明需要退出菜单，保存用户信息文件，然后退出
			return;
		}
		}
	}
}

int UserLinKList::signup()
{
	string usn, pwd;
	cout << "输入0以返回上一步" << endl;
	cout << "请输入注册的账号:";
	cin >> usn;
	cout << endl;
	userInfo user = { usn, pwd }; // 创建新的用户信息结构体
	if (findUser(usn, user))
	{ // 在链表中查找账号是否已经注册过
		cout << "该账号已经注册过，请重新输入" << endl;
	}
	else
	{
		cout << "请输入账号的密码" << endl;
		cin >> pwd;
		addUser(user); // 未注册过添加到用户信息链表
		cout << "用户" << usn << "注册成功！" << endl;
	}
	return -1;
}

int UserLinKList::login()
{
	string usn, pwd;
	cout << "输入0以返回上一步" << endl;
	cout << "请输入账号：";
	cin >> usn;
	cout << endl;
	cout << "请输入密码：";
	cin >> pwd;

	if (usn == "root" && pwd == "root") {
		cout << "管理员，欢迎您使用图书信息管理系统！" << endl;
		return 0;
	}
	else {
		if (!checkInfo(usn, pwd))
		{
			cout << "或输入 back 以返回上一步" << endl;
		}
		else
		{
			cout << "用户" << usn << "欢迎您使用图书馆信息管理系统!" << endl;
			return 0;
		}
	}
	return -1; // 需要返回上一步
}

int UserLinKList::updatePassword()
{
	string usn, pwd;
	cout << "输入0以返回上一步" << endl;
	cout << "请输入需要修改的账号";
	cin >> usn;
	cout << endl;
	while (1) {
		cout << "输入0以返回上一步" << endl;
		cout << "请输入新账号的密码";
		cin >> pwd;
		cout << endl;
		if (!checkInfo(usn, pwd) || pwd == "0")
		{
			cout << "验证失败" << endl;
		}
		else
		{
			cout << "用户" << usn << "密码重置成功，即将返回上一级!" << endl;
		}
	}
	return -1; // 需要返回上一步
}

int UserLinKList::Deletuser()
{
	string usn, pwd;
	cout << "请输入需要删除的账号";
	cin >> usn;
	cout << endl;
	while (1) {
		cout << "输入0以返回上一步" << endl;
		cout << "为了确保安全请输入您的密码：";
		cin >> pwd;
		cout << endl;
		if (!checkInfo(usn, pwd) || pwd == "0")
		{
			cout << "验证失败" << endl;
		}
		else
		{
			cout << "用户" << usn << "密码重置成功，即将返回上一级!" << endl;
		}
	}
	return -1;
}

void UserLinKList::save(ofstream& outFile) {
	UserLinkNode* p = head;
	int cnt = 0;
	while (p != NULL) {
		if(cnt != 1)
			outFile << endl << endl << p->data.username << '@' << p->data.password;
		else if(cnt == 1)
			outFile  << endl << p->data.username << '@' << p->data.password;
		cnt ++;
		p = p->next;
	}
}

