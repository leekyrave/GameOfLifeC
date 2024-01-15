typedef struct map_stats {
	int generations;
	int FIt;
	int Deathes;
	int NLifes;
} map_stats;

typedef struct {
	int width, height;
	int** map;
	void (*showMap)(const struct MapData*);
	void (*setCellAlive)(struct MapData*, int x, int y);
	void (*setCellDied)(struct MapData*, int x, int y);
	int (*nextGeneration)(struct MapData*);
	map_stats stats;
} MapData;

MapData newMap(int cols, int rows);
void showMap(const MapData* mapData);
void setCellAlive(MapData* mapData, int x, int y);
void setCellDied(MapData* mapData, int x, int y);
int nextGeneration(MapData*);