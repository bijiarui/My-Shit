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
	//�������������
	int getRow() { return m_iRow; }
	int getColumn() { return m_iColumn; }
	//��÷�����Ϣ
	BrickCellValue *getBrickMatrix() { return m_brickMatrix; }
	BrickCellValue(*getCurrentBrick())[4]{ return m_currentBrick; }
	BrickType getCurrentBrickType() { return m_currentBrickType; }
	BrickType getNextBrickType() { return m_nextBrickType; }
	//���ָ��λ��ֵ
	BrickCellValue getBrickValue(int r, int c);
	//��õ�ǰ������Ϣ
	BrickCellValue getCurrentBrickValue(int r, int c);
	//��õ�ǰλ��
	int getPosRowOfCurrentBrick() { return m_iPosRow; }
	int getPosColOfCurrentBrick() { return m_iPosCol; }
	//���Ԥ��������Ϣ
	bool getNextValue(int r,int c);
	//��ʼ���������
	void clearBrickMatrix();
	void clearNextBrick();


	//�������
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
	//�̶��������
	static void fixBrick(BrickCellValue *brickMatrix, int row, int column,
							BrickCellValue currentBrick[4][4], int posRow, int posCol);
	//����������
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
	//��Ϸ����
	const int m_iRow;
	//��Ϸ����
	const int m_iColumn;
	//��Ϸ������
	BrickCellValue *m_brickMatrix;
	//��ǰ����λ��
	int m_iPosRow, m_iPosCol;
	//��ǰ��������
	BrickType m_currentBrickType;
	//��ǰ�Ĵ󷽿�
	BrickCellValue m_currentBrick[4][4];
	//Ԥ����������
	BrickType m_nextBrickType;
	//Ԥ���Ĵ󷽿�
	BrickCellValue m_nextBrick[4][4];
	//unsingned char����16������ģ��
	static unsigned char m_ucBrickMode[7];

};

#endif // !_TETRIS_H_