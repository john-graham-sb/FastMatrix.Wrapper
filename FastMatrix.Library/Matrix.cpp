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

float FastMatrix::Get(int index)
{
	return this->_matrix[index];
}

void FastMatrix::Set(float value, int index)
{
	this->_matrix[index] = value;
}

float FastMatrix::ComputePrediction(FastMatrix* x)
{
	float prediction = 0;
	
	for (int index = 0; index < x->_columnCount; index++)
	{
		float value1 = x->Get(index);
		float value2 = Get(index);

		prediction += value1 * value2;
	}

	return prediction;
}

void FastMatrix::ZeroValues()
{
	for (int matrixColumnIndex = 0; matrixColumnIndex < _columnCount; matrixColumnIndex++)
	{
		for (int matrixRowIndex = 0; matrixRowIndex < _rowCount; matrixRowIndex++)
		{
			Set(0, matrixRowIndex + matrixColumnIndex * _rowCount);
		}
	}
}

FastMatrix* FastMatrix::DescendGradient(FastMatrix* X, FastMatrix* y, float alpha, int numIterations)
{
	float scalar = alpha / X->_rowCount;

	FastMatrix* xTransformed = FastMatrix::ComplexConjugateTransform(X);
	FastMatrix* theta = new FastMatrix(X->_columnCount, 1);
	theta->ZeroValues();

	FastMatrix* hypothesis;
	FastMatrix* derivative;
	
	for (int iterationIndex = 0; iterationIndex < numIterations; iterationIndex++)
	{
		hypothesis = FastMatrix::Multiply(X, theta);

		hypothesis->SubtractUpdate(y);

		derivative = FastMatrix::Multiply(xTransformed, hypothesis);

		derivative->ScalarMultiplyUpdate(scalar);

		theta->SubtractUpdate(derivative);

		delete(hypothesis);
		delete(derivative);
	}

	delete(xTransformed);

	return theta;
}

FastMatrix* FastMatrix::ComplexConjugateTransform(FastMatrix* matrix)
{
	FastMatrix* transformedMatrix = new FastMatrix(matrix->_columnCount, matrix->_rowCount);
	
	for(int matrixColumnIndex = 0; matrixColumnIndex < matrix->_columnCount; matrixColumnIndex++)
	{
		for (int matrixRowIndex = 0; matrixRowIndex < matrix->_rowCount; matrixRowIndex++)
		{
			float value = matrix->Get(matrixRowIndex + matrixColumnIndex * matrix->_rowCount);

			transformedMatrix->Set(value, matrixColumnIndex + matrixRowIndex * transformedMatrix->_rowCount);
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

void FastMatrix::SubtractUpdate(FastMatrix* matrix2)
{

	for (int rowIndex = 0; rowIndex < _rowCount; rowIndex++)
	{
		for (int columnIndex = 0; columnIndex < _columnCount; columnIndex++)
		{
			float value1 = Get(rowIndex, columnIndex);
			float value2 = matrix2->Get(rowIndex, columnIndex);

			Set(value1 - value2, rowIndex, columnIndex);
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
			float value1 = matrix1->Get(rowIndex, columnIndex);
			float value2 = matrix2->Get(rowIndex, columnIndex);

			differenceMatrix->Set(value1 - value2, rowIndex, columnIndex);
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
				float value1 = matrix1->Get(_rowIndex + _columnIndex * matrix1->_rowCount);
				float value2 = matrix2->Get(_columnIndex + _productColumnIndex * matrix2->_rowCount);

				value += value1 * value2;
			}

			productMatrix->Set(value, _rowIndex + _productColumnIndex * matrix1->_rowCount);
		}
	}

	return productMatrix;
}