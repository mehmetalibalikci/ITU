/*      
    MEHMET ALİ BALIKÇI
    150200059
*/


#include "../include/Computer.h"


CUDA::CUDA(int cores){                      // Constructor for CUDA object
    std::cout<<"CUDA is ready"<<std::endl;
    numCores = cores;
}
std::string CUDA::render() const{            // To operate render operation
    return "Video is rendered" ;
}
std::string CUDA::trainModel() const{       // To operate trainModel operation
    return "AI Model is trained" ;
}
int CUDA::getNumCores() const{              // To get the variable of numCores
    return numCores;
}
void CUDA::setNumCores(int newNumCores){   // To set the variable of numCores
    numCores = newNumCores;
}


ALU::ALU(int cores){                        // Constructor for ALU object
    std::cout<<"ALU is ready"<<std::endl;
    numPerCores = cores;
}
int ALU::add(int a, int b) const{           // To operate adding operation
    return a+b;
}
int ALU::subtract(int a, int b) const{      // To operate subtracting operation
    return a-b;
}
int ALU::multiply(int a, int b) const{      // To operate multiplying operation
    return a*b;
}
int ALU::getNumPerCores() const{            // To get the variable of numPerCores
    return numPerCores;
}
void ALU::setNumPerCores(int newNumPerCores){ // To set the variable of numPerCores
    numPerCores = newNumPerCores;
}


GPU::GPU(int numOfCUDA)                       // Constructor for GPU object
    : m_cuda{numOfCUDA}
{
    std::cout<<"GPU is ready"<<std::endl;
}
std::string GPU::execute(std::string operationName) const{    // To execute the operations of render and trainModel by means of CUDA
    if(operationName == "render"){
        return m_cuda.render();
    }
    else if(operationName == "trainModel"){
        return m_cuda.trainModel();
    }
    else return 0;
}


CPU::CPU(int numOfALU)                      // Constructor for CPU object
    : m_alu{numOfALU}
{
    std::cout<<"CPU is ready"<<std::endl;
}
int CPU::execute(std::string nameOfOperation) const{ // To execute the operations of adding, subtracting and multiplying by means of ALU
    int x,y;
    std::cout<<"Enter two integers"<<std::endl;
    std::cin>>x;            
    std::cin>>y;
    if(nameOfOperation == "subtract"){
        return m_alu.subtract(x,y);
    }
    else if(nameOfOperation == "add"){
        return m_alu.add(x,y);
    }
    else if(nameOfOperation == "multiply"){
        return m_alu.multiply(x,y);
    }
    else return 0;
}


Computer::Computer(){                           // Constructor for Computer object
    std::cout<<"Computer is ready"<<std::endl;
}
void Computer::operator+(const CPU& in_cpu){    // Overload the sign +, to add a cpu to the computer
    if(cpu_counter == 0){
        attachedCPU = &in_cpu;
        std::cout<<"CPU is attached"<<std::endl;
        cpu_counter++;
    }
    else{
        std::cout<<"There is already a CPU"<<std::endl;
    }
}
void Computer::operator+(const GPU& in_gpu){    // Overload the sign +, to add a Gpu to the computer
    if(gpu_counter == 0){
        attachedGPU = &in_gpu;
        std::cout<<"GPU is attached"<<std::endl;
        gpu_counter++;
    }
    else{
        std::cout<<"There is already a GPU"<<std::endl;
    }
}
void Computer::execute(std::string operation_name) const{   // To execute the operations of adding, subtracting and multiplying, render, trainModel by means of CPU and GPU
    if (operation_name == "subtract" || operation_name == "add" || operation_name == "multiply")
    {
        std::cout<<attachedCPU->execute(operation_name)<<std::endl;
    }
    else if (operation_name == "trainModel" || operation_name == "render")
    {
        std::cout<<attachedGPU->execute(operation_name)<<std::endl;
    }
}