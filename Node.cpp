//
// Created by Dylan on 2021/12/15.
//

#include "common.h"
#include "Node.h"

AVLNode::AVLNode(string usn, string pwd, int state, int borrow) {
    book.bookname = usn;  
    book.booknum = pwd;
    book.bookstates = state;
    book.bookBorrow = borrow;
}

bookInfo& AVLNode::getBook() {
    return book;//���ص�ǰ����ͼ����Ϣ
}

AVLNode::~AVLNode() {

}

AVLNode* AVLNode::getLChild() {
    return lChild;
}

AVLNode* AVLNode::getRChild() {
    return rChild;
}

void AVLNode::setLChild(AVLNode* newNode) {
    lChild = newNode;
}

void AVLNode::setRChild(AVLNode* newNode) {
    rChild = newNode;
}

void AVLNode::setBf(int bf) {
    this->bf = bf;
}

int AVLNode::getBF() {
    return bf;
}
