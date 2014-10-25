/*
*   @Author Ferdinand von Hagen
*   @Mail   vhagenf@student.ethz.ch
*   @Legi   14-942-270
*   @Date   23.10.2014
*/

#include <iostream>
#include "cpusim_lib.cpp"

const unsigned int cmd_add = 0x01;
const unsigned int cmd_sub = 0x02;
const unsigned int cmd_mul = 0x03;
const unsigned int cmd_div = 0x04;
const unsigned int cmd_mod = 0x05;
const unsigned int cmd_set = 0x06;
const unsigned int cmd_jmp = 0x10;
const unsigned int cmd_jge = 0x11;
const unsigned int cmd_jle = 0x12;
const unsigned int cmd_jgr = 0x13;
const unsigned int cmd_jls = 0x14;
const unsigned int cmd_jeq = 0x15;
const unsigned int cmd_jne = 0x16;
const unsigned int cmd_out = 0x21;
const unsigned int cmd_in = 0x22;
const unsigned int cmd_hlt = 0x30;

//Program counter used in Part D
unsigned int pc = 0;


// No comes a whole bunch of functions. All functions are defined here!!
int mem(unsigned int address, unsigned int data)
{
    memory_write(address, data);
    return 0;
}

int mem(unsigned int address)
{
    return memory_read(address);
}

void inst_add(unsigned int op1, unsigned int op2, unsigned int op3)
{
    mem(op3, mem(op1) + mem(op2));
    pc++;
}

void inst_sub(unsigned int op1, unsigned int op2, unsigned int op3)
{
    mem(op3, mem(op1) - mem(op2));
    pc++;
}

void inst_mul(unsigned int op1, unsigned int op2, unsigned int op3)
{
    mem(op3, mem(op1) * mem(op2));
    pc++;
}

void inst_div(unsigned int op1, unsigned int op2, unsigned int op3)
{
    mem(op3, mem(op1) / mem(op2));
    pc++;
}

void inst_mod(unsigned int op1, unsigned int op2, unsigned int op3)
{
    mem(op3, mem(op1) % mem(op2));
    pc++;
}

void inst_jmp(unsigned int op1, unsigned int op2, unsigned int op3)
{
    pc = op1;
}

void inst_jeq(unsigned int op1, unsigned int op2, unsigned int op3)
{
    if (mem(op2) == mem(op3))
    {
        pc = op1;
    }
    else
    {
        pc++;
    }

}

void inst_jne(unsigned int op1, unsigned int op2, unsigned int op3)
{
    if (mem(op2) != mem(op3))
    {
        pc=op1;
    }
    else
    {
        pc++;
    }

}

void inst_jgr(unsigned int op1, unsigned int op2, unsigned int op3)
{
    if (mem(op2) > mem(op3))
    {
        pc = op1;
    }
    else
    {
        pc++;
    }
}

void inst_jls(unsigned int op1, unsigned int op2, unsigned int op3)
{
    if (mem(op2) < mem(op3))
    {
        pc = op1;
    }
    else
    {
        pc++;
    }
}

void inst_jge(unsigned int op1, unsigned int op2, unsigned int op3)
{
    if (mem(op2) >= mem(op3))
    {
        pc = op1;
    }
    else
    {
        pc++;
    }
}

void inst_jle(unsigned int op1, unsigned int op2, unsigned int op3)
{
    if (mem(op2) <= mem(op3))
    {
        pc = op1;
    }
    else
    {
        pc++;
    }
}

void inst_set(unsigned int op1, unsigned int op2, unsigned int op3)
{
    mem(op1, op2 + (op3 * 256));
    pc++;
}

void inst_out(unsigned int op1, unsigned int op2, unsigned int op3)
{
    cpusim_out(mem(op1));
    pc++;
}

void inst_in(unsigned int op1, unsigned int op2, unsigned int op3)
{
    unsigned int data;
    std::cin >> std::dec >> data;
    mem(op1, data);
    pc++;
}

void decode_instruction(unsigned int inst, unsigned int& opc, unsigned int& op1, unsigned int& op2, unsigned int& op3)
{
    op3 = inst & 0xFF;
    op2 = (inst >> 8) & 0xFF;
    op1 = (inst >> 16) & 0xFF;
    opc = (inst >> 24) & 0xFF;
}

