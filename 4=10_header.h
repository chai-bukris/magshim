#pragma once
#define NUM_OF_NUMS 4
char operations[] = { '+', '-', '*', '/' };
int numbers[NUM_OF_NUMS];
char temp_ops[NUM_OF_NUMS - 1];
double temp_result[NUM_OF_NUMS];
bool used[NUM_OF_NUMS] = {false};

double basic_calc(double num1, double num2, char op); // basic calculation function

int multiply_and_divide(double nums[], char ops[], double result[]);
	// calculates only multiplying and dividing operators first for respecting the order of arithmetic operations

void add_and_substract(double result[], int index, char ops[]);

double calculate_expression(double nums[], char ops[]);

double calculate_parens(int nums[], char ops[], int start_paren, int end_paren);

double calculate_all_numbers(int nums[], char ops[], int start_paren, int end_paren);

void print_with_parens(int nums[], char ops[], int start, int end);

void base_4(char ops[], int i); // calculates the exercise with the given numbers and operators

int combine_operators(int nums[]); // trys any operators combination for a given numbers order

int find_exercise(int numbers_filled, int current_numbers[]);

int verify(int numbers[]); // ensures the input is proper
