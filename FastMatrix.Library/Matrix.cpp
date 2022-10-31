#include "pch.h"
#include "matrix.h"

float FastMatrix::Get(int rowIndex, int columnIndex)
{
	return this->_matrix[rowIndex + columnIndex * this->_rowCount];
}

void FastMatrix::Set(float value, int rowIndex, int columnIndex)
{
	this->_matrix[rowIndex + columnIndex * this->_rowCount] = value;
}

float FastMatrix::ComputePrediction(FastMatrix* pXMatrix)
{
	float prediction = 0;

	for (int matrixRowIndex = 0; matrixRowIndex < _rowCount; matrixRowIndex++)
	{
		float theta = Get(matrixRowIndex, 0);

		float x = pXMatrix->Get(0, matrixRowIndex);

		prediction += theta * x;
	}

	return prediction;
}

FastMatrix* FastMatrix::AddOnesColumn(FastMatrix* pMatrix)
{
	FastMatrix* pNewMatrix = new FastMatrix(pMatrix->_rowCount, pMatrix->_columnCount + 1);

	// Set 1's in first column of new matrix.
	for (int matrixRowIndex = 0; matrixRowIndex < pNewMatrix->_rowCount; matrixRowIndex++)
	{
		pNewMatrix->Set(1, matrixRowIndex, 0);
	}

	// Copy the contents of the original matrix into the new matrix, advanced one column.
	for (int matrixColumnIndex = 0; matrixColumnIndex < pMatrix->_columnCount; matrixColumnIndex++)
	{
		for (int matrixRowIndex = 0; matrixRowIndex < pMatrix->_rowCount; matrixRowIndex++)
		{
			float value = pMatrix->Get(matrixRowIndex, matrixColumnIndex);

			pNewMatrix->Set(value, matrixRowIndex, matrixColumnIndex + 1);
		}
	}

	return pNewMatrix;
}

FastMatrix* FastMatrix::AddSquaredColumns(FastMatrix* pMatrix)
{
	int newColumnCount = FastMatrix::ConsequtiveSum(1, pMatrix->_columnCount) + pMatrix->_columnCount;

	FastMatrix* pNewMatrix = new FastMatrix(pMatrix->_rowCount, newColumnCount);

	for (int matrixRowIndex = 0; matrixRowIndex < pMatrix->_rowCount; matrixRowIndex++)
	{
		for (int matrixColumnIndex = 0; matrixColumnIndex < pMatrix->_columnCount; matrixColumnIndex++)
		{
			float value = pMatrix->Get(matrixRowIndex, matrixColumnIndex);

			pNewMatrix->Set(value, matrixRowIndex, matrixColumnIndex);
		}
	}

	for (int newMatrixRowIndex = 0; newMatrixRowIndex < pNewMatrix->_rowCount; newMatrixRowIndex++)
	{
		int currentStartIndex = -1;

		for (int newMatrixColumnIndex = pMatrix->_columnCount; newMatrixColumnIndex < pNewMatrix->_columnCount; newMatrixColumnIndex++)
		{
			currentStartIndex++;

			for (int columnIndex = currentStartIndex; columnIndex < pMatrix->_columnCount; columnIndex++)
			{
				float value1 = pMatrix->Get(newMatrixRowIndex, columnIndex);
				float value2 = pMatrix->Get(newMatrixRowIndex, currentStartIndex);

				pNewMatrix->Set(value1 * value2, newMatrixRowIndex, newMatrixColumnIndex + columnIndex);
			}
		}
	}

	return pNewMatrix;
}

void FastMatrix::ZeroValues()
{
	for (int matrixColumnIndex = 0; matrixColumnIndex < _columnCount; matrixColumnIndex++)
	{
		for (int matrixRowIndex = 0; matrixRowIndex < _rowCount; matrixRowIndex++)
		{
			Set(0, matrixRowIndex, matrixColumnIndex);
		}
	}
}

FastMatrix* FastMatrix::DescendGradient(FastMatrix* X, FastMatrix* y, float alpha, int numIterations)
{
	float scalar = alpha / X->_rowCount;

	FastMatrix* xTransformed = FastMatrix::ComplexConjugateTransform(X);

	FastMatrix* theta = new FastMatrix(X->_columnCount, 1);
	theta->ZeroValues();

	FastMatrix* hypothesis = new FastMatrix(X->_rowCount, theta->_columnCount);

	FastMatrix* derivative;

	for (int iterationIndex = 0; iterationIndex < numIterations; iterationIndex++)
	{
		FastMatrix::MultiplyUpdate(hypothesis, X, theta);

		hypothesis->SubtractUpdate(y);

		derivative = FastMatrix::Multiply(xTransformed, hypothesis);

		derivative->ScalarMultiplyUpdate(scalar);

		theta->SubtractUpdate(derivative);

		delete(derivative);
	}

	delete(hypothesis);
	delete(xTransformed);

	return theta;
}

