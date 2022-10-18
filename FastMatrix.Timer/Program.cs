using FastMatrix.Wrapper;

Matrix X = new(20, 2);
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

Matrix y = new(20, 1);
y[0, 0] = 1;
y[1, 0] = 2;
y[2, 0] = 3;
y[3, 0] = 4;
y[4, 0] = 5;
y[5, 0] = 6;
y[6, 0] = 7;
y[7, 0] = 8;
y[8, 0] = 9;
y[9, 0] = 10;
y[10, 0] = 11;
y[11, 0] = 12;
y[12, 0] = 13;
y[13, 0] = 14;
y[14, 0] = 15;
y[15, 0] = 16;
y[16, 0] = 17;
y[17, 0] = 18;
y[18, 0] = 19;
y[19, 0] = 20;

int avgMilliseconds = 0;

for (int i = 0; i < 20; i++)
{
    var startTime = DateTime.Now;

    Matrix theta = Matrix.DescendGradient(X, y, 0.1F, 999999);

    var endTime = DateTime.Now;

    TimeSpan timeSpan = endTime - startTime;

    avgMilliseconds += timeSpan.Milliseconds;

    Console.WriteLine($" Accumulated Time Difference (ms) = {avgMilliseconds}");

    /*Matrix newX = new(3, 2);
    newX[0, 0] = 1;
    newX[1, 0] = 5;

    float prediction = theta.ComputePrediction(newX);*/
}

avgMilliseconds = avgMilliseconds / 10;

Console.WriteLine($" Average Time Difference (ms) = {avgMilliseconds}");
