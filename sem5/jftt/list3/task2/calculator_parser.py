from calculator_lexer import tokens
from field_operations import *

_FIELD_CHARACTERISTIC = 1234577

_rpn_result = []
_division_by_zero_flag = False

precedence = (
    ("left", "ADD", "SUB"),
    ("left", "MUL", "DIV"),
    ("nonassoc", "POW"),
    ("right", "NEG"),
)


# -----------------------------------------------------------------------------
# Line rules
# -----------------------------------------------------------------------------
def p_line_expression(p):
    """line : expression EOL"""
    global _division_by_zero_flag
    print(f"Reverse Polish Notation: {" ".join(_rpn_result)}")
    print(f"Result: {p[1]}")
    _rpn_result.clear()
    _division_by_zero_flag = False


def p_line_error(p):
    """line : error EOL"""
    global _division_by_zero_flag
    if _division_by_zero_flag:
        print("Division by zero")
    _rpn_result.clear()
    _division_by_zero_flag = False


# -----------------------------------------------------------------------------
# Expression rules
# -----------------------------------------------------------------------------
def p_expression_number(p):
    """expression : number"""
    p[0] = p[1]
    _rpn_result.append(str(p[1]))


def p_expression_add(p):
    """expression : expression ADD expression"""
    p[0] = field_add(p[1], p[3], _FIELD_CHARACTERISTIC)
    _rpn_result.append("+")


def p_expression_sub(p):
    """expression : expression SUB expression"""
    p[0] = field_sub(p[1], p[3], _FIELD_CHARACTERISTIC)
    _rpn_result.append("-")


def p_expression_mul(p):
    """expression : expression MUL expression"""
    p[0] = field_mul(p[1], p[3], _FIELD_CHARACTERISTIC)
    _rpn_result.append("*")


def p_expression_div(p):
    """expression : expression DIV expression"""
    global _division_by_zero_flag
    if p[3] == 0:
        _division_by_zero_flag = True
        raise SyntaxError
    else:
        p[0] = field_div(p[1], p[3], _FIELD_CHARACTERISTIC)
    _rpn_result.append("/")


def p_expression_pow(p):
    """expression : expression POW exponent"""
    p[0] = field_pow(p[1], p[3], _FIELD_CHARACTERISTIC)
    _rpn_result.append("^")


def p_expression_paren(p):
    """expression : LPAREN expression RPAREN"""
    p[0] = p[2]


def p_expression_neg(p):
    """expression : SUB LPAREN expression RPAREN %prec NEG"""
    p[0] = field_sub(0, p[3], _FIELD_CHARACTERISTIC)
    _rpn_result.append("~")


# -----------------------------------------------------------------------------
# Exponent rules
# -----------------------------------------------------------------------------
def p_exponent_exponentnumber(p):
    """exponent : exponent_number"""
    p[0] = p[1]
    _rpn_result.append(str(p[1]))


def p_exponent_add(p):
    """exponent : exponent ADD exponent"""
    p[0] = field_add(p[1], p[3], _FIELD_CHARACTERISTIC - 1)
    _rpn_result.append("+")


def p_exponent_sub(p):
    """exponent : exponent SUB exponent"""
    p[0] = field_sub(p[1], p[3], _FIELD_CHARACTERISTIC - 1)
    _rpn_result.append("-")


def p_exponent_mul(p):
    """exponent : exponent MUL exponent"""
    p[0] = field_mul(p[1], p[3], _FIELD_CHARACTERISTIC - 1)
    _rpn_result.append("*")


def p_exponent_div(p):
    """exponent : exponent DIV exponent"""
    global _division_by_zero_flag
    if p[3] == 0:
        _division_by_zero_flag = True
        raise SyntaxError
    else:
        p[0] = field_div(p[1], p[3], _FIELD_CHARACTERISTIC - 1)
    _rpn_result.append("/")


def p_exponent_paren(p):
    """exponent : LPAREN exponent RPAREN"""
    p[0] = p[2]


def p_exponent_neg_paren(p):
    """exponent : SUB LPAREN exponent RPAREN %prec NEG"""
    p[0] = field_sub(0, p[3], _FIELD_CHARACTERISTIC - 1)
    _rpn_result.append("~")


# -----------------------------------------------------------------------------
# Number rules
# -----------------------------------------------------------------------------
def p_number_num(p):
    """number : NUM"""
    p[0] = p[1] % _FIELD_CHARACTERISTIC


def p_number_neg(p):
    """number : SUB number %prec NEG"""
    p[0] = field_sub(0, p[2], _FIELD_CHARACTERISTIC)


# -----------------------------------------------------------------------------
# Exponent Number rules
# -----------------------------------------------------------------------------
def p_exponentnumber_num(p):
    """exponent_number : NUM"""
    p[0] = p[1] % (_FIELD_CHARACTERISTIC - 1)


def p_exponentnumber_neg(p):
    """exponent_number : SUB exponent_number %prec NEG"""
    p[0] = field_sub(0, p[2], _FIELD_CHARACTERISTIC - 1)


# -----------------------------------------------------------------------------
# Error rule
# -----------------------------------------------------------------------------
def p_error(p):
    if p:
        print("Syntax error")
