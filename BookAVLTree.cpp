//
// Created by Dylan on 2021/12/15.
//

#include "common.h"
#include "BookAVLTree.h"

AVLBookTree::AVLBookTree(ifstream& inFile) {
	string line;

	// ���ж�ȡ�ļ�����
	while (getline(inFile, line)) {
		// ʹ�� ������stringstream �ָ�ÿ������
		stringstream ss(line);
		string bookname, booknum;
		int bookstates, bookBorrow;

		// ��:Ϊ�ָ�����ȡÿ������
		getline(ss, bookname, ':');
		getline(ss, booknum, ':');
		ss >> bookstates;
		ss.ignore();  // ����:����
		ss >> bookBorrow;

		// ��ͼ����Ϣ��ӵ���������
		add(bookname, booknum, bookstates, bookBorrow);
	}
}

AVLBookTree::~AVLBookTree() {
}

void AVLBookTree::menu()
{
	int op = -1;//����ѡ���־λ
	int num = -1;

	while (num != 0)
	{
		system("cls");
		cout << "--------ͼ��ݹ���ϵͳ--------\n\n";
		cout << "        1:����ͼ����Ϣ\n";
		cout << "        2:�����ͼ��\n";//1
		cout << "        3:ɾ����ͼ��\n";//1
		cout << "        4:��ʾ��ǰͼ����Ϣ��\n";//1
		cout << "        0:�˳�\n\n";//1
		cout << "----------------------------\n\n";
		cout << "        ����������ѡ��:";
		cin >> op;
		switch (op)
		{
		case 0: {
			num = 0;
			break;
		}
		case 1:
		{
			string Num;
			system("cls");
			cout << "------����ͼ����Ϣ------\n\n";
			cout << "��������Ҫ���µ�ͼ���ţ�";
			cin >> Num;
			cout << endl;
			updataInfo(Num);
			system("pause");
			break;
		}
		case 2:
		{
			string Name, Num;
			int states, borrow;
			system("cls");
			cout << "-------�����ͼ��-------\n";
			cout << "������ͼ���ţ�";
			cin >> Num;
			cout << endl;
			cout << "������ͼ�����ƣ�";
			cin >> Name;
			cout << endl;
			cout << "������ͼ��״̬��" << endl << "0 - ����" << "1 - ����" << endl;
			cin >> states;
			cout << endl;
			cout << "������ͼ���Ƿ��ڹݣ�" << endl << "0 - ����" << "1 - �ڹ�" << endl;
			cin >> borrow;
			cout << endl;
			add(Name, Num, states, borrow);
			cout << '��' << Name << '��' << "˳������ӣ�" << endl;
			system("pause");
			break;
		}
		case 3:
		{
			string Num;
			system("cls");
			cout << "--------ɾ����ͼ��--------\n\n";
			cout << "��������Ҫɾ����ͼ���ţ�";
			cin >> Num;
			cout << endl;
			deleteNode(Num);
			system("pause");
			break;
		}
		case 4:
		{
			system("cls");
			cout << "----��ʾ��ǰͼ����Ϣ��---\n";
			cout << "���������������������ϣ�����������˳�����ͼ����Ϣ����" << endl;
			print();
			system("pause");
			break;
		default:
			continue;
		}
		if (num == 0) {
			return;
		}
		}
	}
}

void AVLBookTree::print() {  //��װ��Ĵ�ӡ����
	printAVL(root);
}
void AVLBookTree::printAVL(AVLNode* node, int sign)
{
	if (sign > 0) {  //�����ĸ߶ȴ���0ʱ
		for (int i = 0; i < sign - 1; i++) {
			printf(vec_left[i] ? "��   " : "    ");
		}
		printf(vec_left[sign - 1] ? "������ " : "������ ");
	}

	if (!node) {  //����㲻���ڵ�ʱ��
		printf("(null)\n");
		return;
	}

	// ��ӡ��ǰ���ͼ������
	cout << node->getBook().booknum << ' ' << node->getBook().bookname << ' ';
	if (node->getBook().bookstates == 0)
		cout << "����" << ' ';
	else
		cout << "����" << ' ';
	if (node->getBook().bookBorrow == 0)
		cout << "���ڿ�" << ' ';
	else
		cout << "�ڿ�" << ' ';
	cout << endl;
	//��ǰ���ΪҶ�ӽ��ʱ����
	if (!node->getLChild() && !node->getRChild()) {
		return;
	}

	vec_left[sign] = 1; //���뵱ǰ�����Һ���
	printAVL(node->getRChild(), sign + 1);
	vec_left[sign] = 0; //���뵱ǰ��������
	printAVL(node->getLChild(), sign + 1);

}

void AVLBookTree::add(string name, string num, int state, int borrow) {
	add(root, new AVLNode(name, num, state, borrow));
}

void AVLBookTree::add(AVLNode* T, AVLNode* newNode, AVLNode* parent) {  //��һ�������ǵ�ǰ����ַ�����ݹ��ã��ڶ����������½���ַ
	//AVL���ǿ���ʱ��ͷ�ڵ�ָ�����Ľ��
	if (root == nullptr) {
		root = newNode;
		//��ȡ�������
		depth = getHeight(root);
		sign = true;
		return;
	}


	//AVL��Ϊ��ʱ����ͼ������Ϊ�������������������
	if (T->getBook().booknum > newNode->getBook().booknum) {  //����ǰ���ֵ���½��ֵ����ת������
		if (T->getLChild() == nullptr) {
			T->setLChild(newNode);  //����Ϊ�գ�ֱ�����Ϊ����
			sign = true;
			//��ȡ�������
			depth = getHeight(root);
		}
		else add(T->getLChild(), newNode, T);  //���ӷǿգ�ת������
	}
	else if (T->getBook().booknum < newNode->getBook().booknum) {  //����ǰ���ֵ���½��ֵС����ת���Һ���
		if (T->getRChild() == nullptr) {
			T->setRChild(newNode);  //�Һ���Ϊ�գ�ֱ�����Ϊ�Һ���
			sign = true;
			//��ȡ�������
			depth = getHeight(root);
		}
		else add(T->getRChild(), newNode, T);  //�Һ��ӷǿգ�ת���Һ���
	}
	else {  //����ǰ���ֵ���½��ֵһ�����򷵻ش�����Ϣ
		cout << "ͼ��\"" << newNode->getBook().bookname << "\"�Ѵ��ڣ�" << endl;
		delete newNode;  //�ͷſռ�
		return;
	}

	//ƽ�����
	if (T->getBF() > 1) {  //�ҵ���С��ƽ������
		RRotate(T, parent);  //����
	}
	else if (T->getBF() < -1) {
		LRotate(T, parent);  //����
	}
}

void AVLBookTree::updataInfo(string num)
{
	AVLNode* T = root;
	while (T != NULL && num != T->getBook().booknum) {//������Ҫ�޸ĵ�ͼ����
		if (num < T->getBook().booknum)
			T = T->getLChild();//С�ھ����������ϲ���
		else
			T = T->getRChild();//���ھ����������ϲ���
	}
	if (T == NULL)
		cout << "ͼ����" << num << "�����ڣ����������룡";
	else {
		int flag = 1;//ÿһ��Ԫ���Ƿ���Ҫ�޸ı�־λ
		string idxs;//�ݴ���Ҫ�޸ĵ��ַ�����������
		cout << "�Ƿ��޸�ͼ�����ƣ�" << endl << "0 - ����Ҫ" << "1 - ��Ҫ" << endl;
		cin >> flag;
		if (flag == 1) {
			cin >> idxs;
			while (1) {
				cout << "�������µ�ͼ������";
				cin >> idxs;
				if (idxs == T->getBook().bookname) {
					cout << "��ԭ����һ�£��������޸�" << endl;
					continue;
				}
				else {
					T->getBook().bookname = idxs;
					cout << "�޸ĳɹ�!" << endl;
				}
			}
		}
		system("pause");
		cout << "�Ƿ��޸�ͼ���ڹ�״̬��" << endl << "0 - ����Ҫ" << "1 - ��Ҫ" << endl;
		cin >> flag;
		if (flag == 1) {
			T->getBook().bookBorrow = ~(T->getBook().bookBorrow);
			cout << "�޸ĳɹ�!" << endl;
		}

		cout << "�޸�ȫ����ɣ�׼��������һ���˵���" << endl;
	}
}
/*
 * ���ڻ�ȡ�������ʱ��Ҫ�õ�ÿ������������������
 * ���Կ���˳��������ǰ����ƽ������
 */
int AVLBookTree::getHeight(AVLNode* T) {  //ʹ�õݹ��ȡ�������
	if (T == nullptr) return 0;

	int left, right;  //��¼�����������

	left = getHeight(T->getLChild());  //��ǰ������������
	right = getHeight(T->getRChild());  //��ǰ������������
	T->setBf(left - right);  //�������ǰ����ƽ������

	return  max(left, right) + 1;  //ȡ���������������һ����Ϊ����ֵ
}

