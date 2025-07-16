#pragma once
#define NUM_OF_NUMS 4
char operations[] = { '+', '-', '*', '/' };
int numbers[NUM_OF_NUMS];
char temp_ops[NUM_OF_NUMS - 1];
bool used[NUM_OF_NUMS];
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
