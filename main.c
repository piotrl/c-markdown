#include <stdlib.h>

#include "libs/config.h"
#include "libs/stack.h"
#include "libs/markdown.h"

int main(int argc, char const *argv[])
{
    int index;
    char c, is_quote, is_code, newline;

        is_quote = is_code = 0; // 0 OR 1
        newline = 1;

    if( argc <= 1 )
    {
        printf("\n %s: Podaj nazwe pliku do parsowania. \n\n", argv[0] );
        return 1;
    }

    input = fopen(argv[1], "r");
    output = fopen(argv[2], "w");

    if( output == NULL )
    {
        output = stdout;
    }
    else
    {
        printf("\n %s: Zapisano wyniki do: %s\n", argv[0], argv[2]);
    }

    if( input == NULL )
    {
        printf("\n %s: Brak dostepu do %s\n", argv[0], argv[1] );
        return 1;
    }

    while( ( c = fgetc(input) ) != EOF )
    {
        index = isSingleton(c, 3);

        if( c == '&' || c == '<' )
        {   // These charsets can't live in HTML file
            if( c == '&' )
                fprintf(output, "&amp;");
            else {
                fprintf(output, "&lt;");
            }
        }
        else if( newline == 1 && ( c == '>' ||  c == '-' || c == '#' || c == '*' ) )
        {   // on new line
            if( c == '>' )
            {   // open quote
                if( is_quote == 0 )
                {
                    fprintf( output, "<%s>\n", "blockquote" );
                    is_quote = 1;
                }
            }
            else if( c == '#')
            {
                onHeader(input);
                c = '\n';   // hack: set newline to 1;
            }
            else if( c == '-' )
            {
                onHR(input);
            }
            else if( c == '*' )
            {
                onList("ul");
            }
            else
            {
                fprintf( output, "%c", c );
            }
        }
        else if( newline == 1 && is_quote == 1 && c != '>'  )
        {   // close quote
            fprintf( output, "</%s>\n", "blockquote" );
            is_quote = 0;
        }
        else if( c == '[' )
        {   // start link
            onURL(input);
        }
        else if( index != -1 )
        {
            onSingleton(index);
        }
        else
        {
            fprintf( output, "%c", c );
        }

        /**
         * CHANGES OF STATUSES
         * ------------------------------- */

        if( c != '\n')
        {   // newline
            newline = 0;
        }
        else
        {
            newline = 1;
        }
    }
    printf("\n");
    return 0;
}