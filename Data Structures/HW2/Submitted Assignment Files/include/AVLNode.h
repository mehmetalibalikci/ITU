/* @Author
Student Name: Mehmet Ali Balıkçı

Student ID : 150200059

Date: 06.06.2023*/

#pragma once

class AVLNode{
    private:
        int chrom_;
        int pos_;
        char alt_base_;
        AVLNode* left_;
        AVLNode* right_;
        int height_; 
    public:
        AVLNode(const int& chrom, const int& pos, const char& alt_base); // cosntructor
        void setChrom(const int& chrom); // setter for chrom
        int getChrom() const; // getter for chrom
        void setPos(const int& pos); // setter for pos
        int getPos() const; // getter for pos
        void setAltBase(const char& alt_base); // setter for alt_base
        char getAltBase() const; // getter for alt_Base
        void setLeft(AVLNode* left); // setter for left child   
        AVLNode* getLeft() const; // getter for left child
        void setRight(AVLNode* right); // setter for right child
        AVLNode* getRight() const;  // getter for right child
        void setHeight(const int& height); // setter for height
        int getHeight() const; // getter for height
};