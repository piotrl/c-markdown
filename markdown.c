#include "markdown.h"
#include "stack.h"
#include "config.h"

int isSingleton(char c, int len)
{
	int i;

	for(i = 0; i < len; i++)
	{
		if(c == singletons[i])
			return i;
	}
	return -1;
}

void onSingleton(int index)
{
    if(top() == singletons[index])
    {
        fprintf( output, "</%s>", conv[index] );
        pop();
    }
    else
    {
        fprintf( output, "<%s>", conv[index] );
        push(singletons[index]);
    }
}

int onURL()
{	// return 0 if it's ok;
	// not 0 if what's wrong

	int i = 0;
	char c,
		link_name[1000],	//999 is max length of link
		link_url[1000];

	/**
	 * Building name of link
	 * -------------------------------------------------------------- */
	c = fgetc(input);
	while( c != ']' && c != '\n' && c != EOF && i < 999 )
	{
		link_name[i++] = c;

		c = fgetc(input);
	}
	link_name[i] = '\0';	// close string

	if( c == '\n' || c == EOF )
	{	// there is something wrong in syntax
		fprintf(output, "[%s]", link_name );
		return 1;
	}

	/**
	 * Building URL of link
	 * -------------------------------------------------------------- */

	while( ( c = fgetc(input) ) == ' ' ) {}	// ommit white spaces
	if( c == '(' )
	{
		i = 0;
		c = fgetc(input);
		while( c != ')' && c != '\n')
		{
			link_url[i++] = c;
			c = fgetc(input);
		}
		link_url[i] = '\0';

		if(c == '\n')
		{
			fprintf(output, "[%s]", link_name );
			fprintf(output, "(%s\n", link_url);
			return 3;
		}
	}
	else
	{ // this isn't link at all
		fprintf(output, "[%s]", link_name );
		printf("%c", c);
		return 2;
	}

	/**
	 * Printing HTML link
	 * -------------------------------------------------------------- */

	fprintf(output, "<a href=\"%s\">%s</a>", link_url, link_name );
	return 0;
}

int onHeader()
{
	int i, countHash = 1;
	char c;

	while( ( c = fgetc(input) ) == '#' )
	{
		countHash++;
	}

	if( countHash > 6 )
	{
		for( i = 0; i < countHash; i++)
		{
			fprintf(output, "#");
		}
		fprintf(output, "%c", c);
		return 1;
	}

	fprintf(output, "<h%i>%c", countHash, c);

	c = fgetc(input);
	while( c != '\n' && c != EOF )
	{
		fprintf(output, "%c", c);
		c = fgetc(input);
	}

	fprintf(output, "</h%i>\n", countHash);
	return 0;
}

int onHR()
{
	int countDash = 1,
		i;
	char c;

	c = fgetc(input);
	while( c != '\n' && c == '-' )
	{
		countDash++;
		c = fgetc(input);
	}

	if( countDash > 10 )
	{
		fprintf(output, "\n<hr />\n");
	} else
	{
		for( i = 0; i < countDash; i++ )
		{
			fprintf(output, "-");
		}
		fprintf(output, "%c", c);
		return 1;
	}
	return 0;
}

int onList(char* type)
{
	char c,
		line[1000] = {0};
	int i = 0, end_list = 0, index;

	// check if it is really list
	line[i++] = '*';	// '*' is missing in recognizing char in main.c, so we add it.
	c = fgetc(input);
	while( c != '\n' && c != EOF )
	{	// read the line
		line[i++] = c;
		line[i] = '\0';
		c = fgetc(input);
	}
	i = 0;

	c = fgetc(input);
	if( c == '*' )
	{
		fprintf(output, "<%s>\n<li>", type);
		i = 1;	// ommit '*' in first char
	}

	while( line[i] != '\0' )
	{
		index = isSingleton(line[i], 3);
		if( index != -1 )
		{
			onSingleton(index);
		}
		else
		{
			fprintf(output, "%c", line[i]);
		}
		i++;
	}
	fprintf(output, "\n");

	if( c != '*' )
	{
		return 1;	// that isn't list;
	}

	do {
		c = fgetc(input);
		if( c == '\n' )
		{
			c = fgetc(input);
			if( c == '*' )
			{
				fprintf(output, "</li>\n<li>");
			}
			else if( c == '\n' )
			{
				end_list = 1;
				fprintf(output, "</li>\n");
			}
			else
			{
				fprintf(output, "%c\n", c);
			}
		}
		else if( (index = isSingleton(c, 3) ) != -1 )
		{
			onSingleton(index);
		}
		else
		{
			fprintf(output, "%c", c);
		}
	} while(end_list == 0 && c != EOF);

	fprintf(output, "</%s>\n", type);

	return 0;
}