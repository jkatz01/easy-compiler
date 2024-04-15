#include "definitions.h"
#include <iostream>
#include <fstream>

class CodeGenerator {
protected:
	std::string target_name;
	std::ofstream asm_file;
	int label_counter = 0;
public:
	CodeGenerator(std::string target) : target_name(target) {
		asm_file.open("program.asm", std::ios::out | std::ios::trunc);
	}
	virtual void initAssembly() = 0;
	virtual void startMainAssembly() = 0;
	virtual void finalizeAssembly() = 0;
	virtual void functionStart(std::string function_name) = 0;
	virtual void functionAddParameter(int param_offset, std::string reg_1) = 0;
	virtual void functionEnd() = 0;
	virtual void returnRegister(std::string reg_1) = 0;
	virtual void testIntPrint() = 0;
	virtual void printComment(std::string comment) = 0;
	virtual void makeDeclaration(int offset) = 0;
	virtual void makeAssignment(int offset) = 0;
	virtual void makePrintInt() = 0;
	virtual void makePushVariable(int offset) = 0;
	virtual void makePushIntConstant(int number) = 0;
	virtual void pushRegister(std::string reg_1) = 0;
	virtual void popToRegister(std::string reg_1) = 0;
	virtual void makeMoveVariableToReg(int offset, std::string reg) = 0;
	virtual void makeMoveConstIntToReg(int number, std::string reg) = 0;
	virtual void addRegisters(std::string reg_1, std::string reg_2) = 0;
	virtual void subRegisters(std::string reg_1, std::string reg_2) = 0;
	virtual void moveRegisters(std::string reg_1, std::string reg_2) = 0;
	virtual void imulRegisters(std::string reg_1, std::string reg_2) = 0;
	virtual void idivRegisters(std::string reg_1, std::string reg_2) = 0;
	virtual void notRegister(std::string reg_1) = 0;
	virtual void orRegisters(std::string reg_1, std::string reg_2) = 0;
	virtual void andRegisters(std::string reg_1, std::string reg_2) = 0;
	virtual void equalsRegisters(std::string reg_1, std::string reg_2) = 0;
	virtual void unequalsRegisters(std::string reg_1, std::string reg_2) = 0;
	virtual void greaterEqualsRegisters(std::string reg_1, std::string reg_2) = 0;
	virtual void lesserEqualsRegisters(std::string reg_1, std::string reg_2) = 0;
	virtual void greaterRegisters(std::string reg_1, std::string reg_2) = 0;
	virtual void lesserRegisters(std::string reg_1, std::string reg_2) = 0;
	virtual void makeWhileStart(int wh_label_count) = 0;
	virtual void makeWhileMiddle(std::string reg_1, int wh_label_count) = 0;
	virtual void makeWhileEnd(int wh_label_count) = 0;
	virtual void makeIfStart(std::string reg_1, int label_count) = 0;
	virtual void makeIfEnd(int label_count) = 0;
	virtual void makeReturn(std::string reg_1, std::string reg_2) = 0;
	virtual void callFunction(std::string func_name) = 0;
	
};

class CodeGen_x86_64_fasm_w : public CodeGenerator {
public:
	std::string include_path = "D:\\Program Files\\flat-assembler\\INCLUDE\\";

	CodeGen_x86_64_fasm_w() : CodeGenerator("x86_64 flat assembler windows") {}

	void initAssembly() {
		asm_file << ";; Target: " << target_name << std::endl;
		asm_file << ";; Start of assembly" << std::endl;

		asm_file << "format PE64 console 4.0" << std::endl;
		asm_file << std::endl;
		asm_file << "include '" << include_path << "win64a.inc'" << std::endl;
		asm_file << std::endl;
		asm_file << "entry start" << std::endl;
		asm_file << std::endl;

		asm_file << "section '.text' code readable executable" << std::endl;
		
	}

	void startMainAssembly() {
		asm_file << "start: " << std::endl;
		

		// Set up stack pointer
		asm_file << std::endl;
		asm_file << "        push rbp" << std::endl;
		asm_file << "        mov rbp, rsp" << std::endl;

		asm_file << "        sub rsp, 8*400 ; reserve space on stack i think?" << std::endl;
		// This needs to know the number of variables we will have in the var_table
		// or maybe we should just reserve a lot
	}

	void finalizeAssembly() {
		asm_file << std::endl;
		asm_file << "        invoke printf, endprint" << std::endl;
		asm_file << "        invoke Sleep, 4000" << std::endl;
		asm_file << "        push 0" << std::endl;
		asm_file << "        call [ExitProcess]" << std::endl;

		asm_file << std::endl;
		asm_file << "section '.rdata' data readable" << std::endl;
		asm_file << "        intprint db 'int: %d', 10, 0" << std::endl;
		asm_file << "        endprint db 'END OF PROGRAM', 10, 0" << std::endl;

		asm_file << std::endl;
		asm_file << "section '.idata' data readable import" << std::endl;
		asm_file << "        library kernel32, 'kernel32.dll', \\" << std::endl;
		asm_file << "                msvcrt,   'msvcrt.dll'" << std::endl;

		asm_file << "        import kernel32, \\" << std::endl;
		asm_file << "        ExitProcess, 'ExitProcess', \\" << std::endl;
		asm_file << "        Sleep, 'Sleep'" << std::endl;
		asm_file << "        import msvcrt, printf, 'printf'" << std::endl;
	}

