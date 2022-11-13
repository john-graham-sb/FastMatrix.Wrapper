using FastMatrix.Wrapper;

DateTime startTime1;
DateTime startTime2;
DateTime endTime1;
DateTime endTime2;

if (Matrix.TryCreateFromCSVFile(out Matrix xMatrix, out Matrix yMatrix,
    $"C:\\Users\\Sarah Sim\\Source\\Repos\\FastMatrix.Wrapper\\FastMatrix.UnitTests\\Test Data\\imageQuality.csv", 2500))
{

    using Matrix modifiedXMatrix1 = Matrix.AddSquaredColumns(xMatrix);
    using Matrix modifiedXMatrix2 = Matrix.AddOnesColumn(modifiedXMatrix1);

    startTime1 = DateTime.Now;

    using Matrix theta = Matrix.DescendGradient(modifiedXMatrix2, yMatrix,
        0.000000000000000000000001F, 5000);

    endTime1 = DateTime.Now;

    using Matrix newX = new Matrix(1, 2);
    newX[0, 0] = 371716F;
    newX[0, 1] = 398078F;

    using Matrix modifiednewX1 = Matrix.AddSquaredColumns(newX);
    using Matrix modifiednewX2 = Matrix.AddOnesColumn(modifiednewX1);

    TimeSpan timeSpan1 = endTime1 - startTime1;
    Console.WriteLine($"Time = {timeSpan1.ToString()}");

    float prediction = theta.ComputePrediction(modifiednewX2);
    Console.WriteLine($"Prediction = {prediction}");

    startTime2 = DateTime.Now;

    using Matrix theta2 = Matrix.DescendGradientOptimized(modifiedXMatrix2, yMatrix,
        0.000000000000000000000001F, 5000);

    endTime2 = DateTime.Now;

    TimeSpan timeSpan2 = endTime2 - startTime2;

    Console.WriteLine($"Time, Optimized = {timeSpan2.ToString()}");

    xMatrix.Dispose();
    yMatrix.Dispose();
}

