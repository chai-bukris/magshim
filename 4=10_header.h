#pragma once
int NUM_OF_NUMS = 0;
int target = 0;
char operations[] = { '+', '-', '*', '/' };
int* numbers;
char* temp_ops;
double* temp_result;
bool* used;

double basic_calc(double num1, double num2, char op); // basic calculation function

int multiply_and_divide(double nums[], char ops[], double result[]);
	// calculates only multiplying and dividing operators first for respecting the order of arithmetic operations

void add_and_substract(double result[], int index, char ops[]);

double calculate_expression(double nums[], char ops[]);

double calculate_parens(int nums[], char ops[], int start_paren, int end_paren);

double calculate_all_numbers(int nums[], char ops[], int start_paren, int end_paren); 
	// calculates the exercise with given numbers, operators and parentheses

void print_with_parens(int nums[], char ops[], int start, int end);

void base_4(char ops[], int i); 

int combine_operators(int nums[]); // trys any operators combination for a given numbers order

int find_exercise(int numbers_filled, int current_numbers[]);

int verify(int numbers[]); // ensures the input is proper
