//
//  graphlib.h
//  CS 31 Spring Proj 3
//
//  Created by Calvin on 4/25/13.
//  Copyright (c) 2013 Calvin Liu. All rights reserved.
//

// Graphics library interface

#ifndef GRAPHLIB_INCLUDED
#define GRAPHLIB_INCLUDED

const int NROWS = 20;
const int NCOLS = 30;

void clearGrid();
void setChar(int r, int c, char ch);
char getChar(int r, int c);
void draw();

#endif // GRAPHLIB_INCLUDED