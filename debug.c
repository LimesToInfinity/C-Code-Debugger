#include <stdio.h>
#define MAXERROR 1000

int main()
{
    int nline = 1;
    int c;
    int skip = 0;
    
    /* comment variables*/
    int iscomment = 0;
    int comment_line = 0;

    /* single and doublequote variables */
    int issinglequote = 0;
    int singlequote_line = 0;
    int isdoublequote = 0;
    int doublequote_line = 0;

    /* braces "{}" variables */
    int open_bra[MAXERROR];
    int closed_bra[MAXERROR];
    int open_bra_count = 0;
    int closed_bra_count = 0;

    /* parenthesis "()" variables */
    int open_par[MAXERROR];
    int closed_par[MAXERROR];
    int open_par_count = 0;
    int closed_par_count = 0;

    /* square brackets "[]" variables */
    int open_squ[MAXERROR];
    int closed_squ[MAXERROR];
    int open_squ_count = 0;
    int closed_squ_count = 0;
    
    /* Check file for unbalanced braces, parenthesis, square brackets, 
    single quotes, double quotes and comments */
    
    /* Read in the next character */
    while ((c = getchar())!= EOF) {

        /* Skip because character is masked */
        if (skip) {
            skip = 0;
            continue;
        }
        /* Check if we are entering a comment */
        if (!issinglequote && !isdoublequote) {
            if (c == '/') {
                if ((c = getchar()) == '*') {
                    if (!iscomment) {
                        iscomment = !iscomment;
                        comment_line = nline;
                    }
                    else {
                        printf("1: Line %d: New comment '/*' before last one was closed\n", nline);
                        return 0;
                    }
                }
            }

            else if (c == '*') {
                if ((c = getchar()) == '/') {
                    if (iscomment) {
                        iscomment = !iscomment;
                        continue;
                    }
                    else {
                        printf("1: Line %d: Closed comment '*/' before opened\n", nline);
                        return 0;
                    }
                }
            }
        }
        
        /* If the character is a line break, increment nline */
        if (c=='\n'){
            ++nline;
        }

        /* If we are currently in a comment skip character */
        else if (iscomment) {
            ;
        }

        /* If next character is masked set skip to 1 */
        else if (c == '\\') {
            skip = 1;
        }
        

        /* Recognize single or doublequotes */
        else if (c == '\'') {
            issinglequote = !issinglequote;
            if (issinglequote) {
                singlequote_line = nline;
            }
        }

        else if (c == '\"') {
            isdoublequote = !isdoublequote;
            if (isdoublequote) {
                doublequote_line = nline;
            }
        }

        /* Ignore chars as long as issingleqoute or isdoublequote are true */
        else if (issinglequote || isdoublequote) {
            ;
        }

        /* Increment open_bra if char is '{' */
        else if (c=='{') {
            open_bra[open_bra_count] = nline;
            ++open_bra_count;
        }
        /* Increment open_par if char is '(' */
        else if (c=='(') {
            open_par[open_par_count] = nline;
            ++open_par_count;
        }
        /* Increment nopen_squ if char is '[' */
        else if (c=='[') {
            open_squ[open_squ_count] = nline;
            ++open_squ_count;
        }

        /* Decrement open_bra_count, if a closing brace '}' is found and there is a corresponding open brace '{'
        found earlier, else increment closed_bra_count */
        else if (c=='}') {
            if (open_bra_count > 0){
                open_bra[--open_bra_count] = 0;
            }
            else {
                closed_bra[closed_bra_count] = nline;
                ++closed_bra_count;
            }
        }
        /* Same for parenthesis */
        else if (c==')') {
            if (open_par_count > 0){
                open_par[--open_par_count] = 0;
            }
            else {
                closed_par[closed_par_count] = nline;
                ++closed_par_count;
            }
        }
        /* Same for square brackets */
        else if (c==']') {
            if (open_squ_count > 0){
                open_squ[--open_squ_count] = 0;
            }
            else {
                closed_squ[closed_squ_count] = nline;
                ++closed_squ_count;
            }
        }
    }
    /* Print all errors in the order they appeared */
    int error_iter, line_iter, i, j, k, l, m, n;
    i = j = k = l = m = n = 0;
    line_iter = 1;
    error_iter = 1;

    while (i < open_bra_count || j < closed_bra_count|| k < open_par_count || 
           l < closed_par_count || m < open_squ_count || n < closed_squ_count
           || issinglequote || isdoublequote || iscomment) {
        
        if (iscomment) {
           printf("1: Line %d: Open comment '/*' was never closed\n", comment_line);
           return 0; 
        }

        if (i < open_bra_count && open_bra[i] == line_iter) {
            printf("%5d: Line %d: Unbalanced open brace\n", error_iter, line_iter);
            ++error_iter;
            ++i;
        }

        else if (j < closed_bra_count && closed_bra[j] == line_iter) {
            printf("%5d: Line %d: Unbalanced closed brace\n", error_iter, line_iter);
            ++error_iter;
            ++j;
            continue;
        }
        
        else if (k < open_par_count && open_par[k] == line_iter) {
            printf("%5d: Line %d: Unbalanced open parenthesis\n", error_iter, line_iter);
            ++error_iter;
            ++k;
        }

        else if (l < closed_par_count && closed_par[l] == line_iter) {
            printf("%5d: Line %d: Unbalanced closed parenthesis\n", error_iter, line_iter);
            ++error_iter;
            ++l;
        }

        else if (m < open_squ_count && open_squ[m] == line_iter) {
            printf("%5d: Line %d: Unbalanced open square bracket\n", error_iter, line_iter);
            ++error_iter;
            ++m;
        }

        else if (n < closed_squ_count && closed_squ[n] == line_iter) {
            printf("%5d: Line %d: Unbalanced closed square bracket\n", error_iter, line_iter);
            ++error_iter;
            ++n;
        }

        else if (issinglequote && singlequote_line == line_iter) {
            printf("%5d: Line %d: Unbalanced singlequote\n", error_iter, line_iter);
            ++error_iter;
            issinglequote = 0;
            singlequote_line = 0;
        }

        else if (isdoublequote && doublequote_line == line_iter) {
            printf("%5d: Line %d: Unbalanced doublequote\n", error_iter, line_iter);
            ++error_iter;
            isdoublequote = 0;
            doublequote_line = 0;
        }
        ++line_iter;
    }
    return 0;
}
