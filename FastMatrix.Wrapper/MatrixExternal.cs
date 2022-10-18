using System.Runtime.InteropServices;

namespace FastMatrix.Wrapper
{
    public partial class Matrix
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
        public static extern IntPtr FastMatrix_Add(IntPtr matrix1, IntPtr matrix2);

        [DllImport("FastMatrix.Library.dll")]
        public static extern IntPtr FastMatrix_Subtract(IntPtr matrix1, IntPtr matrix2);

        [DllImport("FastMatrix.Library.dll")]
        public static extern float FastMatrix_ComputePrediction(IntPtr theta, IntPtr x);

        [DllImport("FastMatrix.Library.dll")]
        public static extern void FastMatrix_Delete(IntPtr matrix);
    }
}
