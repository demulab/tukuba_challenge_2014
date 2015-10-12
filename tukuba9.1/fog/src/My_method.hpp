#ifndef MY_METHOD
#define MY_METHOD

#include<iostream>
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include <time.h>
#include <sys/time.h>

#define	RAD2DEG 180.0/M_PI
#define	DEG2RAD M_PI/180.0

//! 挿入ソート
// 明解C言語によるアルゴリズムとデータ構造P167
void insertion(double a[], int n);

//0～π 
//-π ～π までの範囲に変換
double changeAngle(double source);

//数字を文字に変換
int ChangeFigure(int i, unsigned char *c);

//文字を数字に変換
int ChangeCharacter(int *i, unsigned char c);

//時間を計る
double getETime(void);
#endif
