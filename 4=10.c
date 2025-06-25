#include <stdio.h> 
#include <stdbool.h>
#define NUM_OF_NUMS 4
/*
great. one more thing - when we use MAGICs, we save them with capital letters - NUM_OF_NUMS.
this way, while reading the code its easy to notice it. done

the code is complicated. the reason - its human thinking, and not using the computer abilities
i think it will take more time to reach the best code, but lets start from this:
you need to seperate MORE to functions.
for example - you dont have a basic calc(int num1, int num2, char op) func. 
its in the big calculate func, and its very clumsy and inelegant.

think about more functions you can make to make your code easier to read.

we have two main rules (for now) when it comes to code with functions:
- the function needs to be no longer than four fingers that you put horizonally on the screen. thats about 15-20 code lines.
- the main() shouldnt hold complicated logic. only simple and understandable actions.
for example, the main() of FIFA should lok like this:
int main() {
	loading_screen();
 	start();
  	activate_menu();
   	exit();
}
you ask yourself how? every function hold many other functions, etc. that way, its very easy to refactor the code
for example, the activate_menu() will look something like this:
void activate_menu() {
	while (!EXIT_FLAG) {
 		if (selection=MULTIPLAYER) {activate_multiplayer()};
   		if (selection=TOURNAMENT) {activate_tournament()};
     		if (selection=SINGLE_MATCH) {activate_single_match()};
     		if (selection=EXIT) (EXIT_FLAG=1);
	}
}

only the most bottom and tatic functions actually holds logic. most of the code is in reasonable "english"
good luck!

this code doesn't work right now (the calculate func specifically).
the variabale "index" doesn't change after calling Multiply_and_Divide function although its supposed to modify it.
the multiply func works well and the list "result", for example, is actually updated.
but index is changed during running Multiply but after that it becomes 0 again (I printed it for checking).
I tried to not initialize it (like I did with result) but the output was same. 

out of this, the main is still really complicated but i guess i will learn later the tools to simplify it. 
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


