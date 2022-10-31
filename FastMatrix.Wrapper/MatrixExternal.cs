using System.Runtime.InteropServices;

namespace FastMatrix.Wrapper
{
    public partial class Matrix
    {

        [DllImport("FastMatrix.Library.dll")]
        public static extern int FastMatrix_GetRowCount(IntPtr fastMMatrix);
        [DllImport("FastMatrix.Library.dll")]
        public static extern int FastMatrix_GetColumnCount(IntPtr fastMMatrix);

        [DllImport("FastMatrix.Library.dll")]
        public static extern IntPtr FastMatrix_Create(int rowCount, int columnCount);

        [DllImport("FastMatrix.Library.dll")]
        public static extern float FastMatrix_Get(IntPtr fastMMatrix, int rowIndex, int columnIndex);

        [DllImport("FastMatrix.Library.dll")]
        public static extern void FastMatrix_Set(IntPtr fastMMatrix, float value, int rowIndex, int columnIndex);

        [DllImport("FastMatrix.Library.dll")]
        public static extern IntPtr FastMatrix_AddSquaredColumns(IntPtr fastMatrix);
        [DllImport("FastMatrix.Library.dll")]
        public static extern IntPtr FastMatrix_AddOnesColumn(IntPtr fastMatrix);

        [DllImport("FastMatrix.Library.dll")]
        public static extern IntPtr FastMatrix_ComplexConjugateTransform(IntPtr fastMatrix);

        [DllImport("FastMatrix.Library.dll")]
        public static extern IntPtr FastMatrix_ScalarMultiply(float scalar, IntPtr fastMatrix);

        [DllImport("FastMatrix.Library.dll")]
        public static extern IntPtr FastMatrix_Multiply(IntPtr fastMMatrix1, IntPtr fastMatrix2);

        [DllImport("FastMatrix.Library.dll")]
        public static extern IntPtr FastMatrix_DescendGradient(IntPtr XFastMatrix, IntPtr YFastMatrix, float alpha, int numIterations);

        [DllImport("FastMatrix.Library.dll")]
        public static extern void FastMatrix_ZeroValues(IntPtr fastMatrix);

        [DllImport("FastMatrix.Library.dll")]
        public static extern IntPtr FastMatrix_Add(IntPtr fastMMatrix1, IntPtr fastMatrix2);

        [DllImport("FastMatrix.Library.dll")]
        public static extern IntPtr FastMatrix_Subtract(IntPtr fastMMatrix1, IntPtr fastMatrix2);

        [DllImport("FastMatrix.Library.dll")]
        public static extern float FastMatrix_ComputePrediction(IntPtr thetaFastMatrix, IntPtr XFastMatrix);

        [DllImport("FastMatrix.Library.dll")]
        public static extern void FastMatrix_Delete(IntPtr fastMatrix);
    }
}
