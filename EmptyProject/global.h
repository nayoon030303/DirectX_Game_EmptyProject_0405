#include "DXUT.h"
#include "PageManager.h"

/*size && pos*/
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define WIDTH 1024
#define HEIGHT 720
#define START_X WINDOW_WIDTH/2 - WIDTH/2
#define START_Y 200


/*MAP_PROPERTY*/
#define MAP_PROPERTY_EDGE 100
#define MAP_PROPERTY_VISIT 200
#define MAP_PROPERTY_VISITING 300
#define MAP_PROPERTY_TEMP 400
#define MAP_PROPERTY_EMPTY 500

/*Map*/
extern int map[WIDTH * HEIGHT];
extern int binaryMap[WIDTH * HEIGHT];
extern int mapData[WIDTH * HEIGHT];


/*Manager*/
extern PageManager pageManager;