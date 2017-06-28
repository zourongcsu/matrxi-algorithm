/**************************************************************************************
*   1、该代码主要利用高斯约当列主消元法求取矩阵的逆运算
*   2、高斯约当列主消元法的主要步骤如下：
        a.求取系数矩阵的曾广矩阵（在系数矩阵右端增加一个n*n的单位矩阵I）
        b.求取每一列中的绝对值对的元素，记录该主元所在的列；
        c.将主元所在的行与对应的行（搜索主元元素所在的列对应的行）进行互换位置
        d.将主元所在的行进行单位化，把对角线上的元素化为1
        e.利用列主消元，把对应列的其他元素化为0
***************************************************************************************
    example:求矩阵[1 1 -1;1 2 -2;-2 1 1]的逆矩阵

    step1:求曾广矩阵如下：

            [  1  1 -1  |  1  0  0
               1  2 -2  |  0  1  0
              -2  1  1  |  0  0  1]

    step2:求第一列的主元，绝对值最大为2，在第三列，故将第三列与第一列互换，得到：

            [ -2  1  1  |  0  0  1
               1  2 -2  |  0  1  0
               1  1 -1  |  1  0  0]

    step3:对主元所在的列进行单位化，得到：

            [  1  -0.5  -0.5  |  0  0  -0.5
               1     2    -2  |  0  1     0
               1     1    -1  |  1  0     0]

    step4:利用列主消元，把对应列的其他元素化为0，得到：

            [  1  -0.5  -0.5  |  0  0  -0.5
               0   2.5  -1.5  |  0  1   0.5
               0   1.5  -0.5  |  1  0   0.5]

    step5:然后对第二列、第三列重复上述操作，得到最终的逆矩阵为：
             [ 1  0  0  |    2    -1    0
               0  1  0  |  1.5  -0.5  0.5
               0  0  1  |  2.5  -1.5  0.5]

***************************************************************************************/
#include<iostream>
#include<math.h>
#define N 4
void matrix_inverse(float (*a)[N],float (*b)[N]);
int main()
{
    using namespace std;
    cout<<"please input "<< N <<"*"<< N <<" matrix:\n";
    int i,j;
    float a[N][N];
    float b[N][N] = {0};
    for(i=0;i<N;i++)
    {
        cout<<"please input the number of "<<(i+1)<<" row:";
        for(j=0;j<N;j++)
        {
            cin>>a[i][j];
        }
    }

    cout<<"the input matrix is :\n";
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            cout<<a[i][j]<<"\t";
        }
        cout<<"\n";
    }
    matrix_inverse(a,b);
    cout<<"the inverse matrix is :\n";
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            cout<<" "<<b[i][j]<<"\t";
        }
        cout<<"\n";
    }
    return 0;
}
void matrix_inverse(float (*a)[N],float (*b)[N])
{
    using namespace std;
    int i,j,k;
    float max,temp;
    // 定义一个临时矩阵t
    float t[N][N];
    // 将a矩阵临时存放在矩阵t[n][n]中
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            t[i][j] = a[i][j];
        }
    }
    // 初始化B矩阵为单位矩阵
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            b[i][j] = (i == j)?(float)1:0;
        }
    }
    // 进行列主消元，找到每一列的主元
    for(i=0;i<N;i++)
    {
        max = t[i][i];
        // 用于记录每一列中的第几个元素为主元
        k = i;
        // 寻找每一列中的主元元素
        for(j=i+1;j<N;j++)
        {
            if(fabsf(t[j][i]) > fabsf(max))
            {
                max = t[j][i];
                k = j;
            }
        }
        //cout<<"the max number is "<<max<<endl;
        // 如果主元所在的行不是第i行，则进行行交换
        if(k != i)
        {
            // 进行行交换
            for(j=0;j<N;j++)
            {
                temp = t[i][j];
                t[i][j] = t[k][j];
                t[k][j] = temp;
                // 伴随矩阵B也要进行行交换
                temp = b[i][j];
                b[i][j] = b[k][j];
                b[k][j] = temp;
            }
        }
        if(t[i][i] == 0)
        {
            cout<<"\nthe matrix does not exist inverse matrix\n";
            break;
        }
        // 获取列主元素
        temp = t[i][i];
        // 将主元所在的行进行单位化处理
        //cout<<"\nthe temp is "<<temp<<endl;
        for(j=0;j<N;j++)
        {
            t[i][j] = t[i][j]/temp;
            b[i][j] = b[i][j]/temp;
        }
        for(j=0;j<N;j++)
        {
            if(j != i)
            {
                temp = t[j][i];
                //消去该列的其他元素
                for(k=0;k<N;k++)
                {
                    t[j][k] = t[j][k] - temp*t[i][k];
                    b[j][k] = b[j][k] - temp*b[i][k];
                }
            }

        }

    }
}
