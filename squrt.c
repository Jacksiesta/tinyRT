#include <stdio.h>

double		ft_squrt(int nb, int p)
{
	int 	left;
	int 	right;
	int 	mid;
	float 	res;
	float 	incr;

	right = nb;
	while (left <= right)
	{
		mid = (left + right) / 2;
		if (mid * mid == nb)
		{
			res = mid;
			break; 
		}
		if (mid * mid < nb)
		{
			left = mid + 1;
			res = mid;
		}
		else
			right = mid - 1;
	}
	left = 0;
	incr = 0.1;
	while (left++ < p)
	{
		while (res * res <= nb)
			res += incr;
		res -= incr;
		incr /= 10;
	}
	return (res);
}

int main(void)
{
	double x;

	x = ft_squrt(50, 3);
	printf("%f\n", x);
}
