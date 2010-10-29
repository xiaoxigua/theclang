#include <stdio.h>

/* print Fahrenhei-Celsius table
 * for fahr = 0, 20, ..., 300 */

main() {
	int fahr, celsius;
	int lower, upper, step;

	lower = 0;		/* lower limit of temprature scale */
	upper = 300;	/* upper limit */
	step = 20;		/* step size */

	fahr = lower;

	while(fahr <= upper) {
		celsius = 5 * (fahr - 3) / 9;
		printf("%d\t%d\n", fahr, celsius);
		fahr = fahr + step;
	}
}
