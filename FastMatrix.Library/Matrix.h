class FastMatrix {

private:

	float* _matrix;
	int _rowCount;
	int _columnCount;

	void MultiplyThenSubtractUpdate(FastMatrix& matrix1, FastMatrix& matrix2, FastMatrix& matrix3);
	void ScalarMultiplyThenSubtractUpdate(float scalar, FastMatrix& matrix);

	static int ConsequtiveSum(int min, int max)
	{
		int sum = 0;

		for (int i = min; i <= max; i++)
		{
			sum += i;
		}

		return sum;
	}

public:
	FastMatrix(const FastMatrix& fastMatrix)
	{
		int arrayLength = fastMatrix._rowCount * fastMatrix._columnCount;

		this->_matrix = new float[arrayLength]();

		for (int index = 0; index < arrayLength; index++)
		{
			this->_matrix[index] = fastMatrix._matrix[index];
		}

		this->_rowCount = fastMatrix._rowCount;
		this->_columnCount = fastMatrix._columnCount;
	}

	FastMatrix(int rowCount, int columnCount)
	{
		this->_rowCount = rowCount;
		this->_columnCount = columnCount;

		this->_matrix = new float[rowCount * columnCount];
	}

	~FastMatrix()
	{
		if (this->_matrix != 0x00)
		{
			delete this->_matrix;
		}
	}

	int GetRowCount()
	{
		return this->_rowCount;
	}

	int GetColumnCount()
	{
		return this->_columnCount;
	}

	float Get(int rowIndex, int columnIndex);

	void Set(float value, int rowIndex, int columnIndex);

	float ComputePrediction(FastMatrix& matrix);

	static FastMatrix AddSquaredColumns(FastMatrix& matrix);

	static FastMatrix AddOnesColumn(FastMatrix& matrix);

	void ZeroValues();

	static FastMatrix ComplexConjugateTransform(FastMatrix& matrix);

	static FastMatrix DescendGradient(FastMatrix& XMatrix,  FastMatrix& yVector, float alpha, int numIterations);

	static FastMatrix DescendGradientOptimized(FastMatrix& XMatrix, FastMatrix& yVector, float alpha, int numIterations);

	FastMatrix operator *(FastMatrix& matrix);
	FastMatrix operator *(float scalar);
	FastMatrix operator /(float inversedScalar);
	FastMatrix operator -(FastMatrix& matrix);
	FastMatrix operator +(FastMatrix& matrix);

	void operator -=(FastMatrix& matrix);
	void operator *=(float scalar);
};


extern "C"
{
	__declspec(dllexport) FastMatrix* FastMatrix_Create(int rowCount, int columnCount)
	{
		return new FastMatrix(rowCount, columnCount);
	}

	__declspec(dllexport) float FastMatrix_Get(FastMatrix* pMatrix, int rowIndex, int columnIndex)
	{
		return pMatrix->Get(rowIndex, columnIndex);
	}

	__declspec(dllexport) void FastMatrix_Set(FastMatrix* pMatrix, float value, int rowIndex, int columnIndex)
	{
		pMatrix->Set(value, rowIndex, columnIndex);
	}

	__declspec(dllexport) int FastMatrix_GetRowCount(FastMatrix* pMatrix)
	{
		return pMatrix->GetRowCount();
	}

	__declspec(dllexport) int FastMatrix_GetColumnCount(FastMatrix* pMatrix)
	{
		return pMatrix->GetColumnCount();
	}

	__declspec(dllexport) void FastMatrix_ZeroValues(FastMatrix* pMatrix)
	{
		pMatrix->ZeroValues();
	}

	__declspec(dllexport) FastMatrix* FastMatrix_AddOnesColumn(FastMatrix* pMatrix)
	{
		return new FastMatrix(FastMatrix::AddOnesColumn(*pMatrix));
	}

	__declspec(dllexport) FastMatrix* FastMatrix_AddSquaredColumns(FastMatrix* pMatrix)
	{
		return new FastMatrix(FastMatrix::AddSquaredColumns(*pMatrix));
	}

	__declspec(dllexport)  FastMatrix* FastMatrix_Add(FastMatrix* pMatrix1, FastMatrix* pMatrix2)
	{
		return new FastMatrix(*pMatrix1 + *pMatrix2);
	}

	__declspec(dllexport) FastMatrix* FastMatrix_Subtract(FastMatrix* pMatrix1, FastMatrix* pMatrix2)
	{
		return new FastMatrix(*pMatrix1 - *pMatrix2);
	}

	__declspec(dllexport) FastMatrix* FastMatrix_ScalarMultiply(float scalar, FastMatrix* pMatrix2)
	{
		return new FastMatrix(*pMatrix2 * scalar);
	}

	__declspec(dllexport) FastMatrix* FastMatrix_Multiply(FastMatrix* pMatrix1, FastMatrix* pMatrix2)
	{
		return new FastMatrix(*pMatrix1 * *pMatrix2);
	}

	__declspec(dllexport) FastMatrix* FastMatrix_DescendGradient(FastMatrix* pXMatrix, FastMatrix* pYMatrix, float alpha, int numIterations)
	{
		return new FastMatrix(FastMatrix::DescendGradient(*pXMatrix, *pYMatrix, alpha, numIterations));
	}

	__declspec(dllexport) FastMatrix* FastMatrix_DescendGradient_Optimized(FastMatrix* pXMatrix, FastMatrix* pYMatrix, float alpha, int numIterations)
	{
		return new FastMatrix(FastMatrix::DescendGradientOptimized(*pXMatrix, *pYMatrix, alpha, numIterations));
	}

	__declspec(dllexport) float FastMatrix_ComputePrediction(FastMatrix* pThetaMatrix, FastMatrix* pXmatrix)
	{
		return pThetaMatrix->ComputePrediction(*pXmatrix);
	}

	__declspec(dllexport) void FastMatrix_Delete(FastMatrix* pMatrix)
	{
		delete pMatrix;
	}
}