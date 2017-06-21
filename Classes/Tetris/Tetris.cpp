#include "Tetris.h"

unsigned char Tetris::m_ucBrickMode[7] = { 0x66, 0xe4, 0xe2, 0xe8, 0x6c, 0xc6, 0xf0 };

Tetris::Tetris(int row, int column):m_iRow(row),m_iColumn(column)
{
	int size = m_iColumn*m_iRow;
	m_brickMatrix = new BrickCellValue[size];
	for (int i = 0; i < size; ++i) {
		m_brickMatrix[i] = BrickCellValue_NULL;
	}
}

Tetris::~Tetris()
{
	delete[] m_brickMatrix;
}

//获得所需位置的方块值
BrickCellValue Tetris::getBrickValue(int r, int c)
{
	if ((r >= 0 && r < m_iRow) && (c >= 0 && c < m_iColumn)) {
		// 方块矩阵的该位置有方块则返回该值
		if (BrickCellValue_NULL != m_brickMatrix[r*m_iColumn + c]) {
			return m_brickMatrix[r*m_iColumn + c];
		}
		// 否则，如果(r,c)为当前方块上的值，则返回当前方块相应位置的值
		else if ((r >= m_iPosRow && r < m_iPosRow + 4) && (c >= m_iPosCol && c< m_iPosCol + 4)) {
			return m_currentBrick[r - m_iPosRow][c - m_iPosCol];
		}
	}
	return BrickCellValue_NULL;
}

BrickCellValue Tetris::getCurrentBrickValue(int r, int c)
{
		return m_currentBrick[r][c];
}

bool Tetris::getNextValue(int r, int c)
{
	if (m_nextBrick[r][c] != BrickCellValue_NULL)
		return true;
	else
		return false;
}

//矩阵设为空
void Tetris::clearBrickMatrix()
{
	for (int i = 0; i < m_iColumn*m_iRow; ++i) {
		m_brickMatrix[i] = BrickCellValue_NULL;
	}
}

void Tetris::clearNextBrick()
{
	for (int r = 0; r < 4; ++r) {
		for (int c = 0; c< 4; ++c) {
			m_nextBrick[r][c] = BrickCellValue_NULL;
		}
	}
}

bool Tetris::setNewBrick(BrickType brickType, BrickCellValue brickCellValue, BrickCellValue * brickMatrix , 
	int row, int column, BrickCellValue currentBrick[4][4], int & posRow, int & posCol)
{
	if (brickType <= BrickType_NULL || brickType >= BrickType_Count) {
		return false;
	}
	// 当前方块位置重置
	posRow = 0;
	posCol = (column - 4) / 2;
	// 清空原有方块
	for (int r = 0; r < 4; ++r) {
		for (int c = 0; c< 4; ++c) {
			currentBrick[r][c] = BrickCellValue_NULL;
		}
	}
	// 根据模板填充方块
	for (int r = 0; r < 2; ++r) {
		for (int c = 0; c< 4; ++c) {
			if (((Tetris::m_ucBrickMode[brickType] << (r * 4 + c)) & 0x80) > 0) {
				currentBrick[r][c] = brickCellValue;
				// 方块矩阵的这个位置有效，且方块矩阵的这个位置也有值，则游戏结束
				int offset = (posRow + (1 + r))*column + (posCol + c);
				if (posRow + (1 + r) >= 0 && brickMatrix[offset] != BrickCellValue_NULL) {
					return false;
				}
			}
		}
	}
	return true;
}

bool Tetris::getNextBrick(BrickType brickType, BrickCellValue brickCellValue,  BrickCellValue nextBrick[4][4])
{
	if(brickType <= BrickType_NULL || brickType >= BrickType_Count) {
		return false;
	}
	// 清空原有方块
	for (int r = 0; r < 4; ++r) {
		for (int c = 0; c< 4; ++c) {
			nextBrick[r][c] = BrickCellValue_NULL;
		}
	}
	// 根据模板填充方块
	for (int r = 0; r < 2; ++r) {
		for (int c = 0; c< 4; ++c) {
			if (((Tetris::m_ucBrickMode[brickType] << (r * 4 + c)) & 0x80) > 0) {
				nextBrick[r][c] = brickCellValue;
			}
		}	
	}
	return true;
}

