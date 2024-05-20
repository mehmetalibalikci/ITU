/*      
    MEHMET ALİ BALIKÇI
    150200059
*/

#include<string>
#include<iostream>

using std::string;

class CUDA{
    public:
        CUDA(int);
        string render() const;
        string trainModel() const;
        int getNumCores() const;
        void setNumCores(int);
    private:
        int numCores;
};

class ALU{
    public:
        ALU(int);
        int add(int,int) const;
        int subtract(int,int) const;
        int multiply(int,int) const;
        int getNumPerCores() const;
        void setNumPerCores(int);
    private:
        int numPerCores;
};

class GPU{
    public:
        GPU(int);
        string execute(string) const;
    private:
        CUDA m_cuda;
};

class CPU{
    public:
        CPU(int);
        int execute(string) const;
    private:
        ALU m_alu; 
};

class Computer{
    public:
        Computer();
        void operator +(const CPU&);
        void operator +(const GPU&);
        void execute(string) const;
    private:
        unsigned int cpu_counter{};
        unsigned int gpu_counter{};
        const CPU* attachedCPU;
        const GPU* attachedGPU;       
};