void disassemble_inst(unsigned int inst)
{
    //Break the instruction into the four parts
    unsigned int opc = 0, op1 = 0, op2 = 0, op3 = 0;
    decode_instruction(inst, opc, op1, op2, op3);

    //Now comes a big fat if-table
    if(opc == cmd_set)
    {
        cpu::aout << "set " << op1 << ", " << op2 << ", " << op3 << std::endl;
    }
    else if(opc == cmd_out)
    {
        cpu::aout << "out " << op1 << std::endl;
    }
    else if(opc == cmd_in)
    {
        cpu::aout << "in " << op1 << std::endl;
    }
    else if(opc == cmd_hlt)
    {
        cpu::aout << "hlt" << std::endl;
    }
    else if(opc == cmd_add)
    {
        cpu::aout << "add " << op1 << ", " << op2 << ", " << op3 << std::endl;
    }
    else if(opc == cmd_sub)
    {
        cpu::aout << "sub " << op1 << ", " << op2 << ", " << op3 << std::endl;
    }
    else if(opc == cmd_mul)
    {
        cpu::aout << "mul " << op1 << ", " << op2 << ", " << op3 << std::endl;
    }
    else if(opc == cmd_div)
    {
        cpu::aout << "div " << op1 << ", " << op2 << ", " << op3 << std::endl;
    }
    else if(opc == cmd_mod)
    {
        cpu::aout << "mod " << op1 << ", " << op2 << ", " << op3 << std::endl;
    }
    else if(opc == cmd_jmp)
    {
        cpu::aout << "jmp " << op1 << std::endl;
    }
    else if(opc == cmd_jeq)
    {
        cpu::aout << "jeq " << op1 << ", " << op2 << ", " << op3 << std::endl;
    }
    else if(opc == cmd_jne)
    {
        cpu::aout << "jne " << op1 << ", " << op2 << ", " << op3 << std::endl;
    }
    else if(opc == cmd_jgr)
    {
        cpu::aout << "jgr " << op1 << ", " << op2 << ", " << op3 << std::endl;
    }
    else if(opc == cmd_jls)
    {
        cpu::aout << "jls " << op1 << ", " << op2 << ", " << op3 << std::endl;
    }
    else if(opc == cmd_jge)
    {
        cpu::aout << "jge " << op1 << ", " << op2 << ", " << op3 << std::endl;
    }
    else if(opc == cmd_jle)
    {
        cpu::aout << "jle " << op1 << ", " << op2 << ", " << op3 << std::endl;
    }
    else
    {
        //Anything went terribly wrong
        cpu::aout << "illegal" << std::endl;
    }
}

void execute_inst(unsigned int opc, unsigned int op1, unsigned int op2, unsigned int op3){
    //Now comes a big fat if-table again but now we just call the method handlers!!
    if(opc == cmd_set)
    {
        inst_set(op1, op2, op3);
    }
    else if(opc == cmd_out)
    {
        inst_out(op1, op2, op3);
    }
    else if(opc == cmd_in)
    {
        inst_in(op1, op2, op3);
    }
    else if(opc == cmd_add)
    {
        inst_add(op1, op2, op3);
    }
    else if(opc == cmd_sub)
    {
        inst_sub(op1, op2, op3);
    }
    else if(opc == cmd_mul)
    {
        inst_mul(op1, op2, op3);
    }
    else if(opc == cmd_div)
    {
        inst_div(op1, op2, op3);
    }
    else if(opc == cmd_mod)
    {
        inst_mod(op1, op2, op3);
    }
    else if(opc == cmd_jmp)
    {
        inst_jmp(op1, op2, op3);
    }
    else if(opc == cmd_jeq)
    {
        inst_jeq(op1, op2, op3);
    }
    else if(opc == cmd_jne)
    {
        inst_jne(op1, op2, op3);
    }
    else if(opc == cmd_jgr)
    {
        inst_jgr(op1, op2, op3);
    }
    else if(opc == cmd_jls)
    {
        inst_jls(op1, op2, op3);
    }
    else if(opc == cmd_jge)
    {
        inst_jge(op1, op2, op3);
    }
    else if(opc == cmd_jle)
    {
        inst_jle(op1, op2, op3);
    }
}

int main()
{
    // part (a) input data from std::cin and write to program memory
    {
        // p is used to walk through the memory
        unsigned int p = 0;
        unsigned int code;

        do
        {
            //First read the value from stdin; We will get hexadecimal values so convert them to uint
            std::cin >> std::hex >> code;

            //Finally write the values to memory and post-increment the memory counter
            memory_write(p++, code);
        }
        //Do this until code is zero. This marks the end of the program
        while (code != 0);
    }

    // part (b) decode instructions
    {
        unsigned int p = 0, opc = 0, op1 = 0, op2 = 0, op3 = 0, inst = 0;
        do
        {
            //first read the code from the memory
            inst = memory_read(p++);

            //decode instruction to the four parts OpCode and three operands
            decode_instruction(inst, opc, op1, op2, op3);

            //and write the extracted code to the cpusim_lib for grading
            cpusim_outdecode(opc, op1, op2, op3);
        }
        while(inst != 0);
    }

    // part (c) print instructions
    {
        unsigned int p = 0, inst;
        while((inst = mem(p++)) != 0)
        {
            disassemble_inst(inst);
        }
    }
    // part (d) execute instructions
    {
        //Initialize ProgramCounter to zero; It should be zero but we make it fail safe!!
        pc = 0;
        unsigned int inst = 0;
        unsigned int opc = 0, op1 = 0, op2 = 0, op3 = 0;

        do
        {
            //FETCH
            inst = memory_read(pc);

            //DECODE
            decode_instruction(inst, opc, op1, op2, op3);

            //EXECUTE
            execute_inst(opc, op1, op2, op3);
        }
        while(inst != 0 && opc != cmd_hlt);
    }


    return 0;
}


