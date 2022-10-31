using FastMatrix.Wrapper;

if (Matrix.CreateFromCSVFile(out Matrix X, out Matrix y, @"C:\Users\Sarah Sim\Source\Repos\FastMatrix.Wrapper\FastMatrix.UnitTests\Test Data\imageQuality.csv", 2000))
{
    Console.WriteLine("Created Matrix from CSV file...");

    using Matrix augmentedX1 = Matrix.AddSquaredColumns(X);

    float v1 = augmentedX1[0, 0];
    float v2 = augmentedX1[0, 1];
    float v3 = augmentedX1[0, 2];
    float v4 = augmentedX1[0, 3];
    float v5 = augmentedX1[0, 4];

    Console.WriteLine("Augmented X...");

    using Matrix theta = new(5, 1);

    using Matrix theta2 = Matrix.DescendGradient(augmentedX1, y, 0.00000000000000000001F, 50000);

    float v6 = theta2[0, 0];
    float v7 = theta2[0, 1];
    float v8 = theta2[0, 2];
    float v9 = theta2[0, 3];
    float v10 = theta2[0, 4];

    Console.WriteLine("Descended gradient...");

    using (Matrix newX1 = new(1, 5))
    {
        newX1[0, 0] = 4378;
        newX1[0, 1] = 1900;
        newX1[0, 2] = 4378 * 4378;
        newX1[0, 3] = 4378 * 1900;
        newX1[0, 4] = 1900 * 1900;

        float prediction1 = theta2.ComputePrediction(newX1);

        Console.WriteLine($"Prediction 1 = {prediction1}");
    }

    using (Matrix newX2 = new(1, 5))
    {
        newX2[0, 0] = 2397;
        newX2[0, 1] = 1711;
        newX2[0, 2] = 2397 * 2397;
        newX2[0, 3] = 2397 * 1711;
        newX2[0, 4] = 1711 * 1711;

        float prediction2 = theta2.ComputePrediction(newX2);

        Console.WriteLine($"Prediction 2 = {prediction2}");
    }
}