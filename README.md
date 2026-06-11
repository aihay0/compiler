# Compiler
Compiles a code written in a custom-made language into runnable assembly code

# How to use

1) Install NASM: https://www.nasm.us/
2) Write the code you want to run and put it in a file (for example: code.txt)
3) Run the following commands:
gcc main.cpp -o main.exe
main.exe < "filename.txt" < maintest.asm
nasm -f win64 maintest.asm -o maintest.obj
gcc maintest.obj -o maintest.exe
maintest.exe

# Example codes:

- Add 2 numbers:

```
int x;
int y;
input(x);
input(y);
output(x+y);
```

- First n prime numbers:

int n;
input(n);
int cur=2;
while(n>=0){
    int prime=1;
    for(int i=2;i*i<=cur;i=i+1){
	if(cur/i*i==cur){
	    prime=0;
	    break;
	}
    }
    if(prime==1){
	outputsp(cur);
	n=n-1;
    }
    cur=cur+1;
}

- Cool pattern:

int n;
input(n);
for(int i=0;i<n*2+3;i=i+1)
	output(0);
outputln(0);
for(int i=0;i<n;i=i+1){
	int c1=n-i-1;
	int c2=i*2+1;
	int c3=c1;
	output(0);
	while(c1>=0){
		output(1);
		c1=c1-1;
	}
	while(c2>=0){
		output(8);
		c2=c2-1;
	}
	while(c3>=0){
		output(1);
		c3=c3-1;
	}
	outputln(0);
}
for(int i=n-1;i>=0;i=i-1){
	int c1=n-i-1;
	int c2=i*2+1;
	int c3=c1;
	output(0);
	while(c1>=0){
		output(1);
		c1=c1-1;
	}
	while(c2>=0){
		output(8);
		c2=c2-1;
	}
	while(c3>=0){
		output(1);
		c3=c3-1;
	}
	outputln(0);
}
for(int i=0;i<n*2+3;i=i+1)
	output(0);
outputln(0);
