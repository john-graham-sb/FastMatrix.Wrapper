using FastMatrix.Wrapper;
using NUnit.Framework.Internal;

namespace FastMatrix.UnitTests
{
    [TestClass]
    public class MatrixTests
    {
        [TestMethod]
        public void MatrixShouldSetAndGetValues()
        {
            using Matrix matrix = new(3, 2);
            matrix[0, 0] = 1;
            matrix[1, 0] = 2.00F;
            matrix[2, 0] = -3;
            matrix[0, 1] = -4.05F;
            matrix[1, 1] = 5.005F;
            matrix[2, 1] = 0.000000005F;

            Assert.AreEqual(3, matrix.RowCount);
            Assert.AreEqual(2, matrix.ColumnCount);

            Assert.AreEqual(1, matrix[0, 0]);
            Assert.AreEqual(2.00F, matrix[1, 0]);
            Assert.AreEqual(-3, matrix[2, 0]);
            Assert.AreEqual(-4.05F, matrix[0, 1]);
            Assert.AreEqual(5.005F, matrix[1, 1]);
            Assert.AreEqual(0.000000005F, matrix[2, 1]);
        }

        [TestMethod]
        public void MatrixShouldMultiply()
        {
            using Matrix matrix1 = new(3, 2);
            matrix1[0, 0] = 1;
            matrix1[1, 0] = 2;
            matrix1[2, 0] = 3;
            matrix1[0, 1] = 4;
            matrix1[1, 1] = 5;
            matrix1[2, 1] = 6;

            using Matrix matrix2 = new(2, 1);
            matrix2[0, 0] = 1;
            matrix2[1, 0] = 2;

            using Matrix productMatrix = matrix1 * matrix2;

            Assert.AreEqual(9, productMatrix[0, 0]);
            Assert.AreEqual(12, productMatrix[1, 0]);
            Assert.AreEqual(15, productMatrix[2, 0]);
        }

        [TestMethod]
        public void MatrixShouldScalarMultiply()
        {
            using Matrix matrix = new(3, 1);
            matrix[0, 0] = 1;
            matrix[1, 0] = 2;
            matrix[2, 0] = 3;

            float scalar = 2;

            using Matrix productMatrix = scalar * matrix;

            Assert.AreEqual(2, productMatrix[0, 0]);
            Assert.AreEqual(4, productMatrix[1, 0]);
            Assert.AreEqual(6, productMatrix[2, 0]);
        }

        [TestMethod]
        public void MatrixShouldScalarDivide()
        {
            using Matrix matrix = new(3, 1);
            matrix[0, 0] = 2;
            matrix[1, 0] = 4;
            matrix[2, 0] = 6;

            float scalar = 2;

            using Matrix productMatrix = matrix / scalar;

            Assert.AreEqual(1, productMatrix[0, 0]);
            Assert.AreEqual(2, productMatrix[1, 0]);
            Assert.AreEqual(3, productMatrix[2, 0]);
        }

        [TestMethod]
        public void MatrixShouldAdd()
        {
            using Matrix matrix1 = new(3, 2);
            matrix1[0, 0] = 1;
            matrix1[1, 0] = 2;
            matrix1[2, 0] = 3;
            matrix1[0, 1] = 4;
            matrix1[1, 1] = 5;
            matrix1[2, 1] = 6;

            using Matrix matrix2 = new(3, 2);
            matrix2[0, 0] = 7;
            matrix2[1, 0] = 8;
            matrix2[2, 0] = 9;
            matrix2[0, 1] = 10;
            matrix2[1, 1] = 11;
            matrix2[2, 1] = 12;

            using Matrix sumMatrix = matrix1 + matrix2;

            Assert.AreEqual(8, sumMatrix[0, 0]);
            Assert.AreEqual(10, sumMatrix[1, 0]);
            Assert.AreEqual(12, sumMatrix[2, 0]);
            Assert.AreEqual(14, sumMatrix[0, 1]);
            Assert.AreEqual(16, sumMatrix[1, 1]);
            Assert.AreEqual(18, sumMatrix[2, 1]);
        }

