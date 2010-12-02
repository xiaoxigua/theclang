#include <stdio.h>
#include <string.h>

#define EXIT_FAILURE 1

static char *program_name;

/* allocate memory, die on error */
void *xmalloc(size_t n)
{
	void *p = malloc(n);

	if(p == NULL)
	{
		fprintf(stderr, "%s: out of memory\n", program_name);
		exit(EXIT_FAILURE);
	}
	return p;
}

/* reallocate memory, die on error */
void *xrealloc(void *p, size_t n)
{
	void *s;
	
	if(n == 0)
	{
		if(p != NULL)
			free(p);
		return NULL;
	}
	if(p == NULL)
		return xmalloc(n);
	s = realloc(p, n);
	if(s == NULL)
	{
		fprintf(stderr, "%s: out of memory\n", program_name);
		exit(EXIT_FAILURE);
	}
	return s;
}

int main(int argc, char **agrv)
{
	printf("argc = %d\n", argc);
	char *allocked_argvs = xmalloc(10000);
	//char **new_argv = xmalloc((argc + 1) * sizeof(char *));
	printf("allocked_argvs string: %s\n", allocked_argvs);
	printf("allocked_argvs string length: %d\n", strlen(allocked_argvs));
	printf("allocked_argvs[0] address: %d\n", &allocked_argvs[0]);
	printf("allocked_argvs[1] address: %d\n", &allocked_argvs[1]);
	printf("allocked_argvs[2] address: %d\n", &allocked_argvs[2]);
	printf("allocked_argvs[0] value: %d\n", allocked_argvs[0]);
	printf("allocked_argvs[1] value: %d\n", allocked_argvs[1]);
	printf("allocked_argvs[2] value: %d\n", allocked_argvs[2]);
}
