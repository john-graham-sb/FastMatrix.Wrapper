namespace FastMatrix.Wrapper
{
    public partial class Matrix : IDisposable
    {
        private IntPtr _pCMatrix;

        public Matrix(int rowCount, int columnCount)
        {
            _pCMatrix = FastMatrix_Create(rowCount, columnCount);
        }

        private Matrix(IntPtr _pMatrix)
        {
            this._pCMatrix = _pMatrix;
        }

        public float this[int rowIndex, int columnIndex]
        {
            get => FastMatrix_Get(_pCMatrix, rowIndex, columnIndex);
            set => FastMatrix_Set(_pCMatrix, value, rowIndex, columnIndex);
        }

        public static Matrix operator *(Matrix matrix1, Matrix matrix2)
        {
            IntPtr pProductMatrix = FastMatrix_Multiply(matrix1._pCMatrix, matrix2._pCMatrix);

            return new Matrix(pProductMatrix);
        }

        public static Matrix operator *(float scalar, Matrix matrix2)
        {
            IntPtr pProductMatrix = FastMatrix_ScalarMultiply(scalar, matrix2._pCMatrix);

            return new Matrix(pProductMatrix);
        }

        public static Matrix operator /(Matrix matrix2, float inverseScalar)
        {
            IntPtr pQuotientMatrix = FastMatrix_ScalarMultiply(1 / inverseScalar, matrix2._pCMatrix);

            return new Matrix(pQuotientMatrix);
        }

        public static Matrix operator +(Matrix matrix1, Matrix matrix2)
        {
            IntPtr pSumMatrix = FastMatrix_Add(matrix1._pCMatrix, matrix2._pCMatrix);

            return new Matrix(pSumMatrix);
        }

        public static Matrix operator -(Matrix matrix1, Matrix matrix2)
        {
            IntPtr pDifferenceMatrix = FastMatrix_Subtract(matrix1._pCMatrix, matrix2._pCMatrix);

            return new Matrix(pDifferenceMatrix);
        }

        public static Matrix DescendGradient(Matrix X, Matrix y, float alpha, int numIterations)
        {
            IntPtr pThetaMatrix = FastMatrix_DescendGradient(X._pCMatrix, y._pCMatrix, alpha, numIterations);
            
            return new Matrix(pThetaMatrix);
        }

        public float ComputePrediction(Matrix x)
        {
            return FastMatrix_ComputePrediction(this._pCMatrix, x._pCMatrix);
        }

        public Matrix ComplexConjugateTranspose()
        {
            IntPtr pCMatrix = FastMatrix_ComplexConjugateTransform(this._pCMatrix);

            return new Matrix(pCMatrix);
        }

        public void Dispose()
        {
            FastMatrix_Delete(_pCMatrix);
        }
    }
}