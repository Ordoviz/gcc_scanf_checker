#include <stdio.h>

int main() {
	char buf[100];
	int n = scanf("%s", buf);
	const char* s = "%11s";
	n = scanf(s, buf);
	if (n == 1)
		puts(buf);
}
