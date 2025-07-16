#include <stdio.h> 
#include <stdbool.h>
#include <math.h>
#include "4=10_header.h"

/*
it feels so silly, I just declare function in a seperate file, and I don't have too much programs to use the functions...
can't understand how it helps here, only complicates
*/

double basic_calc(double num1, double num2, char op) { // basic calculation function
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
	// calculates only multiplying and dividing operators first for respecting the order of arithmetic operations
	for (int i = 0; i < NUM_OF_NUMS - 1; i++) {
		temp_ops[i] = ops[i]; // we want to keep ops unmodified for later printing
	}
	int index = 0; // used for modifying the lists and preparing them for the next calculation actions
	result[0] = nums[0];
	for (int i = 0; i < NUM_OF_NUMS - 1; i++) {
		if (temp_ops[i] == '*' || (temp_ops[i] == '/' && nums[i + 1] != 0)) {
			result[index] = basic_calc(result[index], nums[i + 1], temp_ops[i]);
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

double add_and_substract(double result[], int index, char ops[]) {
	for (int i = 0; i < index; i++) {
		result[0] = basic_calc(result[0], result[i + 1], ops[i]); // all the calculations are in result[0]
	}
}

double calculate_all_numbers(int nums[], char ops[]) { // calculates the exercise with the given numbers and operators
	int index = 0; // used for measuring the list's length after multiplying and dividing
	double result[NUM_OF_NUMS];
	index = multiply_and_divide(nums, ops, result);
	if (index == -1) {return 0;}
	add_and_substract(result, index, temp_ops);
	return result[0];
}

void base_4(char ops[], int i) { // create an operations sequence according to a current iteration
	int base_4 = i;
	for (int j = 0; j < NUM_OF_NUMS - 1; j++) {
		ops[j] = operations[base_4 % 4]; // hard logic. we treat i like a base 4 number. each digit represents an operator
		base_4 /= 4;
	}
}

int combine_operators(int nums[]) { // trys any operators combination for a given numbers order
	char ops[NUM_OF_NUMS - 1];
	for (int i = 0; i < pow(4, NUM_OF_NUMS - 1); i++) { // iterates as many times as the number of possible combinations
		base_4(ops, i);
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

int find_exercise(int numbers_filled, int current_numbers[]) {
	if (numbers_filled == NUM_OF_NUMS) {
		return combine_operators(current_numbers);
	}
	for (int i = 0; i < NUM_OF_NUMS; i++) {
		if (!used[i]) { // prevents doubling a number
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


