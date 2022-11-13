#include "pch.h"
#include "matrix.h"

float FastMatrix::Get(int rowIndex, int columnIndex)
{
	float value = this->_matrix[rowIndex + columnIndex * this->_rowCount];

	return value;
}

void FastMatrix::Set(float value, int rowIndex, int columnIndex)
{
	this->_matrix[rowIndex + columnIndex * this->_rowCount] = value;
}

float FastMatrix::ComputePrediction(FastMatrix& matrix)
{
	float prediction = 0;

	for (int thetaRowIndex = 0; thetaRowIndex < this->_rowCount; thetaRowIndex++)
	{
		float theta = Get(thetaRowIndex, 0);

		float x = matrix.Get(0, thetaRowIndex);

		prediction += theta * x;
	}

	return prediction;
}

FastMatrix FastMatrix::AddOnesColumn(FastMatrix& originalMatrix)
{
	FastMatrix newMatrix(originalMatrix._rowCount, originalMatrix._columnCount + 1);

	for (int matrixRowIndex = 0; matrixRowIndex < newMatrix._rowCount; matrixRowIndex++)
	{
		newMatrix.Set(1, matrixRowIndex, 0);
	}

	for (int matrixColumnIndex = 0; matrixColumnIndex < originalMatrix._columnCount; matrixColumnIndex++)
	{
		for (int matrixRowIndex = 0; matrixRowIndex < originalMatrix._rowCount; matrixRowIndex++)
		{
			float value = originalMatrix.Get(matrixRowIndex, matrixColumnIndex);

			newMatrix.Set(value, matrixRowIndex, matrixColumnIndex + 1);
		}
	}

	return newMatrix;
}

FastMatrix FastMatrix::AddSquaredColumns(FastMatrix& originalMatrix)
{
	int newColumnCount = FastMatrix::ConsequtiveSum(1, originalMatrix._columnCount) + originalMatrix._columnCount;

	FastMatrix newMatrix(originalMatrix._rowCount, newColumnCount);

	for (int matrixRowIndex = 0; matrixRowIndex < originalMatrix._rowCount; matrixRowIndex++)
	{
		for (int matrixColumnIndex = 0; matrixColumnIndex < originalMatrix._columnCount; matrixColumnIndex++)
		{
			float value = originalMatrix.Get(matrixRowIndex, matrixColumnIndex);

			newMatrix.Set(value, matrixRowIndex, matrixColumnIndex);
		}
	}

	for (int newMatrixRowIndex = 0; newMatrixRowIndex < newMatrix._rowCount; newMatrixRowIndex++)
	{
		int currentStartIndex = -1;

		for (int newMatrixColumnIndex = originalMatrix._columnCount; newMatrixColumnIndex < newMatrix._columnCount; newMatrixColumnIndex++)
		{
			currentStartIndex++;

			for (int columnIndex = currentStartIndex; columnIndex < originalMatrix._columnCount; columnIndex++)
			{
				float value1 = originalMatrix.Get(newMatrixRowIndex, columnIndex);
				float value2 = originalMatrix.Get(newMatrixRowIndex, currentStartIndex);

				newMatrix.Set(value1 * value2, newMatrixRowIndex, newMatrixColumnIndex + columnIndex);
			}
		}
	}

	return newMatrix;
}

void FastMatrix::ZeroValues()
{
	for (int matrixColumnIndex = 0; matrixColumnIndex < this->_columnCount; matrixColumnIndex++)
	{
		for (int matrixRowIndex = 0; matrixRowIndex < this->_rowCount; matrixRowIndex++)
		{
			this->Set(0, matrixRowIndex, matrixColumnIndex);
		}
	}
}

