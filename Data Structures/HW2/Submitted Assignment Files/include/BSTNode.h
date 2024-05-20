/* @Author
Student Name: Mehmet Ali Balıkçı

Student ID : 150200059

Date: 06.06.2023*/

#pragma once

class BSTNode{
    private:
        int chrom_;
        int pos_;
        char alt_base_;
        BSTNode* left_;
        BSTNode* right_;
    public:
        BSTNode(const int& chrom, const int& pos, const char& alt_base); // constructor
        void setChrom(const int& chrom); // setter
        const int& getChrom() const; // getter
        void setPos(const int& pos); // setter
        const int& getPos() const; // getter
        void setAltBase(const char& alt_base); // setter
        const char& getAltBase() const; // getter
        void setLeft(BSTNode* left);  // setter               
        BSTNode* getLeft() const; // getter
        void setRight(BSTNode* right); // setter
        BSTNode* getRight() const; // getter
};
