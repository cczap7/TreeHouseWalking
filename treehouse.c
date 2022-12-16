/* Corban Czap
 * Tree House Walking
 * 02/10/2022
 */



#include <stdio.h>
#include <stdlib.h>
#include <math.h> // including math.h library for the sqrt function

// declaring function prototypes
int checkPairs(int* pairing, int n);
void calculateDistance(int** trees, int n, int* pairing, float* minimumDistance);
void solve(int** trees, int* pairing, int n, float* minimumDistance);

// driver function
int main()
{
    // reading in the number of test cases the user wants
    int test_cases;
    scanf("%d", &test_cases);
    
    // looping until test cases == 0
    while(test_cases>0)
    {
        // declaring and assigning minimumDistance the size of
        // 1000000000
        float minimumDistance=1e9;
        // repsenting how many pairs of trees there are in the
        // backyard
        int n;
        scanf("%d", &n);
        
        // dynamically allocating arrays the size of 2n
        int** trees=(int**)malloc(sizeof(int*)*2*n);
        int* pairing=(int*)malloc(sizeof(int)*2*n);
        
        // looping 2n times for pairs of trees
        for (int i=0; i<2*n; i++)
        {
            pairing[i]=-1;
            // assigning user entered pair of coordinates to the ith row
            // and first and second columns of DMA array trees
            trees[i]=malloc(sizeof(int)*2);
            scanf("%d%d", &trees[i][0], &trees[i][1]);
        }
        
        // decrementing test cases for the loop
        test_cases--;
        
        // calling solve function with the values entered to trees,
        // the DMA array pairing, the number of pairs(n),
        // and the minimumDistance (1e9)
        solve(trees, pairing, n, &minimumDistance);
        
        // printing out the minimum sum of distances possible
        // rounding float output to exactly 3 decimal places
        printf("%0.3f\n", minimumDistance);
    }
    // signifying end of main function
    return 0;
}

int checkPairs(int* pairing, int n)
{
    int i=0;
    for (i=0; i<2*n; i++)
    {
        if (pairing[i]==-1)
        {
            return i;
        }
    }
    
    return i;
}

// actually calculates the minimum sum of rop ladder distances
// using the square root equation given to us
void calculateDistance(int** trees, int n, int* pairing, float* minimumDistance)
{
    float distance=0;
    // looping 2n times for the pairs of trees
    for (int i=0; i<2*n; i++)
    {
        // equation to find distance between two points
        distance+=sqrt((float)(trees[i][0]-trees[pairing[i]][0])*(trees[i][0]-trees[pairing[i]][0])+(trees[i][1]-trees[pairing[i]][1])*(trees[i][1]-trees[pairing[i]][1]));
    }
    distance = distance/(float)2;
    
    // if minimumDistance is greater than the distance calculated
    // assign minimumDistance the value of distance
    if (*minimumDistance>distance)
    {
        *minimumDistance=distance;
    }
}

// determines the min sum of rope ladder distances
// by calling the checkpairs and calculate distance functions
void solve(int** trees, int* pairing, int n, float* minimumDistance)
{
    int i=checkPairs(pairing, n);
    
    if (i>=2*n)
    {
        calculateDistance(trees, n, pairing, minimumDistance);
        return;
    }
    
    for (int j=0; j<2*n; j++)
    {
        if (j!=i && pairing[j]==-1)
        {
            pairing[i]=j;
            pairing[j]=i;
            solve(trees, pairing, n, minimumDistance);
            pairing[i]=-1;
            pairing[j]=-1;
        }
    }
}
