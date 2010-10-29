/**
 * Write an alternative version of squeeze(s1, s2) that
 * deletes each character in s1 that matches any character
 * in the string s2.
 *
 */

/* squeeze2: delete all characters occurring in s2 from string s1. */

void squeeze2(char s1[], char s2[])
{
	int i, j, k;
	int instr2 = 0;

	for(i = j = 0; s1[i] != '\0'; i++)
	{
		instr2 = 0;
		for(k = 0; s2[k] != '\0' && !instr2; k++)
		{
			if(s2[k] == s1[i])
			{
				instr2 = 1;
			}
		}

		if(!instr2)
		{
			s1[j++] = s1[i];
		}
		s1[j] = '\0';
	}
}
