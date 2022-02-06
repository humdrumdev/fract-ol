#include <math.h>
#include <stdio.h>

#define N 20

double	factorial(double n)
{
	double	f;
	double	i;

	if (n < 2)
		return (1);
	f = 1.0;
	i = 1.0;
	while (i++ < n)
		f *= i;
	return (f);
}

double	cosine(double x)
{
	unsigned int	i;
	double			c;
	double			sign;

	i = 0;
	c = 0.0;
	sign = 1.0;
	while (i < N)
	{
		c += (sign / factorial(i + i)) * pow(x, i + i);
		sign = -sign;
		i++;
	}
	return (c);
}

int	main()
{
	printf("%.15f\n", cosine (3.14/2));
	printf("%.15f\n", cos(3.14/2));
	return (0);
}