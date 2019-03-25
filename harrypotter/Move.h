//
// Created by stefan on 27/3/2017. 
//

#ifndef GHOST_MOVE_H_H
#define GHOST_MOVE_H_H

#define UP_ARRAY_OFFSET 0
#define DOWN_ARRAY_OFFSET 1
#define RIGHT_ARRAY_OFFSET 2
#define LEFT_ARRAY_OFFSET 3

#define UP 0
#define DOWN 1
#define RIGHT 2
#define LEFT 3

#define STAND 5
#define TELEPORT 6

#define CLEVERGHOST 7
#define DUMMYGHOST 8
#define WALL_CHAR  '@'
#define END_MAP_CHAR '*'
#define CUP_CHAR   'W'
#define NO_RESPONDED 9
#define TELEPORTS_MAX 2
#define EASY 9
#define MEDIUM 10
#define EXETASI_MODE 11
#define SMARTGHOST_CHAR '$'
#define DUMMYGHOST_CHAR '#'
#define MOVES_ITERATOR_LOW 1
#define MOVES_ITERATOR_HIGH 5
#define EATCH_MOVE int move=1;move<5;move++
#define EATCH_MAP_PLAY_TIMES 2
#define INF std::numeric_limits<int>::max()
#define DEVCPP_PATH "Map/"
#define CLION_PATH  "../Map/"
#endif //GHOST_MOVE_H_H
