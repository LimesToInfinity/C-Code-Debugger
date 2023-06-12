# C-Code-Debugger
A small C program that debugs simple errors.
---
This program can detect unbalanced braces "{}", parenthesis "()", square brackets "[]",
single quotes ', double quotes " as well as C comments /**/. It reads in 
a C source file and prints each error found on a new line, in which it prints the number of the error, 
followed by the line in which the error occured with an additional explanation of the detected error. 

## How it works
---
### Logic
---
The program reads in a C source file character wise and saves the current character in the variable `c`.   
Now it begins to check for rules in the following order:   

> 1. It checks if the variable `skip` is equal to `1` (true). This means the last character was a backslash outside of a comment   
so the current character was masked and should be skipped.

> 2. Check if we are entering a comment, if so:
    1. Check whether we are not already in a comment and set `iscomment` to `1` (true). Then continue with the while loop.

> 3. Check if we are leaving a comment if so:
    1. Check wheter we are currently in a comment and set `iscomment` to `0` (false). Then continue with the while loop.
    2. If we are currently not in a comment, we are leaving a never opened comment, throw error.

> 4. Check if `c` is a new line character `\n`, then increment our line counter `nline`.

> 5. Check if `iscomment` is true then go to the next iteration.

> 6. Check if `c` is a backslash, then set `skip` to true, and skip the next character during the next iteration (case 1).

> 7. Check if we are entering a single quote `'` (chracter constant) and negate the variable `issinglequote'.

> 8. Check if we are entering a double quote `"` (string) and negate the variable `isdoublequote`. 

> 9. Ignor characters as long as `issinglequote` or `isdoublequote` are true.

> 10. Increment `open_bra_count` when we encounter a `{`.

> 12. Increment `open_par_count` when we encounter a `(`.

> 14. Increment `open_squ_count` when we encounter a `[`.

> 13. Check if we encountered a closing brace `}`.
    1. If `open_bra_count > 0`, decrement `open_bra_count` (we found a corresponding closing `}`).
    2. We found a closing `}`, without a corresponding open `{`.
   
> 14. Check if we encountered a open parenthesis `)`.
    1. If `open_par_count > 0`, decrement `open_par_count` (we found a corresponding closing `)`).
    2. We found a closing `}`, without a corresponding open `(`.

> 15. Check if we encountered a `]`.
    1. If `open_squ_count > 0`, decrement `open_squ_count` (we found a corresponding closing `]`).
    2. We found a closing `]`, without a corresponding open `[`.

### Errors
---
The lines which contain errors are saved in the arrays `open_bra`, `open_par`, `open_squ`. Lines with Single and double quote errors   
are stored in the variables `singlequote_line` and `doublequote_line`. A line with a never closed comment is stored in the variable   
`comment_line`. Every other comment error is printed immediately and uses the current line variable `nline`.   
Next we iterate through the lines and print the errors, if a line is found in one of the error arrays/variables.
