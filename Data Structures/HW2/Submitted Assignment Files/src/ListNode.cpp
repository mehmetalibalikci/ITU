/* @Author
Student Name: Mehmet Ali Balıkçı

Student ID : 150200059

Date: 06.06.2023*/

#include "ListNode.h"

ListNode::ListNode(const int& chrom, const int& pos, const char& alt_base){chrom_=chrom; pos_=pos; alt_base_=alt_base; next_=nullptr;} // constructor
void ListNode::setChrom(const int& chrom){chrom_ = chrom;} // setter method for chrom
int ListNode::getChrom() const {return chrom_;} // getter method for chrom
void ListNode::setPos(const int& pos){pos_ = pos;} // setter method for pos
int ListNode::getPos() const {return pos_;} // getter method for pos
void ListNode::setAltBase(const char& alt_base){alt_base_ = alt_base;} // setter method for alt_base
char ListNode::getAltBase() const {return alt_base_;}  // getter method for alt_base
void ListNode::setNext(ListNode* next){next_ = next;} // setter method for the pointer next
ListNode* ListNode::getNext() const {return next_;} // getter method for the pointer next

