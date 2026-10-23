#!/bin/bash

bison -d yacc.y && flex lex.l && gcc yacc.tab.c lex.yy.c -o calc -lfl 