bool Tetris::setNextBrick(BrickCellValue * brickMatrix, int row, int column, BrickCellValue currentBrick[4][4], BrickCellValue nextBrick[4][4], int & posRow, int & posCol)
{
	// 当前方块位置重置
	posRow = 0;
	posCol = (column - 4) / 2;
	// 清空原有方块
	for (int r = 0; r < 4; ++r) {
		for (int c = 0; c< 4; ++c) {
			currentBrick[r][c] = BrickCellValue_NULL;
		}
	}
	// 填充原有方块
	for (int r = 0; r < 2; ++r) {
		for (int c = 0; c< 4; ++c) {
			currentBrick[r][c] = nextBrick[r][c];
			int offset = (posRow + (1 + r))*column + (posCol + c);
			if (posRow + (1 + r) >= 0 && brickMatrix[offset] != BrickCellValue_NULL) {
				return false;
			}
		}
	}
	return true;
}

bool Tetris::rotateBrick(BrickCellValue *brickMatrix, int row, int column,
	BrickCellValue currentBrick[4][4], BrickType currentBrickType, int posRow, int posCol)
{
	// 正方形旋转
	if (BrickType_o == currentBrickType) {
		return true;
		}
	// 用临时方块试着旋转一下
	BrickCellValue tempBrick[4][4];
	for (int r = 0; r < 4; ++r) {
		for (int c = 0; c < 4; ++c) {
			tempBrick[r][c] = BrickCellValue_NULL;
		}
	}
	
	// 条形方块旋转
	if (BrickType_1 == currentBrickType) {
		// 竖形
		if (currentBrick[0][1] == BrickCellValue_NULL) {
			for (int i = 0; i < 4; ++i) {
				tempBrick[0][i] = currentBrick[i][2];
			}
		}
		// 横形
		else {
			for (int i = 0; i < 4; ++i) {
				tempBrick[i][2] = currentBrick[0][i];
			}
		}
	}
	// s形方块旋转
	else if (BrickType_s == currentBrickType) {
		// 竖形
		if (BrickCellValue_NULL == currentBrick[0][0]) {
			tempBrick[0][0] = currentBrick[0][1];
			tempBrick[1][0] = currentBrick[0][1];
			tempBrick[1][1] = currentBrick[0][1];
			tempBrick[2][1] = currentBrick[0][1];
		}
		// 横形
		else {
			tempBrick[1][0] = currentBrick[1][0];
			tempBrick[1][1] = currentBrick[1][0];
			tempBrick[0][1] = currentBrick[1][0];
			tempBrick[0][2] = currentBrick[1][0];
		}
	}
	// z形方块旋转
	else if (BrickType_z == currentBrickType) {
		// 竖形
		if (BrickCellValue_NULL == currentBrick[0][0]) {
			tempBrick[0][0] = currentBrick[0][1];
			tempBrick[0][1] = currentBrick[0][1];
			tempBrick[1][1] = currentBrick[0][1];
			tempBrick[1][2] = currentBrick[0][1];
		}
		// 横形
		else {
			tempBrick[0][1] = currentBrick[0][0];
			tempBrick[1][0] = currentBrick[0][0];
			tempBrick[1][1] = currentBrick[0][0];
			tempBrick[2][0] = currentBrick[0][0];
		}
	}
	//7型
	else if (BrickType_7 == currentBrickType) {
		if (BrickCellValue_NULL == currentBrick[1][0] && BrickCellValue_NULL == currentBrick[2][2]) {
			tempBrick[0][2] = currentBrick[0][0];
			tempBrick[1][2] = currentBrick[0][0];
			tempBrick[2][2] = currentBrick[0][0];
			tempBrick[2][1] = currentBrick[0][0];
		}
		else if (BrickCellValue_NULL == currentBrick[0][1] && BrickCellValue_NULL == currentBrick[2][0] && BrickCellValue_NULL == currentBrick[1][0]) {
			tempBrick[0][0] = currentBrick[0][2];
			tempBrick[1][0] = currentBrick[0][2];
			tempBrick[1][1] = currentBrick[0][2];
			tempBrick[1][2] = currentBrick[0][2];
		}
		else if (BrickCellValue_NULL == currentBrick[0][2] && BrickCellValue_NULL == currentBrick[2][0]) {
			tempBrick[1][0] = currentBrick[1][0];
			tempBrick[2][0] = currentBrick[1][0];
			tempBrick[0][0] = currentBrick[1][0];
			tempBrick[0][1] = currentBrick[1][0];
		}
		else if (BrickCellValue_NULL == currentBrick[0][2] && BrickCellValue_NULL == currentBrick[2][1] && BrickCellValue_NULL == currentBrick[1][2]) {
			tempBrick[0][2] = currentBrick[0][0];
			tempBrick[1][2] = currentBrick[0][0];
			tempBrick[0][0] = currentBrick[0][0];
			tempBrick[0][1] = currentBrick[0][0];
		}
	}
	//反7
	else if (BrickType_r7 == currentBrickType) {
		if (BrickCellValue_NULL == currentBrick[2][0] && BrickCellValue_NULL == currentBrick[1][2]) {
			tempBrick[0][1] = currentBrick[0][0];
			tempBrick[0][2] = currentBrick[0][0];
			tempBrick[2][2] = currentBrick[0][0];
			tempBrick[1][2] = currentBrick[0][0];
		}
		else if (BrickCellValue_NULL == currentBrick[0][0] && BrickCellValue_NULL == currentBrick[2][1] && BrickCellValue_NULL == currentBrick[1][1]) {
			tempBrick[0][2] = currentBrick[0][2];
			tempBrick[1][0] = currentBrick[0][2];
			tempBrick[1][1] = currentBrick[0][2];
			tempBrick[1][2] = currentBrick[0][2];
		}
		else if (BrickCellValue_NULL == currentBrick[0][0] && BrickCellValue_NULL == currentBrick[2][2]) {
			tempBrick[1][0] = currentBrick[1][0];
			tempBrick[2][0] = currentBrick[1][0];
			tempBrick[0][0] = currentBrick[1][0];
			tempBrick[2][1] = currentBrick[1][0];
		}
		else if (BrickCellValue_NULL == currentBrick[0][2] && BrickCellValue_NULL == currentBrick[2][2] && BrickCellValue_NULL == currentBrick[0][1]) {
			tempBrick[0][2] = currentBrick[0][0];
			tempBrick[1][0] = currentBrick[0][0];
			tempBrick[0][0] = currentBrick[0][0];
			tempBrick[0][1] = currentBrick[0][0];
		}
	}
	//T
	else if (BrickType_T == currentBrickType) {
		if (BrickCellValue_NULL == currentBrick[1][0] && BrickCellValue_NULL == currentBrick[1][2]) {
			tempBrick[0][2] = currentBrick[1][1];
			tempBrick[1][2] = currentBrick[1][1];
			tempBrick[2][2] = currentBrick[1][1];
			tempBrick[1][1] = currentBrick[1][1];
		}
		else if (BrickCellValue_NULL == currentBrick[1][0] && BrickCellValue_NULL == currentBrick[0][0]) {
			tempBrick[1][0] = currentBrick[1][1];
			tempBrick[1][2] = currentBrick[1][1];
			tempBrick[1][1] = currentBrick[1][1];
			tempBrick[0][1] = currentBrick[1][1];
		}
		else if (BrickCellValue_NULL == currentBrick[0][2] && BrickCellValue_NULL == currentBrick[0][0]) {
			tempBrick[0][0] = currentBrick[1][1];
			tempBrick[1][0] = currentBrick[1][1];
			tempBrick[2][0] = currentBrick[1][1];
			tempBrick[1][1] = currentBrick[1][1];
		}
		else if (BrickCellValue_NULL == currentBrick[1][2] && BrickCellValue_NULL == currentBrick[0][2]) {
			tempBrick[0][0] = currentBrick[1][1];
			tempBrick[0][1] = currentBrick[1][1];
			tempBrick[0][2] = currentBrick[1][1];
			tempBrick[1][1] = currentBrick[1][1];
		}
	}
	else {
		for (int r = 0; r < 3; r++) {
			for (int c = 0; c < 3; c++) {
				tempBrick[r][c] = currentBrick[2 - c][r];
			}
		}
	}
	// 查看旋转后与方块矩阵是否冲突
	for (int r = 0; r < 4; ++r) {
		for (int c = 0; c < 4; ++c) {
			// 当前方块的这个位置有值
			if (tempBrick[r][c] != BrickCellValue_NULL) {
				// 左边，或者右边，或者下边超出边界，旋转失败
				if (posCol + c < 0 || posCol + c >= column || posRow + r >= row) {
					return false;
				}
				// 方块矩阵的这个位置有效，且方块矩阵的这个位置也有值，则旋转失败
				int offset = (posRow + r)*column + (posCol + c);
				if (offset >= 0 && offset < row*column &&
					brickMatrix[offset] != BrickCellValue_NULL) {
					return false;
				}
			}
		}
	}
	// 不冲突则旋转
	for (int r = 0; r < 4; ++r) {
		for (int c = 0; c < 4; ++c) {
			currentBrick[r][c] = tempBrick[r][c];
		}
	}
	return true;
}
bool Tetris::moveLeftBrick(BrickCellValue *brickMatrix, int row, int column,
	BrickCellValue currentBrick[4][4], int posRow, int &posCol)
{
	// 试着左移一下
	int tempPosCol = posCol - 1;
	for (int r = 0; r < 4; ++r) {
		for (int c = 0; c < 4; ++c) {
			// 当前方块的这个位置有值
			if (currentBrick[r][c] != BrickCellValue_NULL) {
				// 超出左边界，左移失败
				if (tempPosCol + c < 0) {
					return false;
				}
				// 方块矩阵的这个位置有效，且方块矩阵的这个位置也有值，则左移失败
				int offset = (posRow + r)*column + (tempPosCol + c);
				if (posRow + r >= 0 && posRow + r < row &&
					brickMatrix[offset] != BrickCellValue_NULL) {
					return false;
				}
			}
		}
	}
	// 可以左移
	posCol -= 1;
	return true;
}
bool Tetris::moveRightBrick(BrickCellValue *brickMatrix, int row, int column,
	BrickCellValue currentBrick[4][4], int posRow, int &posCol)
{
	// 试着右移一下
	int tempPosCol = posCol + 1;
	for (int r = 0; r < 4; ++r) {
		for (int c = 3; c >= 0; --c) { // 从右往左判断可能会快些
									   // 当前方块的这个位置有值
			if (currentBrick[r][c] != BrickCellValue_NULL) {
				// 超出右边界，右移失败
				if (tempPosCol + c >= column) {
					return false;
				}
				// 方块矩阵的这个位置有效，且方块矩阵的这个位置也有值，则右移失败
				int offset = (posRow + r)*column + (tempPosCol + c);
				if (posRow + r >= 0 && posRow + r < row &&
					brickMatrix[offset] != BrickCellValue_NULL) {
					return false;
				}
			}
		}
	}
	// 可以右移
	posCol += 1;
	return true;
}
bool Tetris::fallBrick(BrickCellValue *brickMatrix, int row, int column,
	BrickCellValue currentBrick[4][4], int &posRow, int posCol)
{
	// 试着下移一下
	int tempPosRow = posRow + 1;
	for (int r = 3; r >= 0; --r) {
		for (int c = 0; c < 4; ++c) {
			// 当前方块的这个位置有值
			if (currentBrick[r][c] != BrickCellValue_NULL) {
				// 超出下边界，下落失败
				if (tempPosRow + r >= row) {
					// 将当前方块固定到方块矩阵中
					Tetris::fixBrick(brickMatrix, row, column, currentBrick, posRow, posCol);
					return false;
				}
				// 未超出下边界，且这个位置在方块矩阵内，且方块矩阵的这个位置也有值，则下落失败
				else if (tempPosRow + r >= 0 && brickMatrix[(tempPosRow + r)*column + (posCol + c)] != BrickCellValue_NULL) {
					// 将当前方块固定到方块矩阵中
					Tetris::fixBrick(brickMatrix, row, column, currentBrick, posRow, posCol);
					return false;
				}
			}
		}
	}
	// 可以下移
	posRow += 1;
	return true;
}
void Tetris::throwDownBrick(BrickCellValue *brickMatrix, int row, int column,
	BrickCellValue currentBrick[4][4], int &posRow, int posCol)
{
	while (Tetris::fallBrick(brickMatrix, row, column, currentBrick, posRow, posCol));
}
void Tetris::fixBrick(BrickCellValue *brickMatrix, int row, int column,
	BrickCellValue currentBrick[4][4], int posRow, int posCol)
{
	for (int r = 0; r < 4; ++r) {
		for (int c = 0; c < 4; ++c) {
			if (currentBrick[r][c] != BrickCellValue_NULL) {
				brickMatrix[(posRow + r)*column + (posCol + c)] = currentBrick[r][c];
			}
		}
	}
}
bool Tetris::clearOneLine(BrickCellValue *brickMatrix, int row, int column,
	int posRowCurrentBrick, int &lineIndex)
{
	int rStart = (row - 1< posRowCurrentBrick + 4) ? (row - 1) : (posRowCurrentBrick + 4);
	int rEnd = (0> posRowCurrentBrick) ? 0 : posRowCurrentBrick;
	for (int r = rStart; r >= rEnd;--r) {
		// 先查看该行是否可以消行
		bool canClearLine = true;
		for (int c = 0; c < column; ++c) {
			if (brickMatrix[r*column + c] == BrickCellValue_NULL) {
				canClearLine = false;
				break;
			}
		}
		// 如果能消行，则继续看上一行
		if (canClearLine) {
			lineIndex = r;
			// 从上往下赋值，内存移位处理
			memmove(brickMatrix + column, brickMatrix, r*column * sizeof(BrickCellValue));
			// 第0行清空
			for (int c = 0; c < column; c++) {
				brickMatrix[c] = BrickCellValue_NULL;
			}
			return true;
		}
	}
	return false;
}

