#include <stdio.h> 
#include <stdbool.h>
#include <math.h>

#define NUM_OF_NUMS 4

char operations[] = { '+', '-', '*', '/' };
int numbers[NUM_OF_NUMS];
char temp_ops[NUM_OF_NUMS - 1];
/*
seems like the code is RIGHT. congrats


now some cosmetic fixes i think you sould improve:
"calc" was a good name, before you had like 4 functions that calculate something. call it something more clear, like basic_calc or any other name that indicates it is the most basic action
--
the fact that you have a multiply and divide function makes it more reasonable to have add and substract function, although its a much simpler one.
then, when someone reads it its clear that you first /* and then +-
--
multiply_and_divide - you have a compicated if-else sequence. you can do it a bit better - longer, but simpler. think how and do it
(hint - we will do everything to avoid terms like (|| || &&), or (&& ||). each if should be one logic unit, and you check both if its (/ or *), and validate its not 0, all in one logic unit)
--
a suggestion that im not sure of - will it be more convenient if we use MAGICs for the operators?
what do we prefer:
temp_ops[i] == '*'
or 
temp_ops[i] == MULTIPLY
--
In my opinion combine_operators function is a bit too long. see if you can split it into 2 simpler functions.
{for you to learn to fix yourself - i actually dont fully understand the base_4, but still managed to understand that this function needs a split. 
why? because there is some logic under two for loops, and this logic s only under the lower one - which means i dont interfere in the middle of the pass between the two for loops. thus, it seems that there is an INDEPENDENT logic unit there- should be in a function}
--
actually, your documentation is great. not too long, not too short, only when its really needed. great.


after all of that fixes, give a look to the first version (you can see it here on github), and see how important it to write BEAUTIFUL and READABLE code. you cant even compare them.
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
	for (int i = 0; i < NUM_OF_NUMS - 1; i++) {
		temp_ops[i] = ops[i]; // we want to keep ops unmodified for later printing
	} 
	int index = 0; // used for modifying the lists and preparing them for the next calculation actions
	result[0] = nums[0];
	for (int i = 0; i < NUM_OF_NUMS - 1; i++) {
		if (temp_ops[i] == '*' || (temp_ops[i] == '/' && nums[i + 1] != 0)) {
			result[index] = calc(result[index], nums[i + 1], temp_ops[i]);
		}
		else if (temp_ops[i] == '/' && nums[i + 1] == 0) {return -1;}
		else {
			temp_ops[index] = temp_ops[i];
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
		result[0] = calc(result[0], result[i + 1], temp_ops[i]); // all the calculations are in result[0]
	}
	return result[0];
}

int combine_operators(int nums[]) { // trys any operators combination for a given numbers order
	char ops[NUM_OF_NUMS - 1];
	for (int i = 0; i < pow(4, NUM_OF_NUMS - 1); i++) { // iterates as many times as the number of possible combinations
		int base_4 = i;
		for (int j = 0; j < NUM_OF_NUMS - 1; j++) {
			ops[j] = operations[base_4 % 4]; // hard logic. we treat i like a base 4 number when each digit represents an operator
			base_4 /= 4;
		}
		if (calculate_all_numbers(nums, ops) == 10) {
			// print the exercise if it's result is 10
			for (int j = 0; j < NUM_OF_NUMS - 1; j++) {
				printf("%d %c ", nums[j], ops[j]);
			}
			printf("%d", nums[NUM_OF_NUMS - 1]);
			return 0;
		}
	}
	return -1;
}

bool used[NUM_OF_NUMS]; // prevents doubling a number

int find_exercise(int numbers_filled, int current_numbers[]) {
	if (numbers_filled == NUM_OF_NUMS) {
		return combine_operators(current_numbers);
	}
	for (int i = 0; i < NUM_OF_NUMS; i++) {
		if (!used[i]) {
			current_numbers[numbers_filled] = numbers[i];
			used[i] = true;
			if (find_exercise(numbers_filled + 1, current_numbers) == 0) { // call this function recursively until all numbers are filled
				return 0;
			}
			used[i] = false; // if the exercise was wrong - start again 
		}
	}
	return -1; // indicates that no exercise was found
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
	printf("Enter 4 numbers between 0 and 9: ");
	int x = verify(numbers);
	if (x == 0) {return 0;}
	int current_numbers[NUM_OF_NUMS];
	int y = find_exercise(0, current_numbers);
	if (y == -1) {
		printf("no exercise was found");
	}
	return 0;
}


