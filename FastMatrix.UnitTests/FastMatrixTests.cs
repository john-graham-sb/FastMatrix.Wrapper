using NUnit.Framework.Internal;
using System.Runtime.InteropServices;

namespace FastMatrix.UnitTests
{
    [TestClass]
    public class FastMatrixTests
    {
        [DllImport("FastMatrix.Library.dll")]
        public static extern IntPtr FastMatrix_Create(int rowCount, int columnCount);

        [DllImport("FastMatrix.Library.dll")]
        public static extern float FastMatrix_Get(IntPtr matrix, int rowIndex, int columnIndex);

        [DllImport("FastMatrix.Library.dll")]
        public static extern void FastMatrix_Set(IntPtr matrix, float value, int rowIndex, int columnIndex);

        [DllImport("FastMatrix.Library.dll")]
        public static extern IntPtr FastMatrix_ComplexConjugateTransform(IntPtr matrix);

        [DllImport("FastMatrix.Library.dll")]
        public static extern IntPtr FastMatrix_ScalarMultiply(float scalar, IntPtr matrix2);

        [DllImport("FastMatrix.Library.dll")]
        public static extern IntPtr FastMatrix_Multiply(IntPtr matrix1, IntPtr matrix2);

        [DllImport("FastMatrix.Library.dll")]
        public static extern IntPtr FastMatrix_DescendGradient(IntPtr X, IntPtr y, float alpha, int numIterations);

        [DllImport("FastMatrix.Library.dll")]
        public static extern void FastMatrix_ZeroValues(IntPtr matrix);

        [DllImport("FastMatrix.Library.dll")]
        public static extern float FastMatrix_ComputePrediction(IntPtr theta, IntPtr x);

        [DllImport("FastMatrix.Library.dll")]
        public static extern void FastMatrix_Delete(IntPtr matrix);

        [TestMethod]
        public void FastMatrixShouldSetAndGetValues()
        {
            IntPtr matrix = FastMatrix_Create(3, 2);
            FastMatrix_Set(matrix, 1F, 0, 0);
            FastMatrix_Set(matrix, 2F, 1, 0);
            FastMatrix_Set(matrix, 3F, 2, 0);
            FastMatrix_Set(matrix, 4F, 0, 1);
            FastMatrix_Set(matrix, 5F, 1, 1);
            FastMatrix_Set(matrix, 6F, 2, 1);

            float one = FastMatrix_Get(matrix, 0, 0);
            float two = FastMatrix_Get(matrix, 1, 0);
            float three = FastMatrix_Get(matrix, 2, 0);
            float four = FastMatrix_Get(matrix, 0, 1);
            float five = FastMatrix_Get(matrix, 1, 1);
            float six = FastMatrix_Get(matrix, 2, 1);

            Assert.AreEqual(1, one);
            Assert.AreEqual(2, two);
            Assert.AreEqual(3, three);
            Assert.AreEqual(4, four);
            Assert.AreEqual(5, five);
            Assert.AreEqual(6, six);

            FastMatrix_Delete(matrix);
        }

        [TestMethod]
        public void FastMatrixShouldMultiplyTwoMatrices()
        {
            IntPtr matrix1 = FastMatrix_Create(3, 2);
            FastMatrix_Set(matrix1, 1F, 0, 0);
            FastMatrix_Set(matrix1, 2F, 1, 0);
            FastMatrix_Set(matrix1, 3F, 2, 0);
            FastMatrix_Set(matrix1, 4F, 0, 1);
            FastMatrix_Set(matrix1, 5F, 1, 1);
            FastMatrix_Set(matrix1, 6F, 2, 1);

            IntPtr matrix2 = FastMatrix_Create(2, 1);
            FastMatrix_Set(matrix2, 1F, 0, 0);
            FastMatrix_Set(matrix2, 2F, 1, 0);

            IntPtr productMatrix = FastMatrix_Multiply(matrix1, matrix2);

            float nine = FastMatrix_Get(productMatrix, 0, 0);
            float twelve = FastMatrix_Get(productMatrix, 1, 0);
            float fifteen = FastMatrix_Get(productMatrix, 2, 0);

            Assert.AreEqual(9, nine);
            Assert.AreEqual(12, twelve);
            Assert.AreEqual(15, fifteen);

            FastMatrix_Delete(matrix1);
            FastMatrix_Delete(matrix2);
            FastMatrix_Delete(productMatrix);
        }

        [TestMethod]
        public void FastMatrixShouldScalarMultiply()
        {
            IntPtr matrix = FastMatrix_Create(3, 2);
            FastMatrix_Set(matrix, 1F, 0, 0);
            FastMatrix_Set(matrix, 2F, 1, 0);
            FastMatrix_Set(matrix, 3F, 2, 0);
            FastMatrix_Set(matrix, 4F, 0, 1);
            FastMatrix_Set(matrix, 5F, 1, 1);
            FastMatrix_Set(matrix, 6F, 2, 1);

            float scalar = 2;

            IntPtr scaledMatrix = FastMatrix_ScalarMultiply(scalar, matrix);

            float two = FastMatrix_Get(scaledMatrix, 0, 0);
            float four = FastMatrix_Get(scaledMatrix, 1, 0);
            float six = FastMatrix_Get(scaledMatrix, 2, 0);
            float eight = FastMatrix_Get(scaledMatrix, 0, 1);
            float ten = FastMatrix_Get(scaledMatrix, 1, 1);
            float twelve = FastMatrix_Get(scaledMatrix, 2, 1);

            Assert.AreEqual(2, two);
            Assert.AreEqual(4, four);
            Assert.AreEqual(6, six);
            Assert.AreEqual(8, eight);
            Assert.AreEqual(10, ten);
            Assert.AreEqual(12, twelve);

            FastMatrix_Delete(matrix);
            FastMatrix_Delete(scaledMatrix);
        }

