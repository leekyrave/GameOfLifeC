#include "GameOfLife.h"

void CheckInput(int* value, int TopLimit, int BottomLimit) {
	while (1) {
		scanf("%d", value);
		if (*value < BottomLimit || *value > TopLimit) {
			printf("Liczba musi byc w interwale [%d - %d]\n", BottomLimit, TopLimit);
			continue;
		}

		break;
	}

}