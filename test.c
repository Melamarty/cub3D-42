#include <libc.h>
#include <math.h>
int main()
{
	printf("%lf\n", tan(179 * M_PI / 180));
	// printf("%lf\n", (3 * M_PI / 2 + (M_PI / 3)) * 180 / M_PI);
	// printf("%lf\n", fmod(((19 * M_PI / 2) * 180 / M_PI),  (2 * M_PI) * 180 / M_PI));
}