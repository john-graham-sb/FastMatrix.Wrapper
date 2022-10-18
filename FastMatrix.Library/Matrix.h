class FastMatrix {

private:

	float* _matrix;
	int _rowCount;
	int _columnCount;

public:

	FastMatrix(int rowCount, int columnCount)
	{
		this->_rowCount = rowCount;
		this->_columnCount = columnCount;

		this->_matrix = new float[rowCount * columnCount];
	}

	float Get(int rowIndex, int columnIndex);

	void Set(float number, int rowIndex, int columnIndex);

	float Get(int index);

	void Set(float number, int index);

	float ComputePrediction(FastMatrix* x);

	void ZeroValues();

	void SubtractUpdate(FastMatrix* matrix2);

	static FastMatrix* Subtract(FastMatrix* matrix1, FastMatrix* matrix2);

	static FastMatrix* Add(FastMatrix* matrix1, FastMatrix* matrix2);

	static FastMatrix* ScalarDivide(FastMatrix* matrix, float scalar);

	static FastMatrix* ScalarMultiply(float scalar, FastMatrix* matrix2);

	void ScalarMultiplyUpdate(float scalar);

	static FastMatrix* Multiply(FastMatrix* matrix1, FastMatrix* matrix2);

	static FastMatrix* ComplexConjugateTransform(FastMatrix* matrix);

	static FastMatrix* DescendGradient(FastMatrix* X,  FastMatrix* y, float alpha, int numIterations);
};

extern "C" __declspec(dllexport) FastMatrix* FastMatrix_Create(int rowCount, int columnCount) 
{ 
	return new FastMatrix(rowCount, columnCount); 
}

extern "C" __declspec(dllexport) void FastMatrix_ZeroValues(FastMatrix * matrix)
{
	matrix->ZeroValues();
}

extern "C" __declspec(dllexport) FastMatrix* FastMatrix_Add(FastMatrix * matrix1, FastMatrix * matrix2)
{
	return FastMatrix::Add(matrix1, matrix2);
}

extern "C" __declspec(dllexport) FastMatrix * FastMatrix_Subtract(FastMatrix * matrix1, FastMatrix * matrix2)
{
	return FastMatrix::Subtract(matrix1, matrix2);
}

extern "C" __declspec(dllexport) float FastMatrix_Get(FastMatrix * pFastMatrix, int rowIndex, int columnIndex) 
{ 
	return pFastMatrix->Get(rowIndex, columnIndex); 
}

extern "C" __declspec(dllexport) void FastMatrix_Set(FastMatrix * pFastMatrix, float value, int rowIndex, int columnIndex) 
{ 
	pFastMatrix->Set(value, rowIndex, columnIndex); 
}

extern "C" __declspec(dllexport) FastMatrix * FastMatrix_ScalarMultiply(float scalar, FastMatrix* matrix2) {

	return FastMatrix::ScalarMultiply(scalar, matrix2);
}

extern "C" __declspec(dllexport) FastMatrix * FastMatrix_Multiply(FastMatrix * matrix1, FastMatrix * matrix2) {

	return FastMatrix::Multiply(matrix1, matrix2);
}

extern "C" __declspec(dllexport) FastMatrix * FastMatrix_ComplexConjugateTransform(FastMatrix * matrix)
{
	return FastMatrix::ComplexConjugateTransform(matrix);
}

extern "C" __declspec(dllexport) FastMatrix * FastMatrix_DescendGradient(FastMatrix * X, FastMatrix * y, float alpha, int numIterations)
{
	return FastMatrix::DescendGradient(X, y, alpha, numIterations);
}

extern "C" __declspec(dllexport) float FastMatrix_ComputePrediction(FastMatrix* theta, FastMatrix* x)
{
	return theta->ComputePrediction(x);
}

extern "C" __declspec(dllexport) void FastMatrix_Delete(FastMatrix * pFastMatrix) 
{ 
	delete pFastMatrix; 
}