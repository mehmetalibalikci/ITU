/* @Author
Student Name: Mehmet Ali Balıkçı

Student ID : 150200059

Date: 06.06.2023*/

#include "AVLNode.h"

//constructor
AVLNode::AVLNode(const int& chrom, const int& pos, const char& alt_base)
    : chrom_(chrom), pos_(pos), alt_base_(alt_base), left_(nullptr), right_(nullptr) {};
void AVLNode::setChrom(const int& chrom) {chrom_=chrom;} // setter method for chrom
int AVLNode::getChrom() const{return chrom_;} // getter method for chrom
void AVLNode::setPos(const int& pos){pos_=pos;} // setter method for pos
int AVLNode::getPos() const {return pos_;}// getter method for pos
void AVLNode::setAltBase(const char& alt_base){alt_base_=alt_base;}// setter method for alt_base
char AVLNode::getAltBase() const {return alt_base_;}// getter method for alt_base
void AVLNode::setLeft(AVLNode* left){left_=left;} // setter method for left child                
AVLNode* AVLNode::getLeft() const {return left_;} // getter method for left child
void AVLNode::setRight(AVLNode* right){right_=right;} // setter method for right child 
AVLNode* AVLNode::getRight() const {return right_;} // getter method for right child
void AVLNode::setHeight(const int& height){height_=height;} // setter method for height of a node
int AVLNode::getHeight() const {return height_;}  // getter method for height of a node
