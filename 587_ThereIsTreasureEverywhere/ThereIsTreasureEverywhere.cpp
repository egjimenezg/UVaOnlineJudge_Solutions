#include <stdio.h>
#include <string.h>
#include <cmath>

using namespace std;

struct point {
  double x, y;
  point() { x = y = 0; }
  point(double _x, double _y) : x(_x), y(_y) { }
};

double distance(const point &p1, const point &p2) {
  return hypot(p1.x - p2.x, p1.y - p2.y);
}

double degreesToRadians(double degress) {
  return degress * M_PI / 180.0;
}

point moveToNewPoint(point &p, int length, char* direction) {
  double radians = degreesToRadians(45);

  if (strcmp(direction, "N") == 0) {
    p.y += length;
  } else if (strcmp(direction, "S") == 0) {
    p.y -= length;
  } else if (strcmp(direction, "E") == 0) {
    p.x += length;
  } else if (strcmp(direction, "W") == 0) {
    p.x -= length;
  } else if (strcmp(direction, "NW") == 0) {
    p.x -= (cos(radians) * length);
    p.y += (sin(radians) * length);
  } else if (strcmp(direction, "NE") == 0) {
    p.x += (cos(radians) * length);
    p.y += (sin(radians) * length);
  } else if (strcmp(direction, "SW") == 0) {
    p.x -= (cos(radians) * length);
    p.y -= (sin(radians) * length);
  } else if (strcmp(direction, "SE") == 0) {
    p.x += (cos(radians) * length);
    p.y -= (sin(radians) * length);
  }

  return p;
}

int isEndOfInput(char* line) {
  return strcmp(line, "END") == 0;
}

int main() {
  char mapDescription[200] = "";
  int numberOfMap = 0;

  while(scanf(" %[^\n]s", mapDescription), !isEndOfInput(mapDescription)) {
    numberOfMap++;
    char* lengthsAndDirections = strtok(mapDescription, ".");
    point origin(0, 0);
    point location(0,0);
    char* pair = strtok(lengthsAndDirections, ",");
    int length;
    char direction[3];

    while(pair != NULL) {
      sscanf(pair, "%d %s", &length, direction);
      location = moveToNewPoint(location, length, direction);
      pair = strtok(NULL, ",");
    }

    printf("Map #%d\n", numberOfMap);
    printf("The treasure is located at (%.3f,%.3f).\n", location.x, location.y);
    printf("The distance to the treasure is %.3f.\n\n", std::round(distance(origin, location) * 1000.0) / 1000.0);
  }

  return 0;
}
