#include <stdio.h> 
#include <stdbool.h>
double calculate(int nums[], char ops[]) {
	double help[4];
	help[0] = nums[0];
	int saman = 0;
	for (int i = 0; i < 3; i++) {
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
	int numbers[4];
	int arr[4];
	printf("Enter 4 numbers between 0 and 9: ");
	arr[0] = scanf_s("%d", &numbers[0]);
	arr[1] = scanf_s("%d", &numbers[1]);
	arr[2] = scanf_s("%d", &numbers[2]);
	arr[3] = scanf_s("%d", &numbers[3]);
	for (int i = 0; i < 4; i++) {
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
	char ops[3];
	int nums[4];
	for (int m = 0; m < 4; m++) {
		nums[0] = numbers[m];
		for (int a = 0; a < 4; a++) {
			ops[0] = operations[a];
			for (int n = 0; n < 4; n++) {
				if (m == n) {
					continue;
				}
				nums[1] = numbers[n];
				for (int b = 0; b < 4; b++) {
					ops[1] = operations[b];
					for (int o = 0; o < 4; o++) {
						if (o == n || o == m) {
							continue;
						}
						nums[2] = numbers[o];
						for (int c = 0; c < 4; c++) {
							ops[2] = operations[c];
							for (int p = 0; p < 4; p++) {
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

