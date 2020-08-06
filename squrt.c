#include <stdio.h>

double		ft_squrt(int nb, int p)
{
	int 	left;
	int 	right;
	float 	mid;
	float 	res;

	right = nb;
	left = 0;
	while (left <= right)
	{
		mid = (left + right) / 2;
		if (mid * mid == nb || mid * mid < nb)
		{
			res = mid;
			if (mid * mid == nb)
				break; 
			else
				left = mid + 1;
		}
		else
			right = mid - 1;
	}
	left = 0;
	mid = 0.1;
	while (left++ < p)
	{
		while (res * res <= nb)
			res += mid;
		res -= mid;
		mid /= 10;
	}
	return (res);
}

int main(void)
{
	double x;

	x = ft_squrt(50, 3);
	printf("%f\n", x);
}
