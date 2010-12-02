#include <stdio.h>
#include <string.h>

/* macros */
#define NO_ARG 0
#define REQUIRED_ARG 1
#define OPTIONAL_ARG 2

/* types */

/* GETOPT_LONG_OPTION_T: the type of long option */
typedef struct GETOPT_LONG_OPTION_T
{
	char *name; /* the name of the long option */
	int has_arg; /* one of the above macros */
	int *flag; /** determines if getopt_long() returns a
				 * value for a long option; if it is
				 * non-NULL, 0 is returned as a function
				 * value and the value of val is stored in
				 * the area pointed to by flag. Otherwise,
				 * val is returned. */
	int val; /* determines the value to return if flag is NULL */
} GETOPT_LONG_OPTION_T;

typedef enum GETOPT_ORDERING_T
{
	PERMUTE,
	RETURN_IN_ORDER,
	REQUIRE_ORDER
} GETOPT_ORDERING_T;

/* globally-defined variables */
char *optarg = NULL;
int optind = 0;
int opterr = 1;
int optopt = '?';

/* statically-defined variables */
static char *program_name;
/* if nonzero, it means tab every x characters */

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

void parse_args(int argc, char **argv)
{
	int opt;

	do
	{
		switch((opt = getopt_long(argc, argv, shortopts, longopts, NULL)))
		{
			case 'i': /* initial */
				flag_initial = 1;
				break;
			case 't': /* tab stops */
				handle_tab_stops(optarg);
				break;
			case '?': /* invalid option */
				fprintf(stderr, "For help, type:\n\t%s --help\n", program_name);
				exit(EXIT_FAILURE);
			case 1:
			case 0:
				if(show_help || show_version)
				{
					if(show_help)
						help();
					if(show_version)
						version();
					exit(EXIT_SUCCESS);
				}
				break;
			default:
				break;
		}
	} while(opt != EOF)
}

int main(int argc, char **argv)
{
	int i;
	FILE *fp;
	char *allocked_argvs = xmalloc(argc + 1);
	char **new_argv = xmalloc((argc + 1) * sizeof(char *));
	char *p;

	program_name = argv[0];
	memset(allocked_argvs, 0, argc + 1); /** set all elements of
										   * allocked_argvs to be
										   * 0. */
										   
	for(i = 0; i < argc; i++) 
	{
		p = argv[i];
		if(isdigit(p[1])) 
		{
			new_argv[i] = xmalloc(strlen(p) + 2);
			sprintf(new_argv[i], "-t%s", p + 1);
			allocked_argvs[i] = 1;
		} else
		{
			new_argv[i] = p;
		}
	}
	new_argv[argc] = NULL;
	parse_args(argc, new_argv);
	if(optind == argc)
		tab(stdin);
	else
	{
		for(i = optind; i < argc; i++)
		{
			if(strcmp(argv[i], "-") == 0)
				fp = stdin;
			else
			{
				fp = fopen(argv[i], "r");
				if(fp == NULL)
				{
					fprintf(stderr, "%s: can't open %s\n", argv[0], argv[i]);
					abort();
				}
			}
			tab(fp);
			if(fp != stdin)
				fclose(fp);
		}
	}
	/* free everything we can */
	for(i = 0; i < argc; i++)
	{
		if(allocked_argvs[i])
			free(new_argv[i]);
	}
	free(allocked_argvs);
	if(tab_stop_list != NULL)
		free(tab_stop_list);
	return EXIT_SUCCESS;
}

/* END OF FILE entab.c */