        [TestMethod]
        public void FastMatrixShouldTransform()
        {
            IntPtr matrix = FastMatrix_Create(3, 2);
            FastMatrix_Set(matrix, 1F, 0, 0);
            FastMatrix_Set(matrix, 2F, 1, 0);
            FastMatrix_Set(matrix, 3F, 2, 0);
            FastMatrix_Set(matrix, 4F, 0, 1);
            FastMatrix_Set(matrix, 5F, 1, 1);
            FastMatrix_Set(matrix, 6F, 2, 1);

            IntPtr transformedMatrix = FastMatrix_ComplexConjugateTransform(matrix);

            float one = FastMatrix_Get(transformedMatrix, 0, 0);
            float two = FastMatrix_Get(transformedMatrix, 0, 1);
            float three = FastMatrix_Get(transformedMatrix, 0, 2);
            float four = FastMatrix_Get(transformedMatrix, 1, 0);
            float five = FastMatrix_Get(transformedMatrix, 1, 1);
            float six = FastMatrix_Get(transformedMatrix, 1, 2);

            Assert.AreEqual(1, one);
            Assert.AreEqual(2, two);
            Assert.AreEqual(3, three);
            Assert.AreEqual(4, four);
            Assert.AreEqual(5, five);
            Assert.AreEqual(6, six);

            FastMatrix_Delete(matrix);
            FastMatrix_Delete(transformedMatrix);
        }

        [TestMethod]
        public void FastMatrixShouldZeroAllValues()
        {
            IntPtr X = FastMatrix_Create(3, 2);
            FastMatrix_Set(X, 1F, 0, 0);
            FastMatrix_Set(X, 2F, 1, 0);
            FastMatrix_Set(X, 3F, 2, 0);
            FastMatrix_Set(X, 4F, 0, 1);
            FastMatrix_Set(X, 5F, 1, 1);
            FastMatrix_Set(X, 6F, 2, 1);

            FastMatrix_ZeroValues(X);

            float one = FastMatrix_Get(X, 0, 0);
            float two = FastMatrix_Get(X, 1, 0);
            float three = FastMatrix_Get(X, 2, 0);
            float four = FastMatrix_Get(X, 0, 1);
            float five = FastMatrix_Get(X, 1, 1);
            float six = FastMatrix_Get(X, 2, 1);

            Assert.AreEqual(0, one);
            Assert.AreEqual(0, two);
            Assert.AreEqual(0, three);
            Assert.AreEqual(0, four);
            Assert.AreEqual(0, five);
            Assert.AreEqual(0, six);

            FastMatrix_Delete(X);
        }

        [TestMethod]
        public void FastMatrixShouldDescendGradient()
        {
            IntPtr X = FastMatrix_Create(3, 2);
            FastMatrix_Set(X, 1F, 0, 0);
            FastMatrix_Set(X, 2F, 1, 0);
            FastMatrix_Set(X, 3F, 2, 0);
            FastMatrix_Set(X, 1F, 0, 1);
            FastMatrix_Set(X, 1F, 1, 1);
            FastMatrix_Set(X, 1F, 2, 1);

            IntPtr y = FastMatrix_Create(3, 1);
            FastMatrix_Set(y, 1F, 0, 0);
            FastMatrix_Set(y, 2F, 1, 0);
            FastMatrix_Set(y, 3F, 2, 0);

            IntPtr theta = FastMatrix_DescendGradient(X, y, 0.01F, 999999);

            float one = FastMatrix_Get(theta, 0, 0);
            float two = FastMatrix_Get(theta, 1, 0);

            Assert.AreEqual(1, one, 0.1);
            Assert.AreEqual(0, two, 0.1);

            FastMatrix_Delete(X);
            FastMatrix_Delete(y);
            FastMatrix_Delete(theta);
        }

        [TestMethod]
        public void FastMatrixShouldComputePrediction()
        {
            IntPtr theta = FastMatrix_Create(1, 2);
            FastMatrix_Set(theta, 1F, 0, 0);
            FastMatrix_Set(theta, 0F, 1, 0);

            IntPtr testXValues = FastMatrix_Create(2, 1);
            FastMatrix_Set(testXValues, 5F, 0, 0);
            FastMatrix_Set(testXValues, 1F, 1, 0);

            float prediction = FastMatrix_ComputePrediction(theta, testXValues);

            Assert.AreEqual(5, prediction);

            FastMatrix_Delete(theta);
            FastMatrix_Delete(testXValues);
        }
    }
}