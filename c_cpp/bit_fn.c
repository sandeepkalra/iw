#include <stdio.h>
#include <stdlib.h>

/*----------------------
	Truth Table.
	------------

	 1 & 1 = 1
	 1 & 0 = 0
	 0 & 1 = 0
	 0 & 0 = 0

	 1 | 1 = 1
	 1 | 0 = 1
	 0 | 1 = 1
	 0 | 0 = 0

	 1 ^ 1 = 0
	 1 ^ 0 = 1  (flips when XOR with 1 , same when XOR with 0.)
	 0 ^ 1 = 1
	 0 ^ 0 = 0

	 ~0 = 1
	 ~1 = 0

 -------------------------*/


#define Set_K_th_Bit(n,k) 	(n | (0x01 << (k)) )
#define UnSet_K_th_Bit(n,k) 	(n & (0x01 << (k)) )
#define flip_k_th_Bit(n,k)      (n ^ (0x01 << (k)) )
#define is_kth_bit_Set(n,k)     ((n>>(k-1)) && 1 )


void PrintNumberInBinary(int n)
{
	char arr[32];
	int k = n;
	int i = 0 ;
	for(i=0; i< 32 ; ++i )
	{
		arr[31-i] = ((n && 0x01)?'1':'0');
		n = n>>1;
	}
	printf("%x in Binary is: ",k);
	for (i=0; i<32; ++i) printf("%c", arr[i]);
}

void ReverseBits(int n, int sz)
{
	int mid = sz/2;
	int i = 0;
	for( ;i < mid ; ++i )
	{
		// if the i-th and (sz-i)-th bits are different
		int bit_i = (n & (0x01<<i))?1:0;
		int bit_sz_minus_i = (n & (0x01<<(sz-i)))?1:0;
		if(bit_i ^ bit_sz_minus_i) {
			flip_k_th_Bit(n, i);
			flip_k_th_Bit(n, sz-i);
		}
	}
}
int main()
{
}

