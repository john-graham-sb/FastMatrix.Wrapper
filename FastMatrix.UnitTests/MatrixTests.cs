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
            matrix[1, 0] = 2;
            matrix[2, 0] = 3;
            matrix[0, 1] = 4;
            matrix[1, 1] = 5;
            matrix[2, 1] = 6;

            float one = matrix[0, 0];
            float two = matrix[1, 0];
            float three = matrix[2, 0];
            float four = matrix[0, 1];
            float five = matrix[1, 1];
            float six = matrix[2, 1];

            Assert.AreEqual(one, 1);
            Assert.AreEqual(two, 2);
            Assert.AreEqual(three, 3);
            Assert.AreEqual(four, 4);
            Assert.AreEqual(five, 5);
            Assert.AreEqual(six, 6);
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

            float nine = productMatrix[0, 0];
            float twelve = productMatrix[1, 0];
            float fifteen = productMatrix[2, 0];

            Assert.AreEqual(nine, 9);
            Assert.AreEqual(twelve, 12);
            Assert.AreEqual(fifteen, 15);
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

            float two = productMatrix[0, 0];
            float four = productMatrix[1, 0];
            float six = productMatrix[2, 0];

            Assert.AreEqual(two, 2);
            Assert.AreEqual(four, 4);
            Assert.AreEqual(six, 6);
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

            float one = productMatrix[0, 0];
            float two = productMatrix[1, 0];
            float three = productMatrix[2, 0];

            Assert.AreEqual(one, 1);
            Assert.AreEqual(two, 2);
            Assert.AreEqual(three, 3);
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

            using Matrix sumnMatrix = matrix1 + matrix2;

            float eight = sumnMatrix[0, 0];
            float ten = sumnMatrix[1, 0];
            float twelve = sumnMatrix[2, 0];
            float fourteen = sumnMatrix[0, 1];
            float sixteen = sumnMatrix[1, 1];
            float eighteen = sumnMatrix[2, 1];

            Assert.AreEqual(eight, 8);
            Assert.AreEqual(ten, 10);
            Assert.AreEqual(twelve, 12);
            Assert.AreEqual(fourteen, 14);
            Assert.AreEqual(sixteen, 16);
            Assert.AreEqual(eighteen, 18);
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

            float one = differenceMatrix[0, 0];
            float two = differenceMatrix[1, 0];
            float three = differenceMatrix[2, 0];
            float four = differenceMatrix[0, 1];
            float five = differenceMatrix[1, 1];
            float six = differenceMatrix[2, 1];

            Assert.AreEqual(one, 1);
            Assert.AreEqual(two, 2);
            Assert.AreEqual(three, 3);
            Assert.AreEqual(four, 4);
            Assert.AreEqual(five, 5);
            Assert.AreEqual(six, 6);
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

            using Matrix newX1 = new(1, 2);

            newX1[0, 0] = 1;
            newX1[1, 0] = 5;

            float prediction1 = theta.ComputePrediction(newX1);

            Assert.AreEqual(prediction1, 5, 0.1);

            using Matrix newX2 = new(1, 2);

            newX2[0, 0] = 1;
            newX2[1, 0] = 10;

            float prediction2 = theta.ComputePrediction(newX2);

            Assert.AreEqual(prediction2, 10, 0.1);
        }

        [TestMethod]
        public void MatrixShouldTranform()
        {
            using Matrix X = new(20, 2);

            X[0, 0] = 1;
            X[1, 0] = 2;
            X[2, 0] = 3;
            X[3, 0] = 4;
            X[4, 0] = 5;
            X[5, 0] = 6;
            X[6, 0] = 7;
            X[7, 0] = 8;
            X[8, 0] = 9;
            X[9, 0] = 10;
            X[10, 0] = 11;
            X[11, 0] = 12;
            X[12, 0] = 13;
            X[13, 0] = 14;
            X[14, 0] = 15;
            X[15, 0] = 16;
            X[16, 0] = 17;
            X[17, 0] = 18;
            X[18, 0] = 19;
            X[19, 0] = 20;
            X[0, 1] = 1;
            X[1, 1] = 1;
            X[2, 1] = 1;
            X[3, 1] = 1;
            X[4, 1] = 1;
            X[5, 1] = 1;
            X[6, 1] = 1;
            X[7, 1] = 1;
            X[8, 1] = 1;
            X[9, 1] = 1;
            X[10, 1] = 1;
            X[11, 1] = 1;
            X[12, 1] = 1;
            X[13, 1] = 1;
            X[14, 1] = 1;
            X[15, 1] = 1;
            X[16, 1] = 1;
            X[17, 1] = 1;
            X[18, 1] = 1;
            X[19, 1] = 1;

            using Matrix xTransformed = X.ComplexConjugateTranspose();

            float val1 = xTransformed[0, 0];
            float val2 = xTransformed[0, 1];
            float val3 = xTransformed[0, 2];
            float val4 = xTransformed[0, 3];
            float val5 = xTransformed[0, 4];
            float val6 = xTransformed[0, 5];
            float val7 = xTransformed[0, 6];
            float val8 = xTransformed[0, 7];
            float val9 = xTransformed[0, 8];
            float val10 = xTransformed[0, 9];
            float val11 = xTransformed[0, 10];
            float val12 = xTransformed[0, 11];
            float val13 = xTransformed[0, 12];
            float val14 = xTransformed[0, 13];
            float val15 = xTransformed[0, 14];
            float val16 = xTransformed[0, 15];
            float val17 = xTransformed[0, 16];
            float val18 = xTransformed[0, 17];
            float val19 = xTransformed[0, 18];
            float val20 = xTransformed[0, 19];
            float val21 = xTransformed[1, 0];
            float val22 = xTransformed[1, 1];
            float val23 = xTransformed[1, 2];
            float val24 = xTransformed[1, 3];
            float val25 = xTransformed[1, 4];
            float val26 = xTransformed[1, 5];
            float val27 = xTransformed[1, 6];
            float val28 = xTransformed[1, 7];
            float val29 = xTransformed[1, 8];
            float val30 = xTransformed[1, 9];
            float val31 = xTransformed[1, 10];
            float val32 = xTransformed[1, 11];
            float val33 = xTransformed[1, 12];
            float val34 = xTransformed[1, 13];
            float val35 = xTransformed[1, 14];
            float val36 = xTransformed[1, 15];
            float val37 = xTransformed[1, 16];
            float val38 = xTransformed[1, 17];
            float val39 = xTransformed[1, 18];
            float val40 = xTransformed[1, 19];

            Assert.AreEqual(1, val1, 0.1);
            Assert.AreEqual(2, val2, 0.1);
            Assert.AreEqual(3, val3, 0.1);
            Assert.AreEqual(4, val4, 0.1);
            Assert.AreEqual(5, val5, 0.1);
            Assert.AreEqual(6, val6, 0.1);
            Assert.AreEqual(7, val7, 0.1);
            Assert.AreEqual(8, val8, 0.1);
            Assert.AreEqual(9, val9, 0.1);
            Assert.AreEqual(10, val10, 0.1);
            Assert.AreEqual(11, val11, 0.1);
            Assert.AreEqual(12, val12, 0.1);
            Assert.AreEqual(13, val13, 0.1);
            Assert.AreEqual(14, val14, 0.1);
            Assert.AreEqual(15, val15, 0.1);
            Assert.AreEqual(16, val16, 0.1);
            Assert.AreEqual(17, val17, 0.1);
            Assert.AreEqual(18, val18, 0.1);
            Assert.AreEqual(19, val19, 0.1);
            Assert.AreEqual(20, val20, 0.1);
            Assert.AreEqual(1, val21, 0.1);
            Assert.AreEqual(1, val22, 0.1);
            Assert.AreEqual(1, val21, 0.1);
            Assert.AreEqual(1, val22, 0.1);
            Assert.AreEqual(1, val23, 0.1);
            Assert.AreEqual(1, val24, 0.1);
            Assert.AreEqual(1, val25, 0.1);
            Assert.AreEqual(1, val26, 0.1);
            Assert.AreEqual(1, val27, 0.1);
            Assert.AreEqual(1, val28, 0.1);
            Assert.AreEqual(1, val29, 0.1);
            Assert.AreEqual(1, val30, 0.1);
            Assert.AreEqual(1, val31, 0.1);
            Assert.AreEqual(1, val32, 0.1);
            Assert.AreEqual(1, val33, 0.1);
            Assert.AreEqual(1, val34, 0.1);
            Assert.AreEqual(1, val35, 0.1);
            Assert.AreEqual(1, val36, 0.1);
            Assert.AreEqual(1, val37, 0.1);
            Assert.AreEqual(1, val39, 0.1);
            Assert.AreEqual(1, val39, 0.1);
            Assert.AreEqual(1, val40, 0.1);
        }
    }
}
