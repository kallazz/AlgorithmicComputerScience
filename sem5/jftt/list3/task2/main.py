import sys

from ply import lex, yacc

import calculator_lexer
import calculator_parser


def main() -> None:
    lexer = lex.lex(module=calculator_lexer)
    parser = yacc.yacc(module=calculator_parser)

    current_line = ""
    for input_line in sys.stdin:
        current_line += input_line
        if not input_line.endswith("\\\n"):
            parser.parse(current_line, lexer=lexer)
            current_line = ""


if __name__ == "__main__":
    main()
