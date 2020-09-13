#include <string.h>

int main(void)
{
	char *str = "abcd";
	char *dst = "abwc";

	printf("%d\n", strncmp(str, dst, 3));
}