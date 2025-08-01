#include <stdio.h> 
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include "4=10_header.h"

double basic_calc(double num1, double num2, char op) { 
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

int multiply_and_divide(double nums[], char ops[], double result[]) { 
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

void add_and_substract(double result[], int index, char ops[]) {
	for (int i = 0; i < index; i++) {
		result[0] = basic_calc(result[0], result[i + 1], ops[i]); // all the calculations are in result[0]
	}
}

double calculate_expression(double nums[], char ops[]) {
	int index = 0; // used for measuring the list's length after multiplying and dividing
	double* result = (double*)malloc(NUM_OF_NUMS * sizeof(double));
	index = multiply_and_divide(nums, ops, result);
	if (index == -1) {
		free(result);
		return 0;
	}
	add_and_substract(result, index, temp_ops);
	double expression_result = result[0];
	free(result);
	return expression_result;
}

double calculate_parens(int nums[], char ops[], int start_paren, int end_paren) {
	double* paren_nums = (double*)malloc(NUM_OF_NUMS * sizeof(double));
	char* paren_ops = (char*)malloc((NUM_OF_NUMS - 1) * sizeof(char));
	for (int i = 0; i <= end_paren - start_paren; i++) {
		paren_nums[i] = nums[start_paren + i - 1];
	}
	for (int i = 0; i < end_paren - start_paren; i++) {
		paren_ops[i] = ops[start_paren + i - 1];
	}
	double result = calculate_expression(paren_nums, paren_ops);
	free(paren_nums);
	free(paren_ops);
	return result;
}

double calculate_all_numbers(int nums[], char ops[], int start_paren, int end_paren) {
	double parens_result = calculate_parens(nums, ops, start_paren, end_paren);
	char* ex_paren_ops = (char*)malloc((NUM_OF_NUMS - 1) * sizeof(char));
	for (int i = 0; i < start_paren - 1; i++) { // builds a new list after calculating inside the parentheses
		temp_result[i] = nums[i];
		ex_paren_ops[i] = ops[i];
	}
	temp_result[start_paren - 1] = parens_result; // inserts the parentheses' result in their place
	int ex_index = start_paren;
	for (int i = end_paren; i < NUM_OF_NUMS; i++) {
		temp_result[ex_index] = nums[i];
		ex_paren_ops[ex_index - 1] = ops[i - 1];
		ex_index++;
	}
	double result = calculate_expression(temp_result, ex_paren_ops);
	free(ex_paren_ops);
	return result;
}

void base_4(char ops[], int i) { // create an operations sequence according to a current iteration
	int base_4 = i;
	for (int j = 0; j < NUM_OF_NUMS - 1; j++) {
		ops[j] = operations[base_4 % 4]; // hard logic. we treat i like a base 4 number. each digit represents an operator
		base_4 /= 4;
	}
}

void print_with_parens(int nums[], char ops[], int start, int end) {
	for (int j = 0; j < NUM_OF_NUMS; j++) {
		if (j == start-1) {
			printf("(");
		}
		printf("%d", nums[j]);
		if (j == end - 1) {
			printf(")");
		}
		if (j < NUM_OF_NUMS - 1) {
			printf("%c", ops[j]);
		}
	}
}

int combine_operators(int nums[]) {
	char* ops = (char*)malloc((NUM_OF_NUMS - 1) * sizeof(char));
	double* double_nums = (double*)malloc(NUM_OF_NUMS * sizeof(double));
	for (int j = 0; j < NUM_OF_NUMS; j++) {
		double_nums[j] = (double)nums[j];
	}
	for (int i = 0; i < pow(4, NUM_OF_NUMS - 1); i++) { // iterates as many times as the number of possible combinations
		base_4(ops, i);
		if (calculate_expression(double_nums, ops) == target) { // print the exercise if it's result equals the target
			for (int j = 0; j < NUM_OF_NUMS - 1; j++) {
				printf("%d %c ", nums[j], ops[j]);
			}
			printf("%d", nums[NUM_OF_NUMS - 1]);
			free(ops);
			free(double_nums);
			return 0;
		}
		for (int start = 1; start < NUM_OF_NUMS; start++) { // try with parentheses
			for (int end = start + 1; end <= NUM_OF_NUMS; end++) {
				if (calculate_all_numbers(nums, ops, start, end) == target) {
					print_with_parens(nums, ops, start, end);
					free(ops);
					free(double_nums);
					return 0;
				}
			}
		}
	}
	free(ops);
	free(double_nums);
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
			if (find_exercise(numbers_filled + 1, current_numbers) == 0) { // calls recursively until all numbers are filled
				return 0;
			}
			used[i] = false; // if the exercise was wrong - start again 
		}
	}
	return -1; // indicates that no exercise was found
}

int verify(int numbers[]) {
	int valid = 1;
	for (int i = 0; i < NUM_OF_NUMS; i++) {
		valid = scanf_s("%d", &numbers[i]);
		if (valid != 1) {
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

int main(int argc, char* argv[]) {
	target = 10;
	NUM_OF_NUMS = 4;
	if (argc >= 2) {
		target = atoi(argv[1]);
	}
	if (argc == 3) {
		NUM_OF_NUMS = atoi(argv[2]);
	}
	numbers = (int*)malloc(NUM_OF_NUMS * sizeof(int));
	temp_ops = (char*)malloc((NUM_OF_NUMS - 1) * sizeof(char));
	temp_result = (double*)malloc(NUM_OF_NUMS * sizeof(double));
	used = (bool*)malloc(NUM_OF_NUMS * sizeof(bool));
	for (int i = 0; i < NUM_OF_NUMS; i++) {
		used[i] = false;
	}
	printf("Enter %d numbers between 0 and 9: ", NUM_OF_NUMS);
	if (verify(numbers) == 0) {
		free(numbers);
		free(temp_ops);
		free(temp_result);
		free(used);
		return 0;
	}
	int* current_numbers = (int*)calloc(NUM_OF_NUMS, sizeof(int));
	if (find_exercise(0, current_numbers) == -1) {
		printf("no exercise was found");
	}
	free(current_numbers);
	free(numbers);
	free(temp_ops);
	free(temp_result);
	free(used);
	return 0;
}