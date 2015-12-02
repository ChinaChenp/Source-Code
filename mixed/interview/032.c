#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
** 最长支持的字符串大小
*/
#define MAX_SIZE 64

/*
** 解法就是用一个矩阵来记录两个字符串中所有位置的两个字符之间的
** 匹配情况,若是匹配则为1,否则为0,然后求出对角线最长的1序列,其
** 对应的位置就是最长匹配子串的位置.
*/
char *str_max_match(const char *s1, const char *s2)
{
	if(!s1 || !s2)
		return 0;

	int l1 = strlen(s1);
	int l2 = strlen(s2);

	int M[MAX_SIZE][MAX_SIZE] = {0};
	int i = 0, j = 0, max_len = 0, end = 0;
	for(i=0; i<l1; ++i)
	{
		for(j=0; j<l2; ++j)
		{
			if(s1[i] == s2[j])
			{
				if(i == 0 || j == 0)
					M[i][j] = 1;
				else
					M[i][j] = M[i-1][j-1] + 1;
			}

			/*record the max len*/
			if(M[i][j] > max_len)
			{
				max_len = M[i][j];
				end = i;
			}
		}
	}
	int start = end - max_len + 1;

#if 0
	char *re = calloc(1, max_len + 1);
	for(i=start; i<=end; ++i)
		re[i-start] = s1[i];
#else
	char *re = strndup(s1 + start, max_len);
#endif
	return re;
}

int main(int argc, char *argv[])
{
	char *re = str_max_match(argv[1], argv[2]);
	printf("%s---->%s<-----%s\n", argv[1], re, argv[2]);
	free(re);
	return 0;
}
