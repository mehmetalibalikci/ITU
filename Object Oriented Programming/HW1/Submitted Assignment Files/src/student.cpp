/* @Author
 * Student Name:  Mehmet Ali Balıkçı
 * Student ID : 150200059
 */

#include "../include/Student.h"
#include <iostream>

using std::cout;
using std::endl;

Student::Student(string name,double gpa,int gre,int toefl){
	Name=name;
	GPA=gpa;
	GRE=gre;
	TOEFL=toefl;
	cout<<Name<<" logged in to the system."<<endl;
}


string Student::get_name() const{
	return Name;
}

void Student::set_noapp() const{
	NOAPP ++;
}

unsigned int Student::get_noapp() const{
		return NOAPP;
}

void Student::set_name(string name){
	cout<<get_name()<<" logged in to the system "<<endl;
	Name=name;
}

double Student::get_gpa() const{
	return GPA;
}

int Student::get_gre() const{
	return GRE;
}

int Student::get_toefl() const{
	return TOEFL;
}

Student::~Student(){
	cout<<Name<<" logged out of the system with "<<NOAPP<<" application(s)"<<endl;
}