bool Tetris::setNewBrick(BrickType brickType, BrickCellValue brickCellValue)
{
	m_currentBrickType = brickType;

	return Tetris::setNewBrick(brickType, brickCellValue,m_brickMatrix,m_iRow,m_iColumn,m_currentBrick,m_iPosRow,m_iPosCol);
}
bool Tetris::getNextBrick(BrickType brickType, BrickCellValue brickCellValue)
{
	m_nextBrickType = brickType;

	return Tetris::getNextBrick( brickType,  brickCellValue, m_nextBrick);
}
bool Tetris::setNextBrick(BrickType nextBrickType)
{
	m_currentBrickType = nextBrickType;
	return Tetris::setNextBrick( m_brickMatrix, m_iRow, m_iColumn, m_currentBrick,m_nextBrick, m_iPosRow, m_iPosCol);;
}
bool Tetris::moveLeftBrick()
{
	return Tetris::moveLeftBrick(m_brickMatrix,m_iRow,m_iColumn,m_currentBrick,m_iPosRow,m_iPosCol);
}
bool Tetris::moveRightBrick()
{
	return Tetris::moveRightBrick(m_brickMatrix, m_iRow, m_iColumn, m_currentBrick, m_iPosRow, m_iPosCol);;
}
bool Tetris::rotateBrick()
{
	return Tetris::rotateBrick(m_brickMatrix, m_iRow, m_iColumn,m_currentBrick, m_currentBrickType, m_iPosRow, m_iPosCol);
}
bool Tetris::fallBrick()
{
	return Tetris::fallBrick(m_brickMatrix, m_iRow, m_iColumn, m_currentBrick, m_iPosRow, m_iPosCol);
}
void Tetris::throwDownBrick()
{
	Tetris::throwDownBrick(m_brickMatrix, m_iRow, m_iColumn, m_currentBrick, m_iPosRow, m_iPosCol);
}
bool Tetris::clearOneLine(int & lineIndex)
{
	return Tetris::clearOneLine(m_brickMatrix,m_iRow,m_iColumn,m_iPosRow, lineIndex);
}