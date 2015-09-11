// Two input matrice: A(m*4) and B(n*4), represents two groups of line segments with their start and end points.
// for example, A = [x1, y1, x2, y2] as a single line segment input
// Output: OUT(m*n), gives the distance between the midpoints of line segments in A row m and B row n

#include <math.h>
#include "mex.h"
#include <stdio.h>
#include <stdlib.h>

#define IS_REAL_2D_FULL_DOUBLE(P) (!mxIsComplex(P) && mxGetNumberOfDimensions(P) == 2 && !mxIsSparse(P) && mxIsDouble(P))

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	// Macros for the output and input arguments
	#define ANS_OUT   plhs[0]
	#define A_IN    prhs[0]
	#define B_IN    prhs[1]
	double *OUT, *B, *A;
	int m=0, n=0, MA=0, NA=0, MB=0, NB=0;

	if (nrhs<1 || nrhs >2) // check the number of arguments
	{
		mexErrMsgTxt("Wrong number of input arguments.");
	}
	else if (nlhs > 1)
	{
		mexErrMsgTxt("Too many output arguments.");
	}

	if (!IS_REAL_2D_FULL_DOUBLE(A_IN)) //check A
	{
		mexErrMsgTxt("A must be a real 2D full double array.");
	}

	if (!IS_REAL_2D_FULL_DOUBLE(B_IN)) //check B
	{
		mexErrMsgTxt("A must be a real 2D full double array.");
	}

	MA = mxGetM(A_IN);
	NA = mxGetN(A_IN);
	MB = mxGetM(B_IN);
	NB = mxGetN(B_IN);
	A = mxGetPr(A_IN);
	B = mxGetPr(B_IN);
	ANS_OUT = mxCreateDoubleMatrix(MA, MB, mxREAL);
	OUT = mxGetPr(ANS_OUT);
	double *ptr_MidA, *ptr_MidB;
	ptr_MidA = (double*)mxCalloc((MA*2+10), sizeof(double));
	ptr_MidB = (double*)mxCalloc((MB*2+10), sizeof(double));

	for (int i = 0; i< MA; i++)
	{
		//assume NA,NB = 4
		ptr_MidA[i] = (A[i] + A[i+2*MA])/2;
		ptr_MidA[i+MA] = (A[i+MA] + A[i+3*MA])/2;

	}

	for (int i = 0; i< MB; i++)
	{
		//assume NA,NB = 4
		ptr_MidB[i] = (B[i] + B[i+2*MB])/2;
		ptr_MidB[i+MB] = (B[i+MB] + B[i+3*MB])/2;

	}

	double delX=0, delY=0,dist=0;

	for (int i = 0; i<MA; i++)
	{
		for (int j = 0; j<MB; j++)
		{
			delX = pow((ptr_MidA[i]-ptr_MidB[j]),2);
			delY = pow((ptr_MidA[i+MA]-ptr_MidB[j+MB]),2);
			dist = sqrt(delX + delY);
			OUT[i+j*MA] = dist;
		}
	}
	mxFree(ptr_MidA);
	mxFree(ptr_MidB);

}