	void functionStart(std::string function_name) {
		asm_file << function_name << ":" << std::endl;
		asm_file << "        push rbp" << std::endl;
		asm_file << "        mov rbp, rsp" << std::endl;
		asm_file << "        sub rsp, 8*64" << std::endl;
	}
	void functionAddParameter(int param_offset, std::string reg_1) {
		// NOTE: order is the reverse of what you pushed to stack
		// so it should be called in reverse order
		asm_file << "        mov qword [rbp-" << param_offset << "], " << reg_1 << std::endl;
	}
	void functionEnd() {
		asm_file << "        add rsp, 8*64" << std::endl;
		asm_file << "        pop rbp" << std::endl;
		asm_file << "        ret" << std::endl;
	}

	void returnRegister(std::string reg_1) {
		asm_file << "        push " << reg_1 << std::endl;
	}

	void testIntPrint() {
		asm_file << "        ;; test print" << std::endl;
		asm_file << "        push 12345" << std::endl;
		asm_file << "        pop rax" << std::endl;
		asm_file << "        invoke printf, intprint, rax" << std::endl; // I dont know why using call doesnt work
	}

	void printComment(std::string comment) {
		asm_file << "        ;; " << comment << std::endl;
	}

	void makeDeclaration(int offset) {
		// 0 initialize variable
		//asm_file << "        ;; make declaration" << std::endl;
		asm_file << "        mov qword [rbp-" << offset << "], 0" << std::endl;
	}

	void makeAssignment(int offset) {
		//asm_file << "        ;; make assignment" << std::endl;
		asm_file << "        mov qword [rbp-" << offset << "], rax" << std::endl;
	}

	void makePrintInt() {
		//asm_file << "        ;; print integer" << std::endl;
		asm_file << "        invoke printf, intprint, rax" << std::endl;
	}

	void makePushVariable(int offset) {
		//asm_file << "        ;; push variable" << std::endl;
		asm_file << "        push qword [rbp-" << offset << "]" << std::endl;
	}

	void makePushIntConstant(int number) {
		//asm_file << "        ;; push int constant" << std::endl;
		asm_file << "        push " << number << std::endl;
	}
	void makeMoveVariableToReg(int offset, std::string reg) {
		//asm_file << "        ;; move variable" << std::endl;
		asm_file << "        mov " << reg << ", qword [rbp-" << offset << "]" << std::endl;
	}
	void makeMoveConstIntToReg(int number, std::string reg) {
		//asm_file << "        ;; move constant int" << std::endl;
		asm_file << "        mov " << reg << ", " << number << std::endl;
	}
	void addRegisters(std::string reg_1, std::string reg_2) {
		//asm_file << "        ;; add two registers" << std::endl;
		asm_file << "        add " << reg_1 << ", " << reg_2 << std::endl;
	}
	void subRegisters(std::string reg_1, std::string reg_2) {
		//asm_file << "        ;; sub two registers" << std::endl;
		asm_file << "        sub " << reg_1 << ", " << reg_2 << std::endl;
	}
	void moveRegisters(std::string reg_1, std::string reg_2) {
		//asm_file << "        ;; moving registers" << std::endl;
		asm_file << "        mov " << reg_1 << ", " << reg_2 << std::endl;
	}
	void imulRegisters(std::string reg_1, std::string reg_2) {
		//asm_file << "        ;; imul two registers" << std::endl;
		asm_file << "        imul " << reg_1 << ", " << reg_2 << std::endl;
	}
	void idivRegisters(std::string reg_1, std::string reg_2) {
		//asm_file << "        ;; idiv two registers" << std::endl;
		asm_file << "        mov rcx, " << reg_1 << std::endl;
		asm_file << "        mov r8, " << reg_2 << std::endl;
		asm_file << "        xor rdx, rdx" << std::endl;
		asm_file << "        mov rax, rcx" << std::endl;
		asm_file << "        idiv r8" << std::endl;
	}
	void notRegister(std::string reg_1) {
		//asm_file << "        ;; not(expr)" << std::endl;
		asm_file << "        cmp " << reg_1 << ", " << "0" << std::endl;
		asm_file << "        setne cl" << std::endl;
		asm_file << "        xor cl, -1" << std::endl;
		asm_file << "        and cl, 1" << std::endl;
		asm_file << "        movzx edx, cl" << std::endl;
		asm_file << "        movsxd " << reg_1 << ", edx" << std::endl;
	}

	void pushRegister(std::string reg_1) {
		asm_file << "        push " << reg_1 << std::endl;
	}
	void popToRegister(std::string reg_1) {
		asm_file << "        pop " << reg_1 << std::endl;
	}

