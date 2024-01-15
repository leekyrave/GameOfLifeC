#include "GameOfLife.h"
volatile int stopFlag = 0;

int main()
{


	time_t start_time;
	time_t current_time;
	int X, Y;
	printf("Witamy w grze Game of Life\nProsze wpisac rozmiar mapy poziomowo:\n");

	CheckInput(&X, MAX_HORIZONTAL_SIZE, MIN_HORIZONTAL_SIZE);
	printf("Prosze wpisac rozmiar pionowo:\n");
	CheckInput(&Y, MAX_HORIZONTAL_SIZE, MIN_HORIZONTAL_SIZE);

	MapData map = newMap(X, Y);

	map.showMap(&map);

	printf("\nTeraz prosze wpisac zyjace komorki na mapie(w formacie X Y).\nZeby zaczjac gre - prosze wpisac -1 -1\n");
	int x_set, y_set;
	while (1) {
		scanf("%d %d", &x_set, &y_set);
		if (x_set == -1 && y_set == -1)
			break;
		map.setCellAlive(&map, x_set, y_set);

		map.showMap(&map);
	}
	printf("Nacisnij Enter zeby zaczac\n");
	int clearBuffer;
	while ((clearBuffer = getchar()) != '\n' && clearBuffer != EOF);
	getchar();
	start_time = time(NULL);
	while (1) {
		current_time = time(NULL);
		if (!map.nextGeneration(&map))
			break;

		if (current_time - start_time >= TIMER_GAME) {
			int gameContinue = -1;
			printf("Gramy dalej?\nJesli tak - wpisz 1\nNie - wpisz 0");
			scanf("%d", &gameContinue);
			if (gameContinue) {
				start_time = time(NULL);
				continue;
			}
			else
				break;
		}
	}

	printf("Koncowa mapa:\n");
	map.showMap(&map);

	printf("Game is end.\n\nStatystyka:\n\nGenerations: %d (Full Iterations: %d)\nNew lifes: %d\nDeathes: %d\n", map.stats.generations, map.stats.FIt, map.stats.NLifes, map.stats.Deathes);

	while ((clearBuffer = getchar()) != '\n' && clearBuffer != EOF);
	getchar();
	return 0;
}
