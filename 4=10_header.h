#pragma once
#define NUM_OF_NUMS 4
char operations[] = { '+', '-', '*', '/' };
int numbers[NUM_OF_NUMS];
char temp_ops[NUM_OF_NUMS - 1];
bool used[NUM_OF_NUMS];
double basic_calc(double num1, double num2, char op);
int multiply_and_divide(int nums[], char ops[], double result[]);
double add_and_substract(double result[], int index, char ops[]);
double calculate_all_numbers(int nums[], char ops[]);
void base_4(char ops[], int i);
int combine_operators(int nums[]);
int find_exercise(int numbers_filled, int current_numbers[]);
int verify(int numbers[]);
