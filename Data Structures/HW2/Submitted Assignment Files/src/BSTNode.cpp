/* @Author
Student Name: Mehmet Ali Balıkçı

Student ID : 150200059

Date: 06.06.2023*/

#include "BSTNode.h"

// Constructor
BSTNode::BSTNode(const int& chrom, const int& pos, const char& alt_base)
    : chrom_(chrom), pos_(pos), alt_base_(alt_base), left_(nullptr), right_(nullptr){};
void BSTNode::setChrom(const int& chrom){chrom_ = chrom;} // setter method for chrom
const int& BSTNode::getChrom() const {return chrom_;} // getter method for chrom
void BSTNode::setPos(const int& pos){pos_ = pos;} // setter method for pos
const int& BSTNode::getPos() const {return pos_;} // getter method for pos
void BSTNode::setAltBase(const char& alt_base){alt_base_ = alt_base;} // setter method for alt_base
const char& BSTNode::getAltBase() const {return alt_base_;} // getter method for alt_base
void BSTNode::setLeft(BSTNode* left){left_ = left;} // setter method for left child                
BSTNode* BSTNode::getLeft() const {return left_;} // getter method for left child
void BSTNode::setRight(BSTNode* right){right_ = right;} // setter method for right child 
BSTNode* BSTNode::getRight() const {return right_;} // getter method for right child