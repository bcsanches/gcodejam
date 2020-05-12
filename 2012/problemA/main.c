#include <stdio.h>

char archTable_g[] = 
{
	'y', //ok
	'h', //ok
	'e', //ok
	's', //ok
	'o', //ok
	'c', //ok
	'v', //ok
	'x', //ok
	'd', //ok
	'u', //ok
	'i', //ok
	'g', //ok
	'l', //ok
	'b', //ok
	'k', //ok
	'r', //ok
	'z',
	't', //ok
	'n', //ok
	'w', //ok
	'j', //ok
	'p', //ok
	'f', //ok
	'm', //ok
	'a', //ok
	'q'	 //ok
};

/*
char archTable_g[] = 
{
	'a',
	'b',
	'c',
	'd',
	'e',
	'f',
	'g',
	'h',
	'i',
	'j',
	'k',
	'l',
	'm',
	'n',
	'o',
	'p',
	'q',
	'r',
	's,
	't',
	'u',
	'v',
	'w',
	'x',
	'y',
	'z'	
}
*/

int main(int argc, char **argv)
{
	int numEntries;
	char entry[101];
	char output[101];
	int i, j;

	scanf("%d\n", &numEntries);	

	for(i = 0;i < numEntries; ++i)
	{				
		gets(entry);

		for(j = 0;entry[j]; ++j)
		{			
			output[j] = entry[j] == ' ' ? ' ' : archTable_g[entry[j] - 'a'];
		}
		output[j]=0;

		printf("Case #%d: %s\n", i+1, output);		
	}

	return 0;
}
