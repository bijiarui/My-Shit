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

//�������λ�õķ���ֵ
BrickCellValue Tetris::getBrickValue(int r, int c)
{
	if ((r >= 0 && r < m_iRow) && (c >= 0 && c < m_iColumn)) {
		// �������ĸ�λ���з����򷵻ظ�ֵ
		if (BrickCellValue_NULL != m_brickMatrix[r*m_iColumn + c]) {
			return m_brickMatrix[r*m_iColumn + c];
		}
		// �������(r,c)Ϊ��ǰ�����ϵ�ֵ���򷵻ص�ǰ������Ӧλ�õ�ֵ
		else if ((r >= m_iPosRow && r < m_iPosRow + 4) && (c >= m_iPosCol && c< m_iPosCol + 4)) {
			return m_currentBrick[r - m_iPosRow][c - m_iPosCol];
		}
	}
	return BrickCellValue_NULL;
}

bool Tetris::getNextValue(int r, int c)
{
	if (m_nextBrick[r][c] != BrickCellValue_NULL)
		return true;
	else
		return false;
}

//������Ϊ��
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
	// ��ǰ����λ������
	posRow = 0;
	posCol = (column - 4) / 2;
	// ���ԭ�з���
	for (int r = 0; r < 4; ++r) {
		for (int c = 0; c< 4; ++c) {
			currentBrick[r][c] = BrickCellValue_NULL;
		}
	}
	// ����ģ����䷽��
	for (int r = 0; r < 2; ++r) {
		for (int c = 0; c< 4; ++c) {
			if (((Tetris::m_ucBrickMode[brickType] << (r * 4 + c)) & 0x80) > 0) {
				currentBrick[r][c] = brickCellValue;
				// �����������λ����Ч���ҷ����������λ��Ҳ��ֵ������Ϸ����
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
	// ���ԭ�з���
	for (int r = 0; r < 4; ++r) {
		for (int c = 0; c< 4; ++c) {
			nextBrick[r][c] = BrickCellValue_NULL;
		}
	}
	// ����ģ����䷽��
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
	// ��ǰ����λ������
	posRow = 0;
	posCol = (column - 4) / 2;
	// ���ԭ�з���
	for (int r = 0; r < 4; ++r) {
		for (int c = 0; c< 4; ++c) {
			currentBrick[r][c] = BrickCellValue_NULL;
		}
	}
	// ���ԭ�з���
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
	// ��������ת
	if (BrickType_o == currentBrickType) {
		return true;
		}
	// ����ʱ����������תһ��
	BrickCellValue tempBrick[4][4];
	for (int r = 0; r < 4; ++r) {
		for (int c = 0; c < 4; ++c) {
			tempBrick[r][c] = BrickCellValue_NULL;
		}
	}
	
	// ���η�����ת
	if (BrickType_1 == currentBrickType) {
		// ����
		if (currentBrick[0][1] == BrickCellValue_NULL) {
			for (int i = 0; i < 4; ++i) {
				tempBrick[0][i] = currentBrick[i][2];
			}
		}
		// ����
		else {
			for (int i = 0; i < 4; ++i) {
				tempBrick[i][2] = currentBrick[0][i];
			}
		}
	}
	// s�η�����ת
	else if (BrickType_s == currentBrickType) {
		// ����
		if (BrickCellValue_NULL == currentBrick[0][0]) {
			tempBrick[0][0] = currentBrick[0][1];
			tempBrick[1][0] = currentBrick[0][1];
			tempBrick[1][1] = currentBrick[0][1];
			tempBrick[2][1] = currentBrick[0][1];
		}
		// ����
		else {
			tempBrick[1][0] = currentBrick[1][0];
			tempBrick[1][1] = currentBrick[1][0];
			tempBrick[0][1] = currentBrick[1][0];
			tempBrick[0][2] = currentBrick[1][0];
		}
	}
	// z�η�����ת
	else if (BrickType_z == currentBrickType) {
		// ����
		if (BrickCellValue_NULL == currentBrick[0][0]) {
			tempBrick[0][0] = currentBrick[0][1];
			tempBrick[0][1] = currentBrick[0][1];
			tempBrick[1][1] = currentBrick[0][1];
			tempBrick[1][2] = currentBrick[0][1];
		}
		// ����
		else {
			tempBrick[0][1] = currentBrick[0][0];
			tempBrick[1][0] = currentBrick[0][0];
			tempBrick[1][1] = currentBrick[0][0];
			tempBrick[2][0] = currentBrick[0][0];
		}
	}
	//7��
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
	//��7
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
	// �鿴��ת���뷽������Ƿ��ͻ
	for (int r = 0; r < 4; ++r) {
		for (int c = 0; c < 4; ++c) {
			// ��ǰ��������λ����ֵ
			if (tempBrick[r][c] != BrickCellValue_NULL) {
				// ��ߣ������ұߣ������±߳����߽磬��תʧ��
				if (posCol + c < 0 || posCol + c >= column || posRow + r >= row) {
					return false;
				}
				// �����������λ����Ч���ҷ����������λ��Ҳ��ֵ������תʧ��
				int offset = (posRow + r)*column + (posCol + c);
				if (offset >= 0 && offset < row*column &&
					brickMatrix[offset] != BrickCellValue_NULL) {
					return false;
				}
			}
		}
	}
	// ����ͻ����ת
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
	// ��������һ��
	int tempPosCol = posCol - 1;
	for (int r = 0; r < 4; ++r) {
		for (int c = 0; c < 4; ++c) {
			// ��ǰ��������λ����ֵ
			if (currentBrick[r][c] != BrickCellValue_NULL) {
				// ������߽磬����ʧ��
				if (tempPosCol + c < 0) {
					return false;
				}
				// �����������λ����Ч���ҷ����������λ��Ҳ��ֵ��������ʧ��
				int offset = (posRow + r)*column + (tempPosCol + c);
				if (posRow + r >= 0 && posRow + r < row &&
					brickMatrix[offset] != BrickCellValue_NULL) {
					return false;
				}
			}
		}
	}
	// ��������
	posCol -= 1;
	return true;
}
bool Tetris::moveRightBrick(BrickCellValue *brickMatrix, int row, int column,
	BrickCellValue currentBrick[4][4], int posRow, int &posCol)
{
	// ��������һ��
	int tempPosCol = posCol + 1;
	for (int r = 0; r < 4; ++r) {
		for (int c = 3; c >= 0; --c) { // ���������жϿ��ܻ��Щ
									   // ��ǰ��������λ����ֵ
			if (currentBrick[r][c] != BrickCellValue_NULL) {
				// �����ұ߽磬����ʧ��
				if (tempPosCol + c >= column) {
					return false;
				}
				// �����������λ����Ч���ҷ����������λ��Ҳ��ֵ��������ʧ��
				int offset = (posRow + r)*column + (tempPosCol + c);
				if (posRow + r >= 0 && posRow + r < row &&
					brickMatrix[offset] != BrickCellValue_NULL) {
					return false;
				}
			}
		}
	}
	// ��������
	posCol += 1;
	return true;
}
bool Tetris::fallBrick(BrickCellValue *brickMatrix, int row, int column,
	BrickCellValue currentBrick[4][4], int &posRow, int posCol)
{
	// ��������һ��
	int tempPosRow = posRow + 1;
	for (int r = 3; r >= 0; --r) {
		for (int c = 0; c < 4; ++c) {
			// ��ǰ��������λ����ֵ
			if (currentBrick[r][c] != BrickCellValue_NULL) {
				// �����±߽磬����ʧ��
				if (tempPosRow + r >= row) {
					// ����ǰ����̶������������
					Tetris::fixBrick(brickMatrix, row, column, currentBrick, posRow, posCol);
					return false;
				}
				// δ�����±߽磬�����λ���ڷ�������ڣ��ҷ����������λ��Ҳ��ֵ��������ʧ��
				else if (tempPosRow + r >= 0 && brickMatrix[(tempPosRow + r)*column + (posCol + c)] != BrickCellValue_NULL) {
					// ����ǰ����̶������������
					Tetris::fixBrick(brickMatrix, row, column, currentBrick, posRow, posCol);
					return false;
				}
			}
		}
	}
	// ��������
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
		// �Ȳ鿴�����Ƿ��������
		bool canClearLine = true;
		for (int c = 0; c < column; ++c) {
			if (brickMatrix[r*column + c] == BrickCellValue_NULL) {
				canClearLine = false;
				break;
			}
		}
		// ��������У����������һ��
		if (canClearLine) {
			lineIndex = r;
			// �������¸�ֵ���ڴ���λ������
			memmove(brickMatrix + column, brickMatrix, r*column * sizeof(BrickCellValue));
			// ��0�����
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