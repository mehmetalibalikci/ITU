/* @Author
 * Student Name:  Mehmet Ali Balıkçı
 * Student ID : 150200059
 */

#include <iostream>
#include "../include/university.h"
using namespace std;

University::University(string name,double gpa_w, double gre_w, double toefl_w, double bias, string cname){
	Name=name;
	GPA_W=gpa_w;
	GRE_W=gre_w;
	TOEFL_W=toefl_w;
	BIAS=bias;
	CName=cname;
}

void University::evaluate_student(const Student& stobject)
{	
	float z;
	stobject.set_noapp();
	
	z= GPA_W*stobject.get_gpa() + GRE_W*stobject.get_gre() + TOEFL_W*stobject.get_toefl() + BIAS;
	
	if(z>=0){
		cout<<stobject.get_name()<<" is admitted to "<<Name<<endl;
	}
	else{
		cout<<stobject.get_name()<<" is rejected from "<<Name<<endl;
	}
}

void University::evaluate_student(Student& student){
	float z;
	student.set_noapp();
	z= GPA_W*student.get_gpa() + GRE_W*student.get_gre() + TOEFL_W*student.get_toefl() + BIAS;
	
	if(z>=0){
		cout<<student.get_name()<<" is admitted to "<<Name<<endl;
	}
	else{
		cout<<student.get_name()<<" is rejected from "<<Name<<endl;
	}
}