FastMatrix* FastMatrix::ComplexConjugateTransform(FastMatrix* matrix)
{
	FastMatrix* transformedMatrix = new FastMatrix(matrix->_columnCount, matrix->_rowCount);

	for (int matrixColumnIndex = 0; matrixColumnIndex < matrix->_columnCount; matrixColumnIndex++)
	{
		for (int matrixRowIndex = 0; matrixRowIndex < matrix->_rowCount; matrixRowIndex++)
		{
			float value = matrix->Get(matrixRowIndex, matrixColumnIndex);

			transformedMatrix->Set(value, matrixColumnIndex, matrixRowIndex);
		}
	}

	return transformedMatrix;
}

FastMatrix* FastMatrix::Add(FastMatrix* matrix1, FastMatrix* matrix2)
{
	FastMatrix* sumMatrix = new FastMatrix(matrix1->_rowCount, matrix2->_columnCount);

	for (int rowIndex = 0; rowIndex < matrix1->_rowCount; rowIndex++)
	{
		for (int columnIndex = 0; columnIndex < matrix1->_columnCount; columnIndex++)
		{
			float value1 = matrix1->Get(rowIndex, columnIndex);
			float value2 = matrix2->Get(rowIndex, columnIndex);

			sumMatrix->Set(value1 + value2, rowIndex, columnIndex);
		}
	}

	return sumMatrix;
}


// ..Update() functions eliminate the need to create then delete objects. 
void FastMatrix::SubtractUpdate(FastMatrix* pMatrix2)
{
	for (int rowIndex = 0; rowIndex < _rowCount; rowIndex++)
	{
		for (int columnIndex = 0; columnIndex < _columnCount; columnIndex++)
		{
			float firstValue = Get(rowIndex, columnIndex);
			float secondValue = pMatrix2->Get(rowIndex, columnIndex);

			Set(firstValue - secondValue, rowIndex, columnIndex);
		}
	}
}

FastMatrix* FastMatrix::Subtract(FastMatrix* matrix1, FastMatrix* matrix2)
{
	FastMatrix* differenceMatrix = new FastMatrix(matrix1->_rowCount, matrix2->_columnCount);

	for (int rowIndex = 0; rowIndex < matrix1->_rowCount; rowIndex++)
	{
		for (int columnIndex = 0; columnIndex < matrix1->_columnCount; columnIndex++)
		{
			float firstValue = matrix1->Get(rowIndex, columnIndex);
			float secondValue = matrix2->Get(rowIndex, columnIndex);

			differenceMatrix->Set(firstValue - secondValue, rowIndex, columnIndex);
		}
	}

	return differenceMatrix;
}

FastMatrix* FastMatrix::ScalarDivide(FastMatrix* matrix, float scalar)
{
	return FastMatrix::ScalarMultiply(1 / scalar, matrix);
}

FastMatrix* FastMatrix::ScalarMultiply(float scalar, FastMatrix* matrix)
{
	FastMatrix* scaledMatrix = new FastMatrix(matrix->_rowCount, matrix->_columnCount);

	for (int rowIndex = 0; rowIndex < matrix->_rowCount; rowIndex++)
	{
		for (int columnIndex = 0; columnIndex < matrix->_columnCount; columnIndex++)
		{
			float value = matrix->Get(rowIndex, columnIndex);

			scaledMatrix->Set(scalar * value, rowIndex, columnIndex);
		}
	}

	return scaledMatrix;
}

void FastMatrix::ScalarMultiplyUpdate(float scalar)
{
	for (int rowIndex = 0; rowIndex < _rowCount; rowIndex++)
	{
		for (int columnIndex = 0; columnIndex < _columnCount; columnIndex++)
		{
			float value = Get(rowIndex, columnIndex);

			Set(scalar * value, rowIndex, columnIndex);
		}
	}
}

FastMatrix* FastMatrix::Multiply(FastMatrix* matrix1, FastMatrix* matrix2)
{
	FastMatrix* productMatrix = new FastMatrix(matrix1->_rowCount, matrix2->_columnCount);

	for (int _productColumnIndex = 0; _productColumnIndex < matrix2->_columnCount; _productColumnIndex++)
	{
		for (int _rowIndex = 0; _rowIndex < matrix1->_rowCount; _rowIndex++)
		{
			float value = 0;

			for (int _columnIndex = 0; _columnIndex < matrix1->_columnCount; _columnIndex++)
			{
				float value1 = matrix1->Get(_rowIndex, _columnIndex);
				float value2 = matrix2->Get(_columnIndex, _productColumnIndex);

				value += value1 * value2;
			}

			productMatrix->Set(value, _rowIndex, _productColumnIndex);
		}
	}

	return productMatrix;
}
void FastMatrix::MultiplyUpdate(FastMatrix* pProductMatrix, FastMatrix* pMatrix1, FastMatrix* pMatrix2)
{
	for (int _productColumnIndex = 0; _productColumnIndex < pMatrix2->_columnCount; _productColumnIndex++)
	{
		for (int _rowIndex = 0; _rowIndex < pMatrix1->_rowCount; _rowIndex++)
		{
			float value = 0;

			for (int _columnIndex = 0; _columnIndex < pMatrix1->_columnCount; _columnIndex++)
			{
				float value1 = pMatrix1->Get(_rowIndex, _columnIndex);
				float value2 = pMatrix2->Get(_columnIndex,  _productColumnIndex);

				value += value1 * value2;
			}

			pProductMatrix->Set(value, _rowIndex,  _productColumnIndex);
		}
	}
}