#include <stdio.h> 
#include <stdbool.h>
#define NUM_OF_NUMS 4
/*
thats better.
now we have a problem - you solved in a great way for question with 4 numbers. what if we had 10 numbers?
find more generic solution that will fit.
In addition, you can still seperate your main logic to functions. i see there lots of logic and its very complicated!
your main should be readable to someone like Yam - know something about computer and software but not a professional.

at this time i didnt gave you specific fixes - cause i want you to think hard. its a hard exercise whn you need to write it right, but i believe you can do it if you would try enough.
*/ 

double calc(double num1, double num2, char op) { // basic calculation function
	switch (op) {
		case '+':
			return num1 + num2;
		case '-':
			return num1 - num2;
		case '/':
			return num1 / num2;
		case '*':
			return num1 * num2;
	}
}

int multiply_and_divide(int nums[], char ops[], double result[]) { 
	// calculates only multiplying and dividing operators for respecting the order of arithmetic operations
	int index = 0; // used for modifying the lists and preparing them for the next calculation actions
	result[0] = nums[0];
	for (int i = 0; i < NUM_OF_NUMS - 1; i++) {
		if (ops[i] == '*' || (ops[i] == '/' && nums[i + 1] != 0)) {
			result[index] = calc(result[index], nums[i + 1], ops[i]);
		}
		else if (ops[i] == '/' && nums[i + 1] == 0) {return -1;}
		else {
			ops[index] = ops[i];
			index++;
			result[index] = nums[i + 1];
		}
	}
	return index;
}

double calculate_all_numbers(int nums[], char ops[]) { // calculates the exercise with the given numbers and operators
	int index = 0; // used for measuring the list's length after multiplying and dividing
	double result[NUM_OF_NUMS];
	index = multiply_and_divide(nums, ops, result);
	if (index == -1) {return 0;}
	for (int i = 0; i < index; i++) {
		result[0] = calc(result[0], result[i + 1], ops[i]); // all the calculations are in result[0]
	}
	return result[0];
}

int verify(int numbers[]) { // ensures the input is proper
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
	int numbers[NUM_OF_NUMS];
	printf("Enter 4 numbers between 0 and 9: ");
	int x = verify(numbers);
	if (x == 0) {return 0;}
	char operations[] = {'+', '-', '*', '/'};
	char ops[NUM_OF_NUMS - 1];
	int nums[NUM_OF_NUMS];
	for (int m = 0; m < NUM_OF_NUMS; m++) { // going through all the possible combinations of the numbers and operators
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
								if (calculate_all_numbers(nums, ops) == 10) {
									// print the exercise if it's result is 10
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


