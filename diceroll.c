#include <stdio.h>
#include<stdlib.h>
#include <time.h>
#include <unistd.h>
int roll() {
	int value = (rand() % 6) + 1;
	return value;
}
int compare(int n) {
	if (n < 4) {
		return 1;
	}
	return 0;
}
void fill(int array[], int size) {
	for (int i = 0; i < size; i++) {
		array[i] = (rand() % 6) + 1;
	}
}	
void replace(int array[], int size) {
	for (int i = 0; i < size; i++) {
		if (array[i] == 3) {
			array[i] = 0;
		}
	}
}
void reroll(int array[], int size) {
	int rRolls = 0;
	for (int i = 0; i < size; i++) {
		if (array[0] == 3) {
			if (array[i] != 3) {
				rRolls++;
			}
		}
		else {
			if (compare(array[i]) == 0) {
				rRolls++;
			}
		}
	}
	int temp[size];
	int tempValue;
	//printf("\n(%d) - Rolls\n", rRolls);
	for (int i = 0; i < size; i++) {
		if (array[0] == 3) {
			if (array[i] != 3) {
				temp[i] == roll();
				rRolls--;
			}
			else if (array[i] == 3) {
				temp[i] = 0;
			}
		}
		else {		
			if (compare(array[i]) == 0) {
				temp[i] = roll();
				rRolls--;
			}
			else if (compare(array[i]) == 1) {
				temp[i] = 0;
			}
		}
		if (temp[i] < array[i] && temp[i] > 0) {
			array[i] = temp[i];
		}
		if (temp[i] == 0) {
			rRolls++;
		}
	}
	int max;
	if (rRolls > 0) {
		for (int i = 0; i < size; i++) {
			if (i == 0) {
				max = array[i];
			}
			if (array[i] > max) {
				max = i;
			}
		}
		for (int i = 0; i < rRolls; i++) {
			if (compare(array[max]) == 0) {
				array[max] = roll();
				rRolls--;
			}
		}
	}
	replace(array, size);
	//printf("\n(%d) - Rolls\n", rRolls);
	
}
void printDie(int array[], int size) {
	for (int i = 0; i < size; i++) {
		printf("%d ", array[i]);
	}
}
int addDie(int array[], int size, int player) {
	int sum;
	for (int i = 0; i < size; i++) {
		sum += array[i];
	}
	return sum;
}
void main() {
	srand(time(NULL));
	int dieCount, playerCount, min, total, winner;
	printf("Enter number of players (whole number): ");
	scanf("%d", &playerCount);
	printf("\n");
	printf("Enter number of dice to play with (whole number): ");
	scanf("%d", &dieCount);
	printf("\n");
	int dice[dieCount];
	for (int i = 0; i < playerCount; i++) {
		fill(dice, dieCount);
		printf("\n");
		printf("First role: \n");
		printDie(dice, dieCount);
		//replace(dice, dieCount);
		//printf("\n");
		//printDie(dice, dieCount);
		printf("\n");
		reroll(dice, dieCount);
		printf("\nRe-rolled: \n");
		printDie(dice, dieCount);
		printf("\n\n");
		total = addDie(dice, dieCount, i + 1);
		if (i == 0) {
			min = total;
		}
		if (total < min) {
			min = total;
			winner = i + 1;
		}
		printf("Player %d total: %d\n", i + 1, total);
		printf("\n=======================\n");
	}
	printf("\nWINNER: Player %d\n", winner);
}
