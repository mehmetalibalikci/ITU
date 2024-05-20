/* @Author
 * Student Name:  Mehmet Ali Balıkçı
 * Student ID : 150200059
 */
#include <cstring>
#include "Student.h"

using std::string;

class University{
	public:
		University(string,double,double,double,double,string="");
		void evaluate_student(Student& student);
		void evaluate_student(const Student&);
		
	private:
		string Name="";
		double GPA_W, GRE_W, TOEFL_W,BIAS;
		string CName="";		
};