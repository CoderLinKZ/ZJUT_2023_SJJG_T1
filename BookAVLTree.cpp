//
// Created by Dylan on 2021/12/15.
//

#include "common.h"
#include "BookAVLTree.h"

AVLBookTree::AVLBookTree(ifstream& inFile) {
	string line;

	// 逐行读取文件数据
	while (getline(inFile, line)) {
		// 使用 输入流stringstream 分割每行数据
		stringstream ss(line);
		string bookname, booknum;
		int bookstates, bookBorrow;

		// 以:为分隔符提取每个属性
		getline(ss, bookname, ':');
		getline(ss, booknum, ':');
		ss >> bookstates;
		ss.ignore();  // 忽略:符号
		ss >> bookBorrow;

		// 将图书信息添加到二叉树中
		add(bookname, booknum, bookstates, bookBorrow);
	}
}

AVLBookTree::~AVLBookTree() {
}

void AVLBookTree::menu()
{
	int op = -1;//操作选择标志位
	int num = -1;

	while (num != 0)
	{
		system("cls");
		cout << "--------图书馆管理系统--------\n\n";
		cout << "        1:更新图书信息\n";
		cout << "        2:添加新图书\n";//1
		cout << "        3:删除旧图书\n";//1
		cout << "        4:显示当前图书信息树\n";//1
		cout << "        0:退出\n\n";//1
		cout << "----------------------------\n\n";
		cout << "        请输入您的选择:";
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
			cout << "------更新图书信息------\n\n";
			cout << "请输入需要更新的图书编号：";
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
			cout << "-------添加新图书-------\n";
			cout << "请输入图书编号：";
			cin >> Num;
			cout << endl;
			cout << "请输入图书名称：";
			cin >> Name;
			cout << endl;
			cout << "请输入图书状态：" << endl << "0 - 旧书" << "1 - 新书" << endl;
			cin >> states;
			cout << endl;
			cout << "请输入图书是否在馆：" << endl << "0 - 出借" << "1 - 在馆" << endl;
			cin >> borrow;
			cout << endl;
			add(Name, Num, states, borrow);
			cout << '《' << Name << '》' << "顺利被添加！" << endl;
			system("pause");
			break;
		}
		case 3:
		{
			string Num;
			system("cls");
			cout << "--------删除旧图书--------\n\n";
			cout << "请输入需要删除的图书编号：";
			cin >> Num;
			cout << endl;
			deleteNode(Num);
			system("pause");
			break;
		}
		case 4:
		{
			system("cls");
			cout << "----显示当前图书信息树---\n";
			cout << "接下来将按照左子树在上，右子树在下顺序输出图书信息树：" << endl;
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

void AVLBookTree::print() {  //封装后的打印函数
	printAVL(root);
}
void AVLBookTree::printAVL(AVLNode* node, int sign)
{
	if (sign > 0) {  //当树的高度大于0时
		for (int i = 0; i < sign - 1; i++) {
			printf(vec_left[i] ? "│   " : "    ");
		}
		printf(vec_left[sign - 1] ? "├── " : "└── ");
	}

	if (!node) {  //当结点不存在的时候
		printf("(null)\n");
		return;
	}

	// 打印当前结点图书数据
	cout << node->getBook().booknum << ' ' << node->getBook().bookname << ' ';
	if (node->getBook().bookstates == 0)
		cout << "旧书" << ' ';
	else
		cout << "新书" << ' ';
	if (node->getBook().bookBorrow == 0)
		cout << "不在库" << ' ';
	else
		cout << "在库" << ' ';
	cout << endl;
	//当前结点为叶子结点时返回
	if (!node->getLChild() && !node->getRChild()) {
		return;
	}

	vec_left[sign] = 1; //进入当前结点的右孩子
	printAVL(node->getRChild(), sign + 1);
	vec_left[sign] = 0; //进入当前结点的左孩子
	printAVL(node->getLChild(), sign + 1);

}

void AVLBookTree::add(string name, string num, int state, int borrow) {
	add(root, new AVLNode(name, num, state, borrow));
}

void AVLBookTree::add(AVLNode* T, AVLNode* newNode, AVLNode* parent) {  //第一个参数是当前结点地址，作递归用，第二个参数是新结点地址
	//AVL树是空树时，头节点指向加入的结点
	if (root == nullptr) {
		root = newNode;
		//获取树的深度
		depth = getHeight(root);
		sign = true;
		return;
	}


	//AVL不为空时，以图书编号作为二叉排序树的排序规则
	if (T->getBook().booknum > newNode->getBook().booknum) {  //若当前结点值比新结点值大，则转向左孩子
		if (T->getLChild() == nullptr) {
			T->setLChild(newNode);  //左孩子为空，直接添加为左孩子
			sign = true;
			//获取树的深度
			depth = getHeight(root);
		}
		else add(T->getLChild(), newNode, T);  //左孩子非空，转向左孩子
	}
	else if (T->getBook().booknum < newNode->getBook().booknum) {  //若当前结点值比新结点值小，则转向右孩子
		if (T->getRChild() == nullptr) {
			T->setRChild(newNode);  //右孩子为空，直接添加为右孩子
			sign = true;
			//获取树的深度
			depth = getHeight(root);
		}
		else add(T->getRChild(), newNode, T);  //右孩子非空，转向右孩子
	}
	else {  //若当前结点值和新结点值一样大，则返回错误信息
		cout << "图书\"" << newNode->getBook().bookname << "\"已存在！" << endl;
		delete newNode;  //释放空间
		return;
	}

	//平衡操作
	if (T->getBF() > 1) {  //找到最小不平衡子树
		RRotate(T, parent);  //右旋
	}
	else if (T->getBF() < -1) {
		LRotate(T, parent);  //左旋
	}
}

void AVLBookTree::updataInfo(string num)
{
	AVLNode* T = root;
	while (T != NULL && num != T->getBook().booknum) {//查找需要修改的图书编号
		if (num < T->getBook().booknum)
			T = T->getLChild();//小于就在左子树上查找
		else
			T = T->getRChild();//大于就在右子树上查找
	}
	if (T == NULL)
		cout << "图书编号" << num << "不存在，请重新输入！";
	else {
		int flag = 1;//每一项元素是否需要修改标志位
		string idxs;//暂存需要修改的字符串类型数据
		cout << "是否修改图书名称：" << endl << "0 - 不需要" << "1 - 需要" << endl;
		cin >> flag;
		if (flag == 1) {
			cin >> idxs;
			while (1) {
				cout << "请输入新的图书名：";
				cin >> idxs;
				if (idxs == T->getBook().bookname) {
					cout << "与原名称一致，请重新修改" << endl;
					continue;
				}
				else {
					T->getBook().bookname = idxs;
					cout << "修改成功!" << endl;
				}
			}
		}
		system("pause");
		cout << "是否修改图书在馆状态：" << endl << "0 - 不需要" << "1 - 需要" << endl;
		cin >> flag;
		if (flag == 1) {
			T->getBook().bookBorrow = ~(T->getBook().bookBorrow);
			cout << "修改成功!" << endl;
		}

		cout << "修改全部完成，准备返回上一级菜单！" << endl;
	}
}
/*
 * 由于获取树的深度时需要得到每个结点左右子树的深度
 * 所以可以顺便计算出当前结点的平衡因子
 */
int AVLBookTree::getHeight(AVLNode* T) {  //使用递归获取树的深度
	if (T == nullptr) return 0;

	int left, right;  //记录左右子树深度

	left = getHeight(T->getLChild());  //当前结点左子树深度
	right = getHeight(T->getRChild());  //当前结点右子树深度
	T->setBf(left - right);  //计算出当前结点的平衡因子

	return  max(left, right) + 1;  //取左右子树中最深的一个作为返回值
}

void AVLBookTree::deleteNode(string num) {
	deleteNode(root, num);
}
void AVLBookTree::deleteNode(AVLNode* node, string num, AVLNode* p) {
	if (node == nullptr) {
		//cout<<"empty node!"<<endl;
		return;
	}

	if (node->getBook().booknum == num) {  //若当前结点图书编号即为所寻结点图书编号

		if (node->getRChild() && node->getLChild()) {//如果有两个孩子结点

			AVLNode* temPreNode = node;  //指向中序后继结点的双亲结点
			AVLNode* temNode = node->getRChild();  //指向中序后继结点
			while (temNode->getLChild() != nullptr) {  //遍历到右子树最左下结点
				temPreNode = temNode;
				temNode = temNode->getLChild();
			}

			if (node->getRChild() != temNode) {  //当中序后继结点不是目标结点的右孩子时
				if (temNode->getRChild() != nullptr) {  //若中序后继节点右孩子不为空
					temPreNode->setLChild(temNode->getRChild());  //中序后继结点的右孩子变为前一个结点的左孩子
				}
				temNode->setRChild(node->getRChild());  //被删除结点的右孩子作为中序后继节点的右孩子
				temPreNode->setLChild(nullptr);  //中序后继结点的双亲结点左孩子置空
			}
			temNode->setLChild(node->getLChild());  //被删除结点的左孩子作为中序后继节点的左孩子

			if (p != nullptr) {
				if (p->getRChild() == node) {  //是结点的右孩子时
					p->setRChild(temNode);  //中序后继节点作为双亲结点的右孩子
				}
				else if (p->getLChild() == node) {  //是结点的左孩子时
					p->setLChild(temNode);  //中序后继节点作为双亲结点的左孩子
				}
			}
			else {
				root = temNode;
			}
			delete node;  //删除本结点

		}
		else if (node->getRChild() && !node->getLChild()) {  //如果当前结点只有右孩子

			if (p == nullptr) {  //考虑目标结点为根节点的情形
				root = node->getRChild();  //设置根节点
				delete node;  //删除结点
			}
			else if (p->getLChild() == node) {  //若为父节点的左孩子
				p->setLChild(node->getRChild());
				delete node;  //删除结点
			}
			else if (p->getRChild() == node) {  //若为父节点的右孩子
				p->setRChild(node->getRChild());
				delete node;  //删除结点
			}

		}
		else if (!node->getRChild() && node->getLChild()) {  //如果当前结点只有左孩子

			if (p == nullptr) {  //考虑目标结点为根节点的情形
				root = node->getLChild();  //设置根节点
				delete node;  //删除结点
			}
			else if (p->getLChild() == node) {  //若为父节点的左孩子
				p->setLChild(node->getLChild());
				delete node;  //删除结点
			}
			else if (p->getRChild() == node) {  //若为父节点的右孩子
				p->setRChild(node->getLChild());
				delete node;  //删除结点
			}

		}
		else {  //若为叶子结点，则直接删除

			if (p == nullptr) {  //如果目标为孤立的根节点，则直接删除
				delete node;
				root = nullptr;
			}
			else if (p->getLChild() == node) {  //若为父节点的左孩子
				delete node;  //删除结点
				p->setLChild(nullptr);  //父节点左孩子指针置空
			}
			else if (p->getRChild() == node) {  //若为父节点的右孩子
				delete node;  //删除结点
				p->setRChild(nullptr);  //父节点右孩子指针置空
			}

		}
		node = nullptr;
		//重新计算高度
		depth = getHeight(root);
		sign = true;
		return;
	}

	deleteNode(node->getLChild(), num, node);

	//原结点位置平衡操作
	while (node->getLChild() != nullptr && node->getLChild()->getBF() > 1) {
		RRotate(node, p);  //右旋
	}

	//在左支删除时的上层平衡操作
	if (node->getBF() > 1) {  //找到最小不平衡子树
		RRotate(node, p);  //右旋
	}
	else if (node->getBF() < -1) {
		LRotate(node, p);  //左旋
	}

	deleteNode(node->getRChild(), num, node);

	//原结点位置平衡操作
	while (node->getRChild() != nullptr && node->getRChild()->getBF() > 1) {
		RRotate(node, p);  //右旋
	}

	//在右支删除时的上层平衡操作
	if (node->getBF() > 1) {  //找到最小不平衡子树
		RRotate(node, p);  //右旋
	}
	else if (node->getBF() < -1) {
		LRotate(node, p);  //左旋
	}

}

void AVLBookTree::RRotate(AVLNode* node, AVLNode* parent) {
	if (node == root) {  //若最小不平衡子树根结点为根节点
		if (node->getLChild()->getBF() < 0) {  //如果符号不同，则子结点先进行左旋
			LRotate(node->getLChild(), node);
		}
		AVLNode* temNode = root;
		root = root->getLChild();

		if (root->getRChild() == nullptr) {  //如果孩子结点没有右孩子
			root->setRChild(temNode);
			temNode->setLChild(nullptr);
		}
		else {  //如果孩子结点有右孩子，则将孩子结点的右孩子移到双亲结点的左下角
			temNode->setLChild(root->getRChild());
			root->setRChild(temNode);

		}

	}
	else {  //若不为根节点
		if (node->getLChild()->getBF() < 0) {  //如果符号不同，则子结点先进行左旋
			if (parent->getLChild() == node) {  //左边的右旋，双亲结点走左边
				LRotate(node->getLChild(), parent->getLChild());
			}
			else {  //右边的右旋，双亲结点走右边
				LRotate(node->getLChild(), parent->getRChild());
			}
		}

		//旋转操作
		AVLNode* temNode = node;
		AVLNode* childNode = node->getLChild();

		if (parent->getLChild() == node) {  //左边的右旋
			parent->setLChild(childNode);
		}
		else {  //右边的右旋
			parent->setRChild(childNode);
		}

		if (childNode->getRChild() == nullptr) {  //如果孩子结点没有右孩子
			childNode->setRChild(temNode);
			temNode->setLChild(nullptr);
		}
		else {  //如果孩子结点有右孩子结点，则将孩子结点的右孩子移到目标结点的左下角，进行右旋操作
			temNode->setLChild(childNode->getRChild());
			childNode->setRChild(temNode);
		}

	}
	depth = getHeight(root);  //重新计算树的深度和bf
}

void AVLBookTree::LRotate(AVLNode* node, AVLNode* parent) {
	if (node == root) {  //若最小不平衡子树根结点为根节点
		if (node->getRChild()->getBF() > 0) {  //如果符号不同，则子结点先进行右旋
			RRotate(node->getRChild(), node);
		}
		AVLNode* temNode = root;
		root = root->getRChild();

		if (root->getLChild() == nullptr) {  //如果孩子结点没有左孩子
			root->setLChild(temNode);
			temNode->setRChild(nullptr);
		}
		else {  //如果孩子结点有两个孩子结点，则将孩子结点的左孩子移到双亲结点的右下角
			temNode->setRChild(root->getLChild());
			root->setLChild(temNode);
		}

	}
	else {  //若不为根节点
		if (node->getRChild()->getBF() > 0) {  //如果符号不同，则子结点先进行右旋
			if (parent->getLChild() == node) {  //左边的右旋，双亲结点走左边
				RRotate(node->getRChild(), parent->getLChild());
			}
			else {  //右边的左旋，双亲结点走右边
				RRotate(node->getRChild(), parent->getRChild());
			}
		}
		//旋转操作
		AVLNode* temNode = node;
		AVLNode* childNode = node->getRChild();

		if (parent->getLChild() == node) {  //左边的左旋
			parent->setLChild(childNode);
		}
		else {  //右边左旋
			parent->setRChild(childNode);
		}

		if (childNode->getLChild() == nullptr) {  //如果孩子结点没有左孩子
			childNode->setLChild(temNode);
			temNode->setRChild(nullptr);
		}
		else {  //如果孩子结点有两个孩子结点，则将孩子结点的左孩子移到双亲结点的右下角
			temNode->setRChild(childNode->getLChild());
			childNode->setLChild(temNode);
		}


	}
	depth = getHeight(root);  //重新计算树的深度和bf
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


