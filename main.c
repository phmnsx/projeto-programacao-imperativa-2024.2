#include <stdio.h>

int main(int argc, char** argv)
{
	if (argc < 2) printf("oi mundo\n");
	else printf("oi %s", argv[1]);
	return 0;
}
