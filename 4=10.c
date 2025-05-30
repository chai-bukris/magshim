#include <stdio.h> 
#include <stdbool.h>
#define numofnums 4
/*
If im new to this code and trying to understad whats going on, it will be very hard to me.
one reason is that there are lots of numbers and i cant undderstand whats their MEANING.
what is this 4? what is that 3? fixed 
I addition, lets assume that for some reason, you were asked to be able to get 5 numbers and not only 4. what a shame...
you will need to change every time that 4 apears to 5. that will take you a lot of time. (and we put aside the logical problems)
I want you to change/add code, in a way that you will be able to change only 1 codeline in order to change the numbers count.
HINT: read about MAGIC NUMBER. you are already familiar with them, and this is their main purpose. fixed
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