void AVLBookTree::deleteNode(string num) {
	deleteNode(root, num);
}
void AVLBookTree::deleteNode(AVLNode* node, string num, AVLNode* p) {
	if (node == nullptr) {
		//cout<<"empty node!"<<endl;
		return;
	}

	if (node->getBook().booknum == num) {  //����ǰ���ͼ���ż�Ϊ��Ѱ���ͼ����

		if (node->getRChild() && node->getLChild()) {//������������ӽ��

			AVLNode* temPreNode = node;  //ָ�������̽���˫�׽��
			AVLNode* temNode = node->getRChild();  //ָ�������̽��
			while (temNode->getLChild() != nullptr) {  //�����������������½��
				temPreNode = temNode;
				temNode = temNode->getLChild();
			}

			if (node->getRChild() != temNode) {  //�������̽�㲻��Ŀ������Һ���ʱ
				if (temNode->getRChild() != nullptr) {  //�������̽ڵ��Һ��Ӳ�Ϊ��
					temPreNode->setLChild(temNode->getRChild());  //�����̽����Һ��ӱ�Ϊǰһ����������
				}
				temNode->setRChild(node->getRChild());  //��ɾ�������Һ�����Ϊ�����̽ڵ���Һ���
				temPreNode->setLChild(nullptr);  //�����̽���˫�׽�������ÿ�
			}
			temNode->setLChild(node->getLChild());  //��ɾ������������Ϊ�����̽ڵ������

			if (p != nullptr) {
				if (p->getRChild() == node) {  //�ǽ����Һ���ʱ
					p->setRChild(temNode);  //�����̽ڵ���Ϊ˫�׽����Һ���
				}
				else if (p->getLChild() == node) {  //�ǽ�������ʱ
					p->setLChild(temNode);  //�����̽ڵ���Ϊ˫�׽�������
				}
			}
			else {
				root = temNode;
			}
			delete node;  //ɾ�������

		}
		else if (node->getRChild() && !node->getLChild()) {  //�����ǰ���ֻ���Һ���

			if (p == nullptr) {  //����Ŀ����Ϊ���ڵ������
				root = node->getRChild();  //���ø��ڵ�
				delete node;  //ɾ�����
			}
			else if (p->getLChild() == node) {  //��Ϊ���ڵ������
				p->setLChild(node->getRChild());
				delete node;  //ɾ�����
			}
			else if (p->getRChild() == node) {  //��Ϊ���ڵ���Һ���
				p->setRChild(node->getRChild());
				delete node;  //ɾ�����
			}

		}
		else if (!node->getRChild() && node->getLChild()) {  //�����ǰ���ֻ������

			if (p == nullptr) {  //����Ŀ����Ϊ���ڵ������
				root = node->getLChild();  //���ø��ڵ�
				delete node;  //ɾ�����
			}
			else if (p->getLChild() == node) {  //��Ϊ���ڵ������
				p->setLChild(node->getLChild());
				delete node;  //ɾ�����
			}
			else if (p->getRChild() == node) {  //��Ϊ���ڵ���Һ���
				p->setRChild(node->getLChild());
				delete node;  //ɾ�����
			}

		}
		else {  //��ΪҶ�ӽ�㣬��ֱ��ɾ��

			if (p == nullptr) {  //���Ŀ��Ϊ�����ĸ��ڵ㣬��ֱ��ɾ��
				delete node;
				root = nullptr;
			}
			else if (p->getLChild() == node) {  //��Ϊ���ڵ������
				delete node;  //ɾ�����
				p->setLChild(nullptr);  //���ڵ�����ָ���ÿ�
			}
			else if (p->getRChild() == node) {  //��Ϊ���ڵ���Һ���
				delete node;  //ɾ�����
				p->setRChild(nullptr);  //���ڵ��Һ���ָ���ÿ�
			}

		}
		node = nullptr;
		//���¼���߶�
		depth = getHeight(root);
		sign = true;
		return;
	}

	deleteNode(node->getLChild(), num, node);

	//ԭ���λ��ƽ�����
	while (node->getLChild() != nullptr && node->getLChild()->getBF() > 1) {
		RRotate(node, p);  //����
	}

	//����֧ɾ��ʱ���ϲ�ƽ�����
	if (node->getBF() > 1) {  //�ҵ���С��ƽ������
		RRotate(node, p);  //����
	}
	else if (node->getBF() < -1) {
		LRotate(node, p);  //����
	}

	deleteNode(node->getRChild(), num, node);

	//ԭ���λ��ƽ�����
	while (node->getRChild() != nullptr && node->getRChild()->getBF() > 1) {
		RRotate(node, p);  //����
	}

	//����֧ɾ��ʱ���ϲ�ƽ�����
	if (node->getBF() > 1) {  //�ҵ���С��ƽ������
		RRotate(node, p);  //����
	}
	else if (node->getBF() < -1) {
		LRotate(node, p);  //����
	}

}

