# Easy Compiler

This is a compiler for a basic programming language. 
It supports scopes, order of operations and type checking.
The compiler uses flat assembler to generate Windows executable files.

## How to run
- Compile all files in /src or use the Visual Studio solution.
- Use `./easy-compiler.exe program_name.txt`
- install flat assembler for Windows https://flatassembler.net/download.php
- Use flat assembler generate a .exe file from program.asm or run it there directly

## How it works

Compiling a program is split into 4 (somewhat) separate stages:

**Lexing**
	- Tokenizing all keywords, names, and symbols in the input file.
 
**Parsing** 
	- Grammar and LL1 table are read from files in /data.
	- Using an LL1 parser to check for syntax errors in the code.
	- Constructing an AST (Abstract Syntax Tree) for compilation.
 
**Semantic checking** 
	- After the syntax tree is built, it is analyzed for scopes of variables, type checking, etc.
	- Construct symbol tables for variables and functions.
 
**Code Generating**
	- Using the AST, appropriate assembly code is generated.
	- A recursive method is used to correctly perform order of operations.
	
After compilation, flat-assembler can run the generated .asm file, or generate an executable.
