#include <stdio.h>

int main() {
	char *source = "#include <stdio.h> %c%cint main() { %c%cchar *source = %c%s%c; %c%cprintf(source,10,10,10, 9,34,source,34,10,9,10,9,10,10);%c%creturn 0; %c}%c";
	printf(source,10,10,10, 9,34,source,34,10,9,10,9,10,10);
	return 0;
}
