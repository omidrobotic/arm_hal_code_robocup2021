#include "speedcalc.h"


signed short c[ 5 ] = {0};

#define aRowSize 4
#define aColumnSize 3

#define bRowSize 3
#define bColumnSize 1

// Taabe e zarbe 2 matrix
void multiplyMatrix( float a[aRowSize][aColumnSize], float b[bRowSize][bColumnSize], float constant )
{
  int i, j, k;
  if ( aColumnSize == bRowSize )
  {
    // Mohasebeye matrixe c
    for ( i = 0; i < aRowSize; ++i )
    {
      for ( j = 0; j < bColumnSize; ++j )
      {
        c[ i ] = 0;
        for ( k = 0; k < aColumnSize; ++k ) // ya bRowSize
          c[ i ] += constant * a[ i ][ k ] * b[ k ][ j ];
      }
    }
  }
}

double degreeToRadian( int deg )
{
	return deg * 3.141592 / 180;
}

void wheels_velocity_calculate( int vvx, int vvy, float angularVelocity, float rteta ) // 0
{
//	double start_time = std::chrono::
	float modified_coeficient = 1;
	float R = 90;
	
	float bb0 = degreeToRadian( 300 );
	float bb1 = degreeToRadian( 225 );
	float bb2 = degreeToRadian( 135 );
	float bb3 = degreeToRadian( 60 );
	
	float b[ bRowSize ][ bColumnSize ] = {
		vvx / 64.5,
		vvy / 64.5,
		angularVelocity,
	};

	for (int k = 0; k < 2; k++)
	{
		float a[ aRowSize ][ aColumnSize ] = {
			sin( rteta + bb0 ), -cos( rteta + bb0 ), -R,
			sin( rteta + bb1 ), -cos( rteta + bb1 ), -R,
			sin( rteta + bb2 ), -cos( rteta + bb2 ), -R,
			sin( rteta + bb3 ), -cos( rteta + bb3 ), -R,
		};
		
		multiplyMatrix( a, b, modified_coeficient );
		
		double limit_v = 30;
		double swap_v;
		swap_v = limit_v;
		
		for (int i = 0; i < 4; i++)
		{
			if ( fabs( c[ i ] ) > limit_v && fabs( c[ i ] ) > swap_v )
			{
				swap_v = fabs( c[ i ] );
			}
		}
		modified_coeficient = limit_v / swap_v;
	}
	
	for (int m = 0; m < 4; m++)
	{
		c[ m ] = floor( ceil( 2 * c[ m ] ) / 2 );
		send_data_arm_to_fpga[ m] = c[m];
	}
}