void AVLBookTree::RRotate(AVLNode* node, AVLNode* parent) {
	if (node == root) {  //����С��ƽ�����������Ϊ���ڵ�
		if (node->getLChild()->getBF() < 0) {  //������Ų�ͬ�����ӽ���Ƚ�������
			LRotate(node->getLChild(), node);
		}
		AVLNode* temNode = root;
		root = root->getLChild();

		if (root->getRChild() == nullptr) {  //������ӽ��û���Һ���
			root->setRChild(temNode);
			temNode->setLChild(nullptr);
		}
		else {  //������ӽ�����Һ��ӣ��򽫺��ӽ����Һ����Ƶ�˫�׽������½�
			temNode->setLChild(root->getRChild());
			root->setRChild(temNode);

		}

	}
	else {  //����Ϊ���ڵ�
		if (node->getLChild()->getBF() < 0) {  //������Ų�ͬ�����ӽ���Ƚ�������
			if (parent->getLChild() == node) {  //��ߵ�������˫�׽�������
				LRotate(node->getLChild(), parent->getLChild());
			}
			else {  //�ұߵ�������˫�׽�����ұ�
				LRotate(node->getLChild(), parent->getRChild());
			}
		}

		//��ת����
		AVLNode* temNode = node;
		AVLNode* childNode = node->getLChild();

		if (parent->getLChild() == node) {  //��ߵ�����
			parent->setLChild(childNode);
		}
		else {  //�ұߵ�����
			parent->setRChild(childNode);
		}

		if (childNode->getRChild() == nullptr) {  //������ӽ��û���Һ���
			childNode->setRChild(temNode);
			temNode->setLChild(nullptr);
		}
		else {  //������ӽ�����Һ��ӽ�㣬�򽫺��ӽ����Һ����Ƶ�Ŀ��������½ǣ�������������
			temNode->setLChild(childNode->getRChild());
			childNode->setRChild(temNode);
		}

	}
	depth = getHeight(root);  //���¼���������Ⱥ�bf
}

void AVLBookTree::LRotate(AVLNode* node, AVLNode* parent) {
	if (node == root) {  //����С��ƽ�����������Ϊ���ڵ�
		if (node->getRChild()->getBF() > 0) {  //������Ų�ͬ�����ӽ���Ƚ�������
			RRotate(node->getRChild(), node);
		}
		AVLNode* temNode = root;
		root = root->getRChild();

		if (root->getLChild() == nullptr) {  //������ӽ��û������
			root->setLChild(temNode);
			temNode->setRChild(nullptr);
		}
		else {  //������ӽ�����������ӽ�㣬�򽫺��ӽ��������Ƶ�˫�׽������½�
			temNode->setRChild(root->getLChild());
			root->setLChild(temNode);
		}

	}
	else {  //����Ϊ���ڵ�
		if (node->getRChild()->getBF() > 0) {  //������Ų�ͬ�����ӽ���Ƚ�������
			if (parent->getLChild() == node) {  //��ߵ�������˫�׽�������
				RRotate(node->getRChild(), parent->getLChild());
			}
			else {  //�ұߵ�������˫�׽�����ұ�
				RRotate(node->getRChild(), parent->getRChild());
			}
		}
		//��ת����
		AVLNode* temNode = node;
		AVLNode* childNode = node->getRChild();

		if (parent->getLChild() == node) {  //��ߵ�����
			parent->setLChild(childNode);
		}
		else {  //�ұ�����
			parent->setRChild(childNode);
		}

		if (childNode->getLChild() == nullptr) {  //������ӽ��û������
			childNode->setLChild(temNode);
			temNode->setRChild(nullptr);
		}
		else {  //������ӽ�����������ӽ�㣬�򽫺��ӽ��������Ƶ�˫�׽������½�
			temNode->setRChild(childNode->getLChild());
			childNode->setLChild(temNode);
		}


	}
	depth = getHeight(root);  //���¼���������Ⱥ�bf
}

void AVLBookTree::save(ofstream& outFile) {
	save(outFile, root);
}

void AVLBookTree::save(ofstream& outFile, AVLNode* T) {
	if (T == nullptr) return;
	if (T == root) outFile << T->getBook().bookname << ':' << T->getBook().booknum << ':' << T->getBook().bookstates << ':' << T->getBook().bookBorrow;
	else outFile << endl << T->getBook().bookname << ':' << T->getBook().booknum << ':' << T->getBook().bookstates << ':' << T->getBook().bookBorrow;
	save(outFile, T->getLChild());
	save(outFile, T->getRChild());
}

bool AVLBookTree::getSign() {
	return sign;
}

void AVLBookTree::reSign() {
	sign = false;
}