        [TestMethod]
        public void MatrixShouldSubtract()
        {
            using Matrix matrix1 = new(3, 2);
            matrix1[0, 0] = 8;
            matrix1[1, 0] = 10;
            matrix1[2, 0] = 12;
            matrix1[0, 1] = 14;
            matrix1[1, 1] = 16;
            matrix1[2, 1] = 18;

            using Matrix matrix2 = new(3, 2);
            matrix2[0, 0] = 7;
            matrix2[1, 0] = 8;
            matrix2[2, 0] = 9;
            matrix2[0, 1] = 10;
            matrix2[1, 1] = 11;
            matrix2[2, 1] = 12;

            using Matrix differenceMatrix = matrix1 - matrix2;

            Assert.AreEqual(1, differenceMatrix[0, 0]);
            Assert.AreEqual(2, differenceMatrix[1, 0]);
            Assert.AreEqual(3, differenceMatrix[2, 0]);
            Assert.AreEqual(4, differenceMatrix[0, 1]);
            Assert.AreEqual(5, differenceMatrix[1, 1]);
            Assert.AreEqual(6, differenceMatrix[2, 1]);
        }

        [TestMethod]
        public void MatrixShouldDescendGradient()
        {
            using Matrix X = new(3, 2);

            X[0, 0] = 1;
            X[1, 0] = 1;
            X[2, 0] = 1;
            X[0, 1] = 1;
            X[1, 1] = 2;
            X[2, 1] = 3;

            using Matrix y = new(3, 1);

            y[0, 0] = 1;
            y[1, 0] = 2;
            y[2, 0] = 3;

            using Matrix theta = Matrix.DescendGradient(X, y, 0.1F, 500);

            float thetaRowCount = theta.RowCount;
            float thetaColumnCount = theta.ColumnCount;

            Assert.AreEqual(2, theta.RowCount);
            Assert.AreEqual(1, theta.ColumnCount);

            float theta0 = theta[0, 0];
            float theta1 = theta[1, 0];

            Assert.AreEqual(0, theta[0, 0], 0.1);
            Assert.AreEqual(1, theta[1, 0], 0.1);
        }

        [TestMethod]
        public void MatrixShouldMakeCorrectPrediction1()
        {
            using Matrix theta = new(2, 1);
            theta[0, 0] = 0.0000007F;
            theta[1, 0] = 1F;

            using Matrix X = new(1, 2);
            X[0, 0] = 1;
            X[0, 1] = 5;

            float predictedY = theta.ComputePrediction(X);

            Assert.AreEqual(5, predictedY, 0.1);

        }

        [TestMethod]
        public void MatrixShouldMakeCorrectPrediction2()
        {
            using Matrix theta = new(2, 1);
            theta[0, 0] = 0.0000007F;
            theta[1, 0] = 1F;

            using Matrix X = new(1, 2);
            X[0, 0] = 1;
            X[0, 1] = 10;

            float predictedY = theta.ComputePrediction(X);

            Assert.AreEqual(10, predictedY, 0.1);
        }

        [TestMethod]
        public void MatrixShouldMakeCorrectPrediction3()
        {
            Assert.IsTrue(Matrix.TryCreateFromCSVFile(out Matrix? xMatrix, out Matrix? yMatrix, 
                $"C:\\Users\\Sarah Sim\\Source\\Repos\\FastMatrix.Wrapper\\FastMatrix.UnitTests\\Test Data\\imageQuality.csv", 5000),
                $"Failed to prepare matrices from CSV file.");

            using Matrix modifiedXMatrix1 = Matrix.AddSquaredColumns(xMatrix!);
            using Matrix modifiedXMatrix2 = Matrix.AddOnesColumn(modifiedXMatrix1);

            using Matrix theta = Matrix.DescendGradient(modifiedXMatrix2, yMatrix!, 
                0.00000000000000000000001F, 500);

            using Matrix newX = new (1, 2);
            newX[0, 0] = 371716F;
            newX[0, 1] = 398078F;

            using Matrix modifiednewX1 = Matrix.AddSquaredColumns(newX);
            using Matrix modifiednewX2 = Matrix.AddOnesColumn(modifiednewX1);

            float prediction = theta.ComputePrediction(modifiednewX2);

            Assert.IsTrue(prediction > -100 && prediction < 200);

            xMatrix!.Dispose();
            yMatrix!.Dispose();
        }
    }
}
