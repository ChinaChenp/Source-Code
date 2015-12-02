#include <stdio.h>
#include <string.h>

int str_move_char_to_head(char *str, char move_char)
{
	int len = strlen(str);
	char *fast = str + len - 1;
	char *slow = fast;
	char temp;

	while(len--)
	{
		if(*slow != move_char)
		{
			slow--;
			fast = slow;
			continue;
		}
		if(*fast == move_char)
		{
			fast--;
			continue;
		}
		
		{
			temp = *fast;
			*fast-- = *slow;
			*slow-- = temp;
		}
	}
}

int main(int argc, char *argv[])
{
	printf("%s----->", argv[1]);
	str_move_char_to_head(argv[1], '*');
	printf("%s\n", argv[1]);
}

