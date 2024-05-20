/* @Author
Student Name: Mehmet Ali Balıkçı

Student ID : 150200059

Date: 06.06.2023*/

#pragma once

class ListNode{
    private:
        int chrom_;
        int pos_;
        char alt_base_;
        ListNode* next_;
    public:
        ListNode(const int& chrom, const int& pos, const char& alt_base); //constructor
        void setChrom(const int& chrom); // setter
        int getChrom() const; // getter
        void setPos(const int& pos); // setter
        int getPos() const ; // getter
        void setAltBase(const char& alt_base); // setter
        char getAltBase() const; // getter 
        void setNext(ListNode* next); // setter
        ListNode* getNext() const; // getter
};