	void orRegisters(std::string reg_1, std::string reg_2) {
		// Maybe just compare these two to 0 ???
		asm_file << "        cmp " << reg_1 << ", 0" << std::endl;
		asm_file << "        jne LABEL_AND_" << label_counter << std::endl;
		asm_file << "        cmp " << reg_2 << ", 0" << std::endl;
		asm_file << "        setne al" << std::endl;
		asm_file << "LABEL_AND_" << label_counter << ":" << std::endl;
		label_counter++;

		asm_file << "        and al, 1" << std::endl;
		asm_file << "        movzx " << reg_1 << ", al" << std::endl;
	}
	void andRegisters(std::string reg_1, std::string reg_2) {
		// Maybe just compare these two to 0 ???
		asm_file << "        cmp " << reg_1 << ", 0" << std::endl;
		asm_file << "        je LABEL_AND_" << label_counter << std::endl;
		asm_file << "        cmp " << reg_2 << ", 0" << std::endl;
		asm_file << "        setne al" << std::endl;
		asm_file << "LABEL_AND_" << label_counter << ":" << std::endl;
		label_counter++;

		asm_file << "        and al, 1" << std::endl;
		asm_file << "        movzx " << reg_1 << ", al" << std::endl;
	}
	void equalsRegisters(std::string reg_1, std::string reg_2) {
		asm_file << "        cmp " << reg_1 << ", " << reg_2 << std::endl;
		asm_file << "        sete dl" << std::endl;
		asm_file << "        and dl, 1" << std::endl;
		asm_file << "        movzx " << reg_1 << ", dl" << std::endl;
	}
	void unequalsRegisters(std::string reg_1, std::string reg_2) {
		asm_file << "        cmp " << reg_1 << ", " << reg_2 << std::endl;
		asm_file << "        setne dl" << std::endl;
		asm_file << "        and dl, 1" << std::endl;
		asm_file << "        movzx " << reg_1 << ", dl" << std::endl;
	}
	void greaterEqualsRegisters(std::string reg_1, std::string reg_2) {
		asm_file << "        cmp " << reg_1 << ", " << reg_2 << std::endl;
		asm_file << "        setge dl" << std::endl;
		asm_file << "        and dl, 1" << std::endl;
		asm_file << "        movzx " << reg_1 << ", dl" << std::endl;
	}
	void lesserEqualsRegisters(std::string reg_1, std::string reg_2) {
		asm_file << "        cmp " << reg_1 << ", " << reg_2 << std::endl;
		asm_file << "        setle dl" << std::endl;
		asm_file << "        and dl, 1" << std::endl;
		asm_file << "        movzx " << reg_1 << ", dl" << std::endl;
	}
	void greaterRegisters(std::string reg_1, std::string reg_2) {
		asm_file << "        cmp " << reg_1 << ", " << reg_2 << std::endl;
		asm_file << "        setg dl" << std::endl;
		asm_file << "        and dl, 1" << std::endl;
		asm_file << "        movzx " << reg_1 << ", dl" << std::endl;
	}
	void lesserRegisters(std::string reg_1, std::string reg_2) {
		asm_file << "        cmp " << reg_1 << ", " << reg_2 << std::endl;
		asm_file << "        setl dl" << std::endl;
		asm_file << "        and dl, 1" << std::endl;
		asm_file << "        movzx " << reg_1 << ", dl" << std::endl;
	}

	void makeWhileStart(int wh_label_count) {
		asm_file << "LABEL_WH_" << wh_label_count << ":" << std::endl;
		// Expression needs to be evaluated here
	}
	void makeWhileMiddle(std::string reg_1, int wh_label_count) {
		asm_file << "        cmp " << reg_1 << ", 1" << std::endl;
		asm_file << "        jne LABEL_WH_" << wh_label_count << std::endl;
		// Should call the statement sequence after while here
	}

	void makeWhileEnd(int wh_label_count) {
		asm_file << "        ;; while end" << std::endl;
		asm_file << "        jmp LABEL_WH_" << (wh_label_count - 1) << std::endl;
		asm_file << "LABEL_WH_" << wh_label_count << ":" << std::endl;
	}

	void makeIfStart(std::string reg_1, int label_count) {
		asm_file << "        cmp " << reg_1 << ", 1" << std::endl;
		asm_file << "        jne LABEL_IF_" << label_count << std::endl;
	}

	void makeIfEnd(int label_count) {
		asm_file << "LABEL_IF_" << label_count << ":" << std::endl;
	}

	// puts return value in register reg_1
	void makeReturn(std::string reg_1, std::string reg_2) {
		asm_file << "        ;; Return from function" << std::endl;
		asm_file << "        add rsp, 8*64" << std::endl;
		asm_file << "        mov " << reg_1 << ", " << reg_2 << std::endl;
		asm_file << "        pop rbp" << std::endl;
		asm_file << "        ret" << std::endl;
	}

	void callFunction(std::string func_name) {
		asm_file << "        call " << func_name << std::endl;
	}


};