FastMatrix FastMatrix::DescendGradient(FastMatrix& XMatrix, FastMatrix& yVector, float alpha, int numIterations)
{
	float scalar = alpha / XMatrix._rowCount;

	FastMatrix xPrime = FastMatrix::ComplexConjugateTransform(XMatrix);

	FastMatrix theta(XMatrix._columnCount, 1);
	theta.ZeroValues();

	for (int iterationIndex = 0; iterationIndex < numIterations; iterationIndex++)
	{
		FastMatrix error = XMatrix * theta - yVector;

		FastMatrix derivative = xPrime * error;

		derivative *= scalar;

		theta -= derivative;
	}

	return theta;
}

FastMatrix FastMatrix::DescendGradientOptimized(FastMatrix& XMatrix, FastMatrix& yVector, float alpha, int numIterations)
{
	float scalar = alpha / XMatrix._rowCount;

	FastMatrix XPrime = FastMatrix::ComplexConjugateTransform(XMatrix);

	FastMatrix thetaMatrix(XMatrix._columnCount, 1);
	thetaMatrix.ZeroValues();

	FastMatrix hypothesis(XMatrix._rowCount, thetaMatrix._columnCount);

	for (int iterationIndex = 0; iterationIndex < numIterations; iterationIndex++)
	{
		hypothesis.MultiplyThenSubtractUpdate(XMatrix, thetaMatrix, yVector);

		FastMatrix drivative = XPrime * hypothesis;

		thetaMatrix.ScalarMultiplyThenSubtractUpdate(scalar, drivative);
	}

	return thetaMatrix;
}

FastMatrix FastMatrix::ComplexConjugateTransform(FastMatrix& matrix)
{
	FastMatrix transformedMatrix(matrix._columnCount, matrix._rowCount);

	for (int matrixColumnIndex = 0; matrixColumnIndex < matrix._columnCount; matrixColumnIndex++)
	{
		for (int matrixRowIndex = 0; matrixRowIndex < matrix._rowCount; matrixRowIndex++)
		{
			float value = matrix.Get(matrixRowIndex, matrixColumnIndex);

			transformedMatrix.Set(value, matrixColumnIndex, matrixRowIndex);
		}
	}

	return transformedMatrix;
}

void FastMatrix::ScalarMultiplyThenSubtractUpdate(float scalar, FastMatrix& matrix)
{
	for (int rowIndex = 0; rowIndex < this->_rowCount; rowIndex++)
	{
		for (int columnIndex = 0; columnIndex < this->_columnCount; columnIndex++)
		{
			float value1 = matrix.Get(rowIndex, columnIndex);
			float value2 = this->Get(rowIndex, columnIndex);

			this->Set(value2 - (scalar * value1), rowIndex, columnIndex);
		}
	}
}

void FastMatrix::MultiplyThenSubtractUpdate(FastMatrix& matrix1, FastMatrix& matrix2, FastMatrix& matrix3)
{
	for (int _productColumnIndex = 0; _productColumnIndex < matrix2._columnCount; _productColumnIndex++)
	{
		for (int _rowIndex = 0; _rowIndex < matrix1._rowCount; _rowIndex++)
		{
			float value = 0;

			for (int _columnIndex = 0; _columnIndex < matrix1._columnCount; _columnIndex++)
			{
				float value1 = matrix1.Get(_rowIndex, _columnIndex);
				float value2 = matrix2.Get(_columnIndex, _productColumnIndex);

				value += value1 * value2;
			}

			float value3 = matrix3.Get(_rowIndex, 0);

			this->Set(value - value3, _rowIndex, _productColumnIndex);
		}
	}
}

