# compiler
Compiles a code written in a custom-made language into runnable assembly code

1) Install NASM: https://www.nasm.us/
2) Write the code you want to run and put it in a file (for example: code.txt)
3) Run the following commands:
gcc main.cpp -o main.exe
main.exe < "filename.txt" < maintest.asm
nasm -f win64 maintest.asm -o maintest.obj
gcc maintest.obj -o maintest.exe
maintest.exe
