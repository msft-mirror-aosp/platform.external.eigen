// g++ -O3 -DNDEBUG -DMATSIZE=<x> benchmark.cpp -o benchmark && time ./benchmark
#include <Eigen/Array>

#ifndef MATSIZE
#define MATSIZE 3
#endif

using namespace std;
USING_PART_OF_NAMESPACE_EIGEN

#ifndef REPEAT
#define REPEAT 40000000
#endif

#ifndef SCALAR
#define SCALAR double
#endif

int main(int argc, char *argv[])
{
    Matrix<SCALAR,MATSIZE,MATSIZE> I = Matrix<SCALAR,MATSIZE,MATSIZE>::ones();
    Matrix<SCALAR,MATSIZE,MATSIZE> m;
    for(int i = 0; i < MATSIZE; i++)
        for(int j = 0; j < MATSIZE; j++)
        {
            m(i,j) = (i+MATSIZE*j);
        }
    asm("#begin");
    for(int a = 0; a < REPEAT; a++)
    {
        m = Matrix<SCALAR,MATSIZE,MATSIZE>::ones() + 0.00005 * (m + (m*m));
    }
    asm("#end");
    cout << m << endl;
    return 0;
}
