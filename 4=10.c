#include <stdio.h> 
#include <stdbool.h>
#define numofnums 4
/*
great. one moore thing - when we use MAGICs, we save them with capital letters - NUM_OF_NUMS.
this way, while reading the code its easy to notice it.

the code is complicated. the reason - its human thinking, and not using the computer abilities
i think it will take more time to reach the best code, but lets start from this:
you need to seperate MORE to functions.
for example - you dont have a basic calc(int num1, int num2, char op) func. 
its in the big calculate func, and its very clumsy and inelegant.

think about more functions you can make to make your code easier to read.

we have two main rules (for now) when it comes to code with functions:
- the function need to be no longer than four fingers that you put horizonally on the screen. thats about 15-20 code lines.
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
     		if (selection=EXIT) (EXIT_FLAF=1);
	}
}

only the most bottom and tatic functions actually holds logic. most of the code is in reasonable "english"
good luck!
*/ 

double calculate(int nums[], char ops[]) {
	double help[numofnums];
	help[0] = nums[0];
	int saman = 0;
	for (int i = 0; i < numofnums - 1; i++) {
		if (ops[i] == '*') {
			help[saman] *= nums[i + 1];
		}
		else if(ops[i] == '/') {
            if (nums[i + 1] == 0) {
				return 0;
			}
			help[saman] /= nums[i+1];
        }
		else {
			ops[saman] = ops[i];
			saman++;
			help[saman] = nums[i+1];
		}
	}
    for (int i = 0; i < saman; i++) {
        if (ops[i] == '+') {
            help[0] += help[i + 1];
        }
        else if (ops[i] == '-') {
            help[0] -= help[i + 1];
        }
    }
	return help[0];
}
int main() {
	int numbers[numofnums];
	int arr[numofnums];
	printf("Enter 4 numbers between 0 and 9: ");
	for (int i = 0; i < numofnums; i++) {
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
	char operations[] = {'+', '-', '*', '/'};
	char ops[numofnums - 1];
	int nums[numofnums];
	for (int m = 0; m < numofnums; m++) {
		nums[0] = numbers[m];
		for (int a = 0; a < numofnums; a++) {
			ops[0] = operations[a];
			for (int n = 0; n < numofnums; n++) {
				if (m == n) {
					continue;
				}
				nums[1] = numbers[n];
				for (int b = 0; b < numofnums; b++) {
					ops[1] = operations[b];
					for (int o = 0; o < numofnums; o++) {
						if (o == n || o == m) {
							continue;
						}
						nums[2] = numbers[o];
						for (int c = 0; c < numofnums; c++) {
							ops[2] = operations[c];
							for (int p = 0; p < numofnums; p++) {
								if (p == n || p == m || p == o) {
									continue;
								}
								nums[3] = numbers[p];
								if (calculate(nums, ops)==10) {
									printf("%d %c %d %c %d %c %d\n", nums[0], ops[0], nums[1], ops[1], nums[2], ops[2], nums[3]);
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

