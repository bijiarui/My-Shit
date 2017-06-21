#pragma once
#ifndef _TETRIS_H_
#define _TETRIS_H_

#include <iostream>
#include "TetrisDefine.h"

class Tetris
{
public:
	Tetris(int row, int column);
	~Tetris();
	//获得行数和列数
	int getRow() { return m_iRow; }
	int getColumn() { return m_iColumn; }
	//获得方块信息
	BrickCellValue *getBrickMatrix() { return m_brickMatrix; }
	BrickCellValue(*getCurrentBrick())[4]{ return m_currentBrick; }
	BrickType getCurrentBrickType() { return m_currentBrickType; }
	BrickType getNextBrickType() { return m_nextBrickType; }
	//获得指定位置值
	BrickCellValue getBrickValue(int r, int c);
	//获得当前方块信息
	BrickCellValue getCurrentBrickValue(int r, int c);
	//获得当前位置
	int getPosRowOfCurrentBrick() { return m_iPosRow; }
	int getPosColOfCurrentBrick() { return m_iPosCol; }
	//获得预览方块信息
	bool getNextValue(int r,int c);
	//初始化方块矩阵
	void clearBrickMatrix();
	void clearNextBrick();


	//方块操作
	static bool setNewBrick(BrickType brickType, BrickCellValue brickCellValue, BrickCellValue *brickMatrix , int row , int column ,
							BrickCellValue currentBrick[4][4] , int &posRow , int &posCol );
	static bool getNextBrick(BrickType brickType, BrickCellValue brickCellValue,
		BrickCellValue nextBrick[4][4]);
	static bool setNextBrick( BrickCellValue *brickMatrix, int row, int column, BrickCellValue currentBrick[4][4], BrickCellValue nextBrick[4][4], int &posRow, int &posCol);
	
	static bool rotateBrick(BrickCellValue *brickMatrix, int row, int column,
							BrickCellValue currentBrick[4][4], BrickType currentBrickType, int posRow, int posCol);
	static bool moveLeftBrick(BrickCellValue *brickMatrix, int row, int column,
							BrickCellValue currentBrick[4][4], int posRow, int &posCol);
	static bool moveRightBrick(BrickCellValue *brickMatrix, int row, int column,
							BrickCellValue currentBrick[4][4], int posRow, int &posCol);
	static bool fallBrick(BrickCellValue *brickMatrix, int row, int column,
							BrickCellValue currentBrick[4][4], int &posRow, int posCol);
	static void throwDownBrick(BrickCellValue *brickMatrix, int row, int column,
							BrickCellValue currentBrick[4][4], int &posRow, int posCol);
	//固定方块矩阵
	static void fixBrick(BrickCellValue *brickMatrix, int row, int column,
							BrickCellValue currentBrick[4][4], int posRow, int posCol);
	//矩阵消除行
	static bool clearOneLine(BrickCellValue *brickMatrix, int row, int column,
							int posRowCurrentBrick, int &lineIndex);
    
	bool setNewBrick(BrickType brickType, BrickCellValue brickCellValue);
	bool getNextBrick(BrickType brickType, BrickCellValue brickCellValue);
	bool setNextBrick(BrickType nextBrickType);
	bool moveLeftBrick();
	bool moveRightBrick();
	bool rotateBrick();
	bool fallBrick();
	void throwDownBrick();
	bool clearOneLine(int &lineIndex);

private:
	//游戏区行
	const int m_iRow;
	//游戏区列
	const int m_iColumn;
	//游戏区矩阵
	BrickCellValue *m_brickMatrix;
	//当前方块位置
	int m_iPosRow, m_iPosCol;
	//当前方块类型
	BrickType m_currentBrickType;
	//当前的大方块
	BrickCellValue m_currentBrick[4][4];
	//预览方块类型
	BrickType m_nextBrickType;
	//预览的大方块
	BrickCellValue m_nextBrick[4][4];
	//unsingned char储存16进制做模板
	static unsigned char m_ucBrickMode[7];

};

#endif // !_TETRIS_H_