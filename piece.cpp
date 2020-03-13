#include "piece.h"
#include <allegro5/allegro_primitives.h>

piece::piece(int xpos, int ypos) {
	x = 0; 
	y = 0; 
	spin = 1;
	landed = false;
}
void piece::move() {
	y+= 3;
}
int piece::turn(char dir) {
	return 0;
}
bool piece::isLanded() {
	return landed;
}
void piece::draw(int map[10][16]) {

}
int piece::getY() {
	return y;
}
int piece::getX() {
	return x;
}
//paints block's final position
//to the actual map before it's destroyed
void piece::land(int map[10][16]) {

}
//moves the piece based on keyboard input
void piece::MoveSideways(char dir, int grid[10][16]) {

}
bool piece::checkCollision(int grid[10][16]) {
	return 0;
}
