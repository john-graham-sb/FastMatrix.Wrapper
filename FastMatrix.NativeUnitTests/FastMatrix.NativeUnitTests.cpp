#include "pch.h"
#include "CppUnitTest.h"
#include "../FastMatrix.Library/Matrix.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace FastMatrixNativeUnitTests
{
	TEST_CLASS(FastMatrixNativeUnitTests)
	{
	public:

		TEST_METHOD(Set_And_Get)
		{
			FastMatrix* pMatrix = new FastMatrix(2, 3);

			pMatrix->Set(0.0, 0, 0);
			pMatrix->Set(0.5, 0, 1);
			pMatrix->Set(1, 0, 2);
			pMatrix->Set(1.5, 1, 0);
			pMatrix->Set(-1, 1, 1);
			pMatrix->Set(-1.5, 1, 2);

			Assert::AreEqual(0.0F, pMatrix->Get(0, 0));
			Assert::AreEqual(0.5F, pMatrix->Get(0, 1));
			Assert::AreEqual(1.0F, pMatrix->Get(0, 2));
			Assert::AreEqual(1.5F, pMatrix->Get(1, 0));
			Assert::AreEqual(-1.0F, pMatrix->Get(1, 1));
			Assert::AreEqual(-1.5F, pMatrix->Get(1, 2));

			delete(pMatrix);
		}

		TEST_METHOD(Add_Ones_Column)
		{
			FastMatrix* pMatrix = new FastMatrix(2, 3);

			pMatrix->Set(0.0, 0, 0);
			pMatrix->Set(0.5, 0, 1);
			pMatrix->Set(1, 0, 2);
			pMatrix->Set(1.5, 1, 0);
			pMatrix->Set(-1, 1, 1);
			pMatrix->Set(-1.5, 1, 2);

			FastMatrix* pNewMatrix = FastMatrix::AddOnesColumn(pMatrix);

			Assert::AreEqual(1.0F, pNewMatrix->Get(0, 0));
			Assert::AreEqual(0.0F, pNewMatrix->Get(0, 1));
			Assert::AreEqual(0.5F, pNewMatrix->Get(0, 2));
			Assert::AreEqual(1.0F, pNewMatrix->Get(0, 3));

			Assert::AreEqual(1.0F, pNewMatrix->Get(1, 0));
			Assert::AreEqual(1.5F, pNewMatrix->Get(1, 1));
			Assert::AreEqual(-1.0F, pNewMatrix->Get(1, 2));
			Assert::AreEqual(-1.5F, pNewMatrix->Get(1, 3));

			delete(pMatrix);
			delete(pNewMatrix);
		}

		TEST_METHOD(Add_Squared_Columns)
		{
			FastMatrix* pMatrix = new FastMatrix(2, 2);

			pMatrix->Set(0.0, 0, 0);
			pMatrix->Set(0.5, 0, 1);
			pMatrix->Set(1, 1, 0);
			pMatrix->Set(-1.5, 1, 1);

			FastMatrix* pNewMatrix = FastMatrix::AddSquaredColumns(pMatrix);

			Assert::AreEqual(0.0F, pNewMatrix->Get(0, 0));
			Assert::AreEqual(0.5F, pNewMatrix->Get(0, 1));
			Assert::AreEqual(0.0F * 0.0F, pNewMatrix->Get(0, 2));
			Assert::AreEqual(0.0F * 0.5F, pNewMatrix->Get(0, 3));
			Assert::AreEqual(0.5F * 0.5F, pNewMatrix->Get(0, 4));

			Assert::AreEqual(1.0F, pNewMatrix->Get(1, 0));
			Assert::AreEqual(-1.5F, pNewMatrix->Get(1, 1));
			Assert::AreEqual(1.0F * 1.0F, pNewMatrix->Get(1, 2));
			Assert::AreEqual(1.0F * -1.5F, pNewMatrix->Get(1, 3));
			Assert::AreEqual(-1.5F * -1.5F, pNewMatrix->Get(1, 4));

			delete(pMatrix);
			delete(pNewMatrix);
		}

		TEST_METHOD(Zero_All_Columns)
		{
			FastMatrix* pMatrix = new FastMatrix(2, 3);

			pMatrix->Set(0.0, 0, 0);
			pMatrix->Set(0.5, 0, 1);
			pMatrix->Set(1, 0, 2);
			pMatrix->Set(1.5, 1, 0);
			pMatrix->Set(-1, 1, 1);
			pMatrix->Set(-1.5, 1, 2);

			pMatrix->ZeroValues();

			Assert::AreEqual(0.0F, pMatrix->Get(0, 0));
			Assert::AreEqual(0.0F, pMatrix->Get(0, 1));
			Assert::AreEqual(0.0F, pMatrix->Get(0, 2));

			Assert::AreEqual(0.0F, pMatrix->Get(1, 0));
			Assert::AreEqual(0.0F, pMatrix->Get(1, 1));
			Assert::AreEqual(0.0F, pMatrix->Get(1, 2));

			delete(pMatrix);
		}

		TEST_METHOD(Complex_Conjugate_Transform)
		{
			FastMatrix* pMatrix = new FastMatrix(3, 3);

			pMatrix->Set(0.0, 0, 0);
			pMatrix->Set(0.5, 0, 1);
			pMatrix->Set(1, 0, 2);
			pMatrix->Set(1.5, 1, 0);
			pMatrix->Set(-1, 1, 1);
			pMatrix->Set(-1.5, 1, 2);
			pMatrix->Set(2.5, 2, 0);
			pMatrix->Set(-1.25, 2, 1);
			pMatrix->Set(-9.00009, 2, 2);

			FastMatrix* pNewMatrix = FastMatrix::ComplexConjugateTransform(pMatrix);

			Assert::AreEqual(0.0F, pNewMatrix->Get(0, 0));
			Assert::AreEqual(1.5F, pNewMatrix->Get(0, 1));
			Assert::AreEqual(2.5F, pNewMatrix->Get(0, 2));

			Assert::AreEqual(0.5F, pNewMatrix->Get(1, 0));
			Assert::AreEqual(-1.0F, pNewMatrix->Get(1, 1));
			Assert::AreEqual(-1.25F, pNewMatrix->Get(1, 2));

			Assert::AreEqual(1.0F, pNewMatrix->Get(2, 0));
			Assert::AreEqual(-1.5F, pNewMatrix->Get(2, 1));
			Assert::AreEqual(-9.00009F, pNewMatrix->Get(2, 2));

			delete(pMatrix);
			delete(pNewMatrix);
		}

		TEST_METHOD(Scalar_Multiply_Update)
		{
			FastMatrix* pMatrix = new FastMatrix(2, 3);

			pMatrix->Set(0.0, 0, 0);
			pMatrix->Set(0.5, 0, 1);
			pMatrix->Set(1, 0, 2);
			pMatrix->Set(1.5, 1, 0);
			pMatrix->Set(-1, 1, 1);
			pMatrix->Set(-1.5, 1, 2);

			pMatrix->ScalarMultiplyUpdate(5.1);

			Assert::AreEqual(0.0F * 5.1F, pMatrix->Get(0, 0));
			Assert::AreEqual(0.5F * 5.1F, pMatrix->Get(0, 1));
			Assert::AreEqual(1.0F * 5.1F, pMatrix->Get(0, 2));

			Assert::AreEqual(1.5F * 5.1F, pMatrix->Get(1, 0));
			Assert::AreEqual(-1.0F * 5.1F, pMatrix->Get(1, 1));
			Assert::AreEqual(-1.5F * 5.1F, pMatrix->Get(1, 2));

			delete(pMatrix);
		}

		TEST_METHOD(Multiply)
		{
			FastMatrix* pMatrix1 = new FastMatrix(2, 3);

			pMatrix1->Set(0.0, 0, 0);
			pMatrix1->Set(0.5, 0, 1);
			pMatrix1->Set(1, 0, 2);
			pMatrix1->Set(1.5, 1, 0);
			pMatrix1->Set(-1, 1, 1);
			pMatrix1->Set(-1.5, 1, 2);

			FastMatrix* pMatrix2 = new FastMatrix(3, 2);

			pMatrix2->Set(0, 0, 0);
			pMatrix2->Set(1, 0, 1);
			pMatrix2->Set(2, 1, 0);
			pMatrix2->Set(3, 1, 1);
			pMatrix2->Set(4, 2, 0);
			pMatrix2->Set(5, 2, 1);

			FastMatrix* productMatrix = FastMatrix::Multiply(pMatrix1, pMatrix2);

			Assert::AreEqual(0.0F * 0.0F + 0.5F * 2.0F + 1.0F * 4.0F, productMatrix->Get(0, 0));
			Assert::AreEqual(0.0F * 1.0F + 0.5F * 3.0F + 1.0F * 5.0F, productMatrix->Get(0, 1));
			Assert::AreEqual(1.5F * 0.0F + -1.0F * 2.0F + -1.5F * 4.0F, productMatrix->Get(1, 0));
			Assert::AreEqual(1.5F * 1.0F + -1.0F * 3.0F + -1.5F * 5.0F, productMatrix->Get(1, 1));

			delete(pMatrix1);
			delete(pMatrix2);
			delete(productMatrix);
		}

		TEST_METHOD(Multiply_Update)
		{
			FastMatrix* pMatrix1 = new FastMatrix(2, 3);

			pMatrix1->Set(0.0, 0, 0);
			pMatrix1->Set(0.5, 0, 1);
			pMatrix1->Set(1, 0, 2);
			pMatrix1->Set(1.5, 1, 0);
			pMatrix1->Set(-1, 1, 1);
			pMatrix1->Set(-1.5, 1, 2);

			FastMatrix* pMatrix2 = new FastMatrix(3, 2);

			pMatrix2->Set(0, 0, 0);
			pMatrix2->Set(1, 0, 1);
			pMatrix2->Set(2, 1, 0);
			pMatrix2->Set(3, 1, 1);
			pMatrix2->Set(4, 2, 0);
			pMatrix2->Set(5, 2, 1);

			FastMatrix* productMatrix = new FastMatrix(2, 2);

			FastMatrix::MultiplyUpdate(productMatrix, pMatrix1, pMatrix2);

			Assert::AreEqual(0.0F * 0.0F + 0.5F * 2.0F + 1.0F * 4.0F, productMatrix->Get(0, 0));
			Assert::AreEqual(0.0F * 1.0F + 0.5F * 3.0F + 1.0F * 5.0F, productMatrix->Get(0, 1));
			Assert::AreEqual(1.5F * 0.0F + -1.0F * 2.0F + -1.5F * 4.0F, productMatrix->Get(1, 0));
			Assert::AreEqual(1.5F * 1.0F + -1.0F * 3.0F + -1.5F * 5.0F, productMatrix->Get(1, 1));

			delete(pMatrix1);
			delete(pMatrix2);
			delete(productMatrix);
		}

		TEST_METHOD(Subtract_Update)
		{
			FastMatrix* pMatrix1 = new FastMatrix(2, 3);

			pMatrix1->Set(0.0, 0, 0);
			pMatrix1->Set(0.5, 0, 1);
			pMatrix1->Set(1, 0, 2);
			pMatrix1->Set(1.5, 1, 0);
			pMatrix1->Set(-1, 1, 1);
			pMatrix1->Set(-1.5, 1, 2);

			FastMatrix* pMatrix2 = new FastMatrix(2, 3);

			pMatrix2->Set(0, 0, 0);
			pMatrix2->Set(1, 0, 1);
			pMatrix2->Set(2, 0, 2);
			pMatrix2->Set(3, 1, 0);
			pMatrix2->Set(4, 1, 1);
			pMatrix2->Set(5, 1, 2);

			pMatrix1->SubtractUpdate(pMatrix2);

			Assert::AreEqual(0.0F - 0.0F, pMatrix1->Get(0, 0));
			Assert::AreEqual(0.5F - 1.0F, pMatrix1->Get(0, 1));
			Assert::AreEqual(1.0F - 2.0F, pMatrix1->Get(0, 2));
			Assert::AreEqual(1.5F - 3.0F, pMatrix1->Get(1, 0));
			Assert::AreEqual(-1.0F - 4.0F, pMatrix1->Get(1, 1));
			Assert::AreEqual(-1.5F - 5.0F, pMatrix1->Get(1, 2));

			delete(pMatrix1);
			delete(pMatrix2);
		}

		// Equation: Y = X^2 - 1
		// Note: Small errors are intentionally included in X.
		TEST_METHOD(GradientDescent_2nd_Order_Polynomial)
		{
			FastMatrix* pXMatrix = new FastMatrix(5, 1);

			pXMatrix->Set(-0.2, 0, 0);
			pXMatrix->Set(1.1, 1, 0);
			pXMatrix->Set(1.8, 2, 0);
			pXMatrix->Set(3.3, 3, 0);
			pXMatrix->Set(4.2, 4, 0);

			FastMatrix* pYMatrix = new FastMatrix(5, 1);

			pYMatrix->Set(-1, 0, 0);
			pYMatrix->Set(0, 1, 0);
			pYMatrix->Set(3, 2, 0);
			pYMatrix->Set(8, 3, 0);
			pYMatrix->Set(15, 4, 0);

			FastMatrix* pModifiedXMatrix = FastMatrix::AddSquaredColumns(pXMatrix);

			FastMatrix* pModifiedXMatrix2 = FastMatrix::AddOnesColumn(pModifiedXMatrix);

			FastMatrix* pThetaMatrix = FastMatrix::DescendGradient(pModifiedXMatrix2, pYMatrix, 0.001, 1000);

			FastMatrix* pRowMatrix = new FastMatrix(1, 3);

			float featureValue = 5;

			pRowMatrix->Set(1, 0, 0);
			pRowMatrix->Set(featureValue, 0, 1);
			pRowMatrix->Set(featureValue * featureValue, 0, 2);

			float prediction = pThetaMatrix->ComputePrediction(pRowMatrix);

			Assert::AreEqual(featureValue * featureValue, prediction, 0.2F * (featureValue * featureValue - 1));

			delete(pXMatrix);
			delete(pYMatrix);
			delete(pThetaMatrix);
			delete(pRowMatrix);
			delete(pModifiedXMatrix);
			delete(pModifiedXMatrix2);
		}

		// Equation: Y = 2 + 3.X1 + 4.X2
		// Note: Small errors are intentionally included in X and Y.
		TEST_METHOD(GradientDescent__Straight_Line__Multivariable)
		{
			FastMatrix* pXMatrix = new FastMatrix(9, 2);

			pXMatrix->Set(0.2, 0, 0);
			pXMatrix->Set(0, 1, 0);
			pXMatrix->Set(-0.03, 2, 0);
			pXMatrix->Set(1, 3, 0);
			pXMatrix->Set(2, 4, 0);
			pXMatrix->Set(2.9, 5, 0);
			pXMatrix->Set(1, 6, 0);
			pXMatrix->Set(2, 7, 0);
			pXMatrix->Set(3.3, 8, 0);

			pXMatrix->Set(0, 0, 1);
			pXMatrix->Set(1, 1, 1);
			pXMatrix->Set(2, 2, 1);
			pXMatrix->Set(0.1, 3, 1);
			pXMatrix->Set(-0.2, 4, 1);
			pXMatrix->Set(0, 5, 1);
			pXMatrix->Set(1, 6, 1);
			pXMatrix->Set(2, 7, 1);
			pXMatrix->Set(3.5, 8, 1);

			FastMatrix* pYMatrix = new FastMatrix(9, 1);

			pYMatrix->Set(2, 0, 0);
			pYMatrix->Set(6, 1, 0);
			pYMatrix->Set(10.1, 2, 0);
			pYMatrix->Set(5, 3, 0);
			pYMatrix->Set(8, 4, 0);
			pYMatrix->Set(10, 5, 0);
			pYMatrix->Set(9, 6, 0);
			pYMatrix->Set(16, 7, 0);
			pYMatrix->Set(23, 8, 0);

			FastMatrix* pModifiedXMatrix = FastMatrix::AddOnesColumn(pXMatrix);

			FastMatrix* pThetaMatrix = FastMatrix::DescendGradient(pModifiedXMatrix, pYMatrix, 0.001, 1000);

			FastMatrix* pRowMatrix = new FastMatrix(1, 3);

			pRowMatrix->Set(1, 0, 0);
			pRowMatrix->Set(5, 0, 1);
			pRowMatrix->Set(6, 0, 2);

			float prediction = pThetaMatrix->ComputePrediction(pRowMatrix);

			Assert::AreEqual(41, prediction, 0.2F * 41);

			delete(pXMatrix);
			delete(pYMatrix);
			delete(pThetaMatrix);
			delete(pRowMatrix);
			delete(pModifiedXMatrix);
		}
	};
};
