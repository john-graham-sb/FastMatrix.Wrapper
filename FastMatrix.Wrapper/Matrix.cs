namespace FastMatrix.Wrapper
{
    public partial class Matrix : IDisposable
    {
        private readonly IntPtr fastMatrix;

        public int RowCount
        {
            get; private set;
        }
        public int ColumnCount
        {
            get; private set;
        }

        private Matrix()
        {
            throw new InvalidOperationException($"Instantiation requires dimensions.");
        }

        public Matrix(int rowCount, int columnCount)
        {
            this.fastMatrix = FastMatrix_Create(rowCount, columnCount);

            this.RowCount = rowCount;
            this.ColumnCount = columnCount;
        }

        private Matrix(IntPtr fastMatrix)
        {
            this.fastMatrix = fastMatrix;

            this.RowCount = FastMatrix_GetRowCount(fastMatrix);
            this.ColumnCount = FastMatrix_GetColumnCount(fastMatrix);
        }

        public static bool TryCreateFromCSVFile(out Matrix? XMatrix, out Matrix? YMatrix, string csvFilePath, int recordCount)
        {
            XMatrix = null;
            YMatrix = null;

            try
            {
                var lines = File.ReadAllLines(csvFilePath)
            .Select(a => a.Split(',')).Where(line => !line.Any(str => str == string.Empty)).Take(recordCount).ToList();

                int rowCount = lines.Count;
                int columnCount = lines.First().Length - 1;

                XMatrix = new Matrix(rowCount, columnCount);
                YMatrix = new Matrix(rowCount, 1);

                int rowIndex = 0;
                foreach (var line in lines)
                {
                    int columnIndex = 0;
                    foreach (var lineElement in line.Take(columnCount))
                    {
                        XMatrix[rowIndex, columnIndex] = float.Parse(lineElement);

                        columnIndex++;
                    }

                    var finalLineElement = line.Skip(columnCount).Take(1).First();

                    YMatrix[rowIndex, 0] = float.Parse(finalLineElement);

                    rowIndex++;
                }
            }
            catch (Exception)
            {
                return false;
            }

            return true;
        }

        public float this[int rowIndex, int columnIndex]
        {
            get => FastMatrix_Get(this.fastMatrix, rowIndex, columnIndex);
            set => FastMatrix_Set(this.fastMatrix, value, rowIndex, columnIndex);
        }

        public static Matrix operator *(Matrix matrix1, Matrix matrix2)
        {
            IntPtr fastMatrix = FastMatrix_Multiply(matrix1.fastMatrix, matrix2.fastMatrix);

            return new Matrix(fastMatrix);
        }

        public static Matrix operator *(float scalar, Matrix matrix2)
        {
            IntPtr fastMatrix = FastMatrix_ScalarMultiply(scalar, matrix2.fastMatrix);

            return new Matrix(fastMatrix);
        }

        public static Matrix operator /(Matrix matrix2, float inverseScalar)
        {
            IntPtr fastMatrix = FastMatrix_ScalarMultiply(1 / inverseScalar, matrix2.fastMatrix);

            return new Matrix(fastMatrix);
        }

        public static Matrix operator +(Matrix matrix1, Matrix matrix2)
        {
            IntPtr fastMatrix = FastMatrix_Add(matrix1.fastMatrix, matrix2.fastMatrix);

            return new Matrix(fastMatrix);
        }

        public static Matrix operator -(Matrix matrix1, Matrix matrix2)
        {
            IntPtr fastMatrix = FastMatrix_Subtract(matrix1.fastMatrix, matrix2.fastMatrix);

            return new Matrix(fastMatrix);
        }

        public static Matrix DescendGradient(Matrix XMatrix, Matrix YMatrix, float alpha, int numIterations)
        {
            IntPtr fastMatrix = FastMatrix_DescendGradient(XMatrix.fastMatrix, YMatrix.fastMatrix, alpha, numIterations);

            return new Matrix(fastMatrix);
        }

        public static Matrix DescendGradientOptimized(Matrix XMatrix, Matrix YMatrix, float alpha, int numIterations)
        {
            IntPtr fastMatrix = FastMatrix_DescendGradient_Optimized(XMatrix.fastMatrix, YMatrix.fastMatrix, alpha, numIterations);

            return new Matrix(fastMatrix);
        }

        public float ComputePrediction(Matrix XRowMatrix)
        {
            float prediction = FastMatrix_ComputePrediction(this.fastMatrix, XRowMatrix.fastMatrix);

            return prediction;
        }

        public Matrix ComplexConjugateTranspose()
        {
            IntPtr fastMatrix = FastMatrix_ComplexConjugateTransform(this.fastMatrix);

            return new Matrix(fastMatrix);
        }

        public static Matrix AddOnesColumn(Matrix matrix)
        {
            IntPtr fastMatrix = FastMatrix_AddOnesColumn(matrix.fastMatrix);

            return new Matrix(fastMatrix);
        }

        public static Matrix AddSquaredColumns(Matrix matrix)
        {
            IntPtr fastMatrix = FastMatrix_AddSquaredColumns(matrix.fastMatrix);

            return new Matrix(fastMatrix);
        }

        public void Dispose()
        {
            FastMatrix_Delete(this.fastMatrix);
        }
    }
}