#include "common.h"
#include "UserLinkList.h"

UserLinKList::UserLinKList(ifstream &inFile)
{
	string tempstr;		// ��ȡ�ַ���
	UserLinkNode *temp; // �½��ָ��

	if (inFile.is_open())
	{
		cout << "��ʼ��UserData�ļ������û���Ϣ......" << endl;
		std::string line;
		while (getline(inFile, line))
		{
			std::istringstream iss(line);
			std::string username, password;

			if (getline(iss, username, '@') && getline(iss, password))
			{ // ������������ʽ���ļ�����ȡ���û���������
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
		std::cerr << "��UserData�ļ�ʱ��������" << endl;
	}
}

UserLinKList::~UserLinKList() {
}

// �����û�
void UserLinKList::addUser(userInfo user)
{
	UserLinkNode *newNode = new UserLinkNode(user);
	newNode->next = head;
	head = newNode;
}

// ɾ���û�
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
		return false; // �û������ڣ�ɾ��ʧ��
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
		return true; // ɾ���ɹ�
	}
}

// �����ַ��������û�
bool UserLinKList::findUser(string username, userInfo &user)
{
	UserLinkNode *current = head;

	while (current != NULL && current->data.username != username)
	{
		current = current->next;
	}

	if (current == NULL)
	{
		return false; // ����ʧ�ܣ�����
	}
	else
	{
		user = current->data; // �������ò���Ϊ���ҵ�����Ϣ�ṹ��
		return true;		  // ���ҳɹ����ز��ҵ��Ľڵ�
	}
}

bool UserLinKList::checkInfo(string usr, string pwd)
{
	userInfo user = {usr, pwd};
	userInfo idx = {usr, pwd};
	if (!findUser(usr, idx))
	{
		cout << "�˺Ų����ڣ������¼������룡" << endl;
		return false;
	}
	else
	{
		if (idx.password != pwd)
		{
			cout << "����������������¼������룡" << endl;
			return false;
		}
		else
			return true;
	}
}

void UserLinKList::menu()
{
	int op = -1;//����ѡ���־λ
	int num = -1;
	
	while (num != 0)
	{
		system("cls");
		cout << "--------�û���¼ϵͳ--------\n\n";
		cout << "        0:�˳�\n\n";
		cout << "        1:�û���¼\n";
		cout << "        2:�û�ע��\n";
		cout << "        3:�û������޸�\n";
		cout << "        4:�û�ע��\n";
		cout << "----------------------------\n\n";
		cout << "        ����������ѡ��:";
		cin >> op;
		switch (op)
		{
		case 0:
			num = 0;
			break;
		case 1:
		{
			system("cls");
			cout << "----------��¼----------\n\n";
			num = login();
			break;
		}
		case 2:
		{
			system("cls");
			string nName, nPwd;
			cout << "--------�û�ע��--------\n";
			signup();
			break;
		}
		case 3:
		{
			system("cls");
			cout << "--------�û������޸�--------\n\n";
			updatePassword();
			break;
		}
		case 4:
		{
			system("cls");
			cout << "--------�û�ע��--------\n";
			Deletuser();
			break;
		default:
			continue;
		}
		if (num == 0) {//˵����Ҫ�˳��˵��������û���Ϣ�ļ���Ȼ���˳�
			return;
		}
		}
	}
}

int UserLinKList::signup()
{
	string usn, pwd;
	cout << "����0�Է�����һ��" << endl;
	cout << "������ע����˺�:";
	cin >> usn;
	cout << endl;
	userInfo user = { usn, pwd }; // �����µ��û���Ϣ�ṹ��
	if (findUser(usn, user))
	{ // �������в����˺��Ƿ��Ѿ�ע���
		cout << "���˺��Ѿ�ע���������������" << endl;
	}
	else
	{
		cout << "�������˺ŵ�����" << endl;
		cin >> pwd;
		addUser(user); // δע�����ӵ��û���Ϣ����
		cout << "�û�" << usn << "ע��ɹ���" << endl;
	}
	return -1;
}

int UserLinKList::login()
{
	string usn, pwd;
	cout << "����0�Է�����һ��" << endl;
	cout << "�������˺ţ�";
	cin >> usn;
	cout << endl;
	cout << "���������룺";
	cin >> pwd;

	if (usn == "root" && pwd == "root") {
		cout << "����Ա����ӭ��ʹ��ͼ����Ϣ����ϵͳ��" << endl;
		return 0;
	}
	else {
		if (!checkInfo(usn, pwd))
		{
			cout << "������ back �Է�����һ��" << endl;
		}
		else
		{
			cout << "�û�" << usn << "��ӭ��ʹ��ͼ�����Ϣ����ϵͳ!" << endl;
			return 0;
		}
	}
	return -1; // ��Ҫ������һ��
}

int UserLinKList::updatePassword()
{
	string usn, pwd;
	cout << "����0�Է�����һ��" << endl;
	cout << "��������Ҫ�޸ĵ��˺�";
	cin >> usn;
	cout << endl;
	while (1) {
		cout << "����0�Է�����һ��" << endl;
		cout << "���������˺ŵ�����";
		cin >> pwd;
		cout << endl;
		if (!checkInfo(usn, pwd) || pwd == "0")
		{
			cout << "��֤ʧ��" << endl;
		}
		else
		{
			cout << "�û�" << usn << "�������óɹ�������������һ��!" << endl;
		}
	}
	return -1; // ��Ҫ������һ��
}

int UserLinKList::Deletuser()
{
	string usn, pwd;
	cout << "��������Ҫɾ�����˺�";
	cin >> usn;
	cout << endl;
	while (1) {
		cout << "����0�Է�����һ��" << endl;
		cout << "Ϊ��ȷ����ȫ�������������룺";
		cin >> pwd;
		cout << endl;
		if (!checkInfo(usn, pwd) || pwd == "0")
		{
			cout << "��֤ʧ��" << endl;
		}
		else
		{
			cout << "�û�" << usn << "�������óɹ�������������һ��!" << endl;
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

