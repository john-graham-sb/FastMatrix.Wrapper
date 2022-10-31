class FastMatrix {

private:

	float* _matrix;
	int _rowCount;
	int _columnCount;

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

	FastMatrix(int rowCount, int columnCount)
	{
		this->_rowCount = rowCount;
		this->_columnCount = columnCount;

		this->_matrix = new float[rowCount * columnCount];
	}

	int GetRowCount()
	{
		return _rowCount;
	}

	int GetColumnCount()
	{
		return _columnCount;
	}

	float Get(int rowIndex, int columnIndex);

	void Set(float value, int rowIndex, int columnIndex);

	float ComputePrediction(FastMatrix* pXMatrix);

	static FastMatrix* AddSquaredColumns(FastMatrix* pMatrix);

	static FastMatrix* AddOnesColumn(FastMatrix* pMatrix);

	void ZeroValues();

	void SubtractUpdate(FastMatrix* pMatrix2);

	static FastMatrix* Subtract(FastMatrix* pMatrix1, FastMatrix* pMatrix2);

	static FastMatrix* Add(FastMatrix* pMatrix1, FastMatrix* pMatrix2);

	static FastMatrix* ScalarDivide(FastMatrix* pMatrix, float scalar);

	static FastMatrix* ScalarMultiply(float scalar, FastMatrix* pMatrix);

	void ScalarMultiplyUpdate(float scalar);

	static void MultiplyUpdate(FastMatrix* pProductMatrix, FastMatrix* pMatrix1, FastMatrix* pMatrix2);

	static FastMatrix* Multiply(FastMatrix* pMatrix1, FastMatrix* pMatrix2);

	static FastMatrix* ComplexConjugateTransform(FastMatrix* pMatrix);

	static FastMatrix* DescendGradient(FastMatrix* pXMatrix,  FastMatrix* pYMatrix, float alpha, int numIterations);
};

extern "C"
{
	__declspec(dllexport) int FastMatrix_GetRowCount(FastMatrix* pMatrix)
	{
		return pMatrix->GetRowCount();
	}

	__declspec(dllexport) int FastMatrix_GetColumnCount(FastMatrix* pMatrix)
	{
		return pMatrix->GetColumnCount();
	}

	__declspec(dllexport) FastMatrix* FastMatrix_Create(int rowCount, int columnCount)
	{
		return new FastMatrix(rowCount, columnCount);
	}

	__declspec(dllexport) void FastMatrix_ZeroValues(FastMatrix* pMatrix)
	{
		pMatrix->ZeroValues();
	}

	__declspec(dllexport)  FastMatrix* FastMatrix_Add(FastMatrix* pMatrix1, FastMatrix* pMatrix2)
	{
		return FastMatrix::Add(pMatrix1, pMatrix2);
	}

	__declspec(dllexport) FastMatrix* FastMatrix_Subtract(FastMatrix* pMatrix1, FastMatrix* pMatrix2)
	{
		return FastMatrix::Subtract(pMatrix1, pMatrix2);
	}

	__declspec(dllexport) float FastMatrix_Get(FastMatrix* pMatrix, int rowIndex, int columnIndex)
	{
		return pMatrix->Get(rowIndex, columnIndex);
	}

	__declspec(dllexport) void FastMatrix_Set(FastMatrix* pMatrix, float value, int rowIndex, int columnIndex)
	{
		pMatrix->Set(value, rowIndex, columnIndex);
	}

	__declspec(dllexport) FastMatrix* FastMatrix_ScalarMultiply(float scalar, FastMatrix* pMatrix2)
	{

		return FastMatrix::ScalarMultiply(scalar, pMatrix2);
	}

	__declspec(dllexport) FastMatrix* FastMatrix_Multiply(FastMatrix* pMatrix1, FastMatrix* pMatrix2)
	{

		return FastMatrix::Multiply(pMatrix1, pMatrix2);
	}

	__declspec(dllexport) FastMatrix* FastMatrix_ComplexConjugateTransform(FastMatrix* pMatrix)
	{
		return FastMatrix::ComplexConjugateTransform(pMatrix);
	}

	__declspec(dllexport) FastMatrix* FastMatrix_DescendGradient(FastMatrix* pXMatrix, FastMatrix* pYMatrix, float alpha, int numIterations)
	{
		return FastMatrix::DescendGradient(pXMatrix, pYMatrix, alpha, numIterations);
	}

	__declspec(dllexport) float FastMatrix_ComputePrediction(FastMatrix* pThetaMatrix, FastMatrix* pXmatrix)
	{
		return pThetaMatrix->ComputePrediction(pXmatrix);
	}

	__declspec(dllexport) FastMatrix* FastMatrix_AddOnesColumn(FastMatrix* pMatrix)
	{
		return FastMatrix::AddOnesColumn(pMatrix);
	}

	__declspec(dllexport) FastMatrix* FastMatrix_AddSquaredColumns(FastMatrix* pMatrix)
	{
		return FastMatrix::AddSquaredColumns(pMatrix);
	}

	__declspec(dllexport) void FastMatrix_Delete(FastMatrix* pMatrix)
	{
		delete pMatrix;
	}
}