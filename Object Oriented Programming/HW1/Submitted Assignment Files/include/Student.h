/* @Author
 * Student Name:  Mehmet Ali Balıkçı
 * Student ID : 150200059
 */

#include<cstring>
#include<iostream>
using std::string;

class Student{
	public:
		Student(string,double,int,int);
		~Student();
		void set_name(string);	
		unsigned int counter{};
		string get_name() const;
		double get_gpa() const;
		int get_gre() const;
		int get_toefl() const;
		unsigned int get_noapp() const;	
		void set_noapp() const;
	private:
		mutable unsigned int NOAPP{};
		string Name="";
		double GPA; 
		int GRE{}, TOEFL{};
};