FastMatrix FastMatrix::operator *(FastMatrix& rhsMatrix)
{
	FastMatrix& lhsMatrix = *this;

	FastMatrix productMatrix(lhsMatrix._rowCount, rhsMatrix._columnCount);

	for (int _productColumnIndex = 0; _productColumnIndex < rhsMatrix._columnCount; _productColumnIndex++)
	{
		for (int _rowIndex = 0; _rowIndex < lhsMatrix._rowCount; _rowIndex++)
		{
			float newValue = 0;

			for (int _columnIndex = 0; _columnIndex < lhsMatrix._columnCount; _columnIndex++)
			{
				float lhsValue = lhsMatrix.Get(_rowIndex, _columnIndex);
				float rhsValue = rhsMatrix.Get(_columnIndex, _productColumnIndex);

				newValue += lhsValue * rhsValue;
			}

			productMatrix.Set(newValue, _rowIndex, _productColumnIndex);
		}
	}

	return productMatrix;
}

FastMatrix FastMatrix::operator *(float scalar)
{
	FastMatrix& matrix = *this;

	FastMatrix pScaledMatrix(matrix._rowCount, matrix._columnCount);

	for (int rowIndex = 0; rowIndex < matrix._rowCount; rowIndex++)
	{
		for (int columnIndex = 0; columnIndex < matrix._columnCount; columnIndex++)
		{
			float originalValue = matrix.Get(rowIndex, columnIndex);

			pScaledMatrix.Set(originalValue * scalar, rowIndex, columnIndex);
		}
	}

	return pScaledMatrix;
}

FastMatrix FastMatrix::operator /(float inversedScalar)
{
	FastMatrix& matrix = *this;

	return matrix * (1 / inversedScalar);
}

FastMatrix FastMatrix::operator -(FastMatrix& rhsMatrix)
{
	FastMatrix& lhsMatrix = *this;

	FastMatrix differenceMatrix(lhsMatrix._rowCount, rhsMatrix._columnCount);

	for (int rowIndex = 0; rowIndex < lhsMatrix._rowCount; rowIndex++)
	{
		for (int columnIndex = 0; columnIndex < lhsMatrix._columnCount; columnIndex++)
		{
			float lhsValue = lhsMatrix.Get(rowIndex, columnIndex);
			float rhsValue = rhsMatrix.Get(rowIndex, columnIndex);

			differenceMatrix.Set(lhsValue - rhsValue, rowIndex, columnIndex);
		}
	}

	return differenceMatrix;
}

FastMatrix FastMatrix::operator +(FastMatrix& rhsMatrix)
{
	FastMatrix& lhsMatrix = *this;

	FastMatrix sumMatrix(lhsMatrix._rowCount, rhsMatrix._columnCount);

	for (int rowIndex = 0; rowIndex < lhsMatrix._rowCount; rowIndex++)
	{
		for (int columnIndex = 0; columnIndex < lhsMatrix._columnCount; columnIndex++)
		{
			float lhsValue = lhsMatrix.Get(rowIndex, columnIndex);
			float rhsValue = rhsMatrix.Get(rowIndex, columnIndex);

			sumMatrix.Set(lhsValue + rhsValue, rowIndex, columnIndex);
		}
	}

	return sumMatrix;
}

void FastMatrix::operator *=(float scalar)
{
	FastMatrix& matrix = *this;

	for (int rowIndex = 0; rowIndex < matrix._rowCount; rowIndex++)
	{
		for (int columnIndex = 0; columnIndex < matrix._columnCount; columnIndex++)
		{
			float originalValue = matrix.Get(rowIndex, columnIndex);

			matrix.Set(originalValue * scalar, rowIndex, columnIndex);
		}
	}
}

void FastMatrix::operator -=(FastMatrix& rhsMatirx)
{
	FastMatrix& lhsMatrix = *this;

	for (int rowIndex = 0; rowIndex < lhsMatrix._rowCount; rowIndex++)
	{
		for (int columnIndex = 0; columnIndex < lhsMatrix._columnCount; columnIndex++)
		{
			float lhsValue = lhsMatrix.Get(rowIndex, columnIndex);
			float rhsValue = rhsMatirx.Get(rowIndex, columnIndex);

			lhsMatrix.Set(lhsValue - rhsValue, rowIndex, columnIndex);
		}
	}
}