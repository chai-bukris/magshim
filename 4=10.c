#include <stdio.h> 
#include <stdbool.h>
#define NUM_OF_NUMS 4
/*
this code doesn't work right now (the calculate func specifically).
the variabale "index" doesn't change after calling Multiply_and_Divide function although its supposed to modify it.
the multiply func works well and the list "result", for example, is actually updated.
but index is changed during running Multiply but after that it becomes 0 again (I printed it for checking).
I tried to not initialize it (like I did with result) but the output was same. 

out of this, the main is still really complicated but i guess i will learn later the tools to simplify it. 

In C and many other languages, you can't change a variable from inside a func if it wasm allocated outside of it. 
If you want to understand it deeply i recommend you to read about the stack and how functions in C works, that will explain it well.
at the bottom line, when you change index in the function it will not affect index in main. 
thus, you need to return the index value, and re-assign it after the function. you can also use pointers(thats the reason "result" list do change), but we will meet it lately.
thats for functionality, that the first fixes you should make. (read about the stack and fix the code so it will work)

afterwards, i want you to search for a more elegant way to write the calc function.
hint: what if you had 10 cases? you would write 10 times else if? maybe there's a way a bit more fit.

in addition, you have one function called calc and another one calculate. hmmm... think a bit more about naming.
for "Multiply_and_Divide", its a good name but its written in strange way. read about function naming methods:
snake_case
CamelCase
and choose one. in C it is common to use snake_case, but its your choice and what you think will be more convinient to you.

finally, i have to admit that the code is still fully understandable. yes, it builded a little more beautiful with functions.
but its not intuitive. if i have a calc func, why whould i have another func that makes calculations between * and /?
of course, you have a reason, but as a reader i can be very confused. 
the solution is to DOCUMENT your code. read about documentation (a cross-language term), choose one method that you like and document your code.
i recommend to choose a short one so tou will not get tired of it fastly, its maybe one of the nost boring things to do while coding but its important when working on large code-bases or complicated ones.
good luck!
*/ 

double calc(double num1, double num2, char op) {
	if (op == '+') {
		return num1 + num2;
	}
	else if (op == '-') {
		return num1 - num2;
	}
	else if (op == '*') {
		return num1 * num2;
	}
	else {
		return num1 / num2;
	}
}

int Multiply_and_Divide(int nums[], char ops[], double result[], int index) {
	result[0] = nums[0];
	for (int i = 0; i < NUM_OF_NUMS - 1; i++) {
		if (ops[i] == '*' || (ops[i] == '/' && nums[i + 1] != 0)) {
			result[index] = calc(result[index], nums[i + 1], ops[i]);
		}
		else if (ops[i] == '/' && nums[i + 1] == 0) {return 0;}
		else {
			ops[index] = ops[i];
			index++;
			result[index] = nums[i + 1];
		}
	}
	return 1;
}

double calculate(int nums[], char ops[]) {
	int index = 0;
	double result[NUM_OF_NUMS];
	int x = Multiply_and_Divide(nums, ops, result, index);
	printf("%d\n", index);
	if (x == 0) {return 0;}
	for (int i = 0; i < index; i++) {
		result[0] = calc(result[0], result[i + 1], ops[i]);
	}
	return result[0];
}

int verify(int numbers[]) {
	int arr[NUM_OF_NUMS];
	for (int i = 0; i < NUM_OF_NUMS; i++) {
		arr[i] = scanf_s("%d", &numbers[i]);
		if (arr[i] != 1) {
			printf("bruh, I told you to enter numbers");
			return 0;
		}
		else if (numbers[i] > 9 || numbers[i] < 0) {
			printf("enter in the range of 0-9. try again");
			return 0;
		}
	}
	return 1;
}

int main() {
	int trials[4] = {1, 2, 3, 4};
	char trys[3] = {'+', '+', '+'};
	int h = calculate(trials, trys);
	printf("%d\n", h);
	int numbers[NUM_OF_NUMS];
	printf("Enter 4 numbers between 0 and 9: ");
	int x = verify(numbers);
	if (x == 0) {return 0;}
	char operations[] = {'+', '-', '*', '/'};
	char ops[NUM_OF_NUMS - 1];
	int nums[NUM_OF_NUMS];
	for (int m = 0; m < NUM_OF_NUMS; m++) {
		nums[0] = numbers[m];
		for (int a = 0; a < NUM_OF_NUMS; a++) {
			ops[0] = operations[a];
			for (int n = 0; n < NUM_OF_NUMS; n++) {
				if (m == n) {
					continue;
				}
				nums[1] = numbers[n];
				for (int b = 0; b < NUM_OF_NUMS; b++) {
					ops[1] = operations[b];
					for (int o = 0; o < NUM_OF_NUMS; o++) {
						if (o == n || o == m) {
							continue;
						}
						nums[2] = numbers[o];
						for (int c = 0; c < NUM_OF_NUMS; c++) {
							ops[2] = operations[c];
							for (int p = 0; p < NUM_OF_NUMS; p++) {
								if (p == n || p == m || p == o) {
									continue;
								}
								nums[3] = numbers[p];
								printf("%d %c %d %c %d %c %d\n", nums[0], ops[0], nums[1], ops[1], nums[2], ops[2], nums[3]);
								if (calculate(nums, ops) == 10) {
									printf("great");
									return 0;
								}
							}

						}
					}

				}
			}

		}
	}

	return 0;
}


