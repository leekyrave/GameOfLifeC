#include "GameOfLife.h"

MapData newMap(int X, int Y) {
	MapData object;

	object.width = X;
	object.height = Y;
	object.showMap = &showMap;
	object.setCellAlive = &setCellAlive;
	object.setCellDied = &setCellDied;
	object.nextGeneration = &nextGeneration;
	object.map = (int**)calloc(Y, sizeof(int*));
	object.stats.Deathes = 0;
	object.stats.FIt = 0;
	object.stats.generations = 0;
	object.stats.NLifes = 0;
	
	for (int i = 0; i < Y; i++) {
		object.map[i] = (int*)calloc(X, sizeof(int));
	}
	
	return object;
}

void showMap(const MapData *mapData) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < mapData->height; i++) {
		for (int j = 0; j < mapData->width; j++) {
			if (mapData->map[i][j] == 1)
			#ifdef _WIN32
				SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			#else
				//
			#endif
			else {
				#ifdef _WIN32
					SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
				#else
					//
				#endif
			}
				

			printf("* ");

			#ifdef _WIN32
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			#else
			//
			#endif
		}

		printf("\n");
	}

	printf("\n\n");
}

void setCellAlive(MapData* mapData, int x, int y) {
	mapData->map[GetAbsoluteIndex(mapData->height, y)][GetAbsoluteIndex(mapData->width, x)] = 1;
	mapData->stats.NLifes++;
}

void setCellDied(MapData* mapData, int x, int y) {
	mapData->map[GetAbsoluteIndex(mapData->height, y)][GetAbsoluteIndex(mapData->width, x)] = 0;
	mapData->stats.Deathes++;
}

int nextGeneration(MapData* mapData) {

	int isSomeChanges = 0;
	for (int i = 0; i < mapData->height; i++) {
		for (int j = 0; j < mapData->width; j++) {
			mapData->stats.FIt++;
			if (SetLiveOrDie(mapData, j, i) == 1) {
				isSomeChanges = 1;
				showMap(mapData);
				#ifdef _WIN32
				Sleep(150);
				#else
				sleep(0.15);
				#endif
			}
		}
	}

	mapData->stats.generations++;
	return isSomeChanges;

}


int SetLiveOrDie(MapData* mapData, int x, int y) {
	int x_tmp = 0;
	int y_tmp = 0;
	int alive_points_near = 0;
	int isChanges = 0;

	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (i == 0 && j == 0) continue;
			x_tmp = GetAbsoluteIndex(mapData->width, x + j);
			y_tmp = GetAbsoluteIndex(mapData->height, y + i);

			alive_points_near = (mapData->map[y_tmp][x_tmp] == 1) ? ++alive_points_near : alive_points_near;
		}
	}

	if (mapData->map[y][x] == 0 && alive_points_near == 3) {
		mapData->setCellAlive(mapData, x, y);
		isChanges = 1;
	}

	if ((alive_points_near <= 1 || alive_points_near > 3) && mapData->map[y][x] == 1) {
		mapData->setCellDied(mapData, x, y);
		isChanges = 1;
	}

	return isChanges;
}