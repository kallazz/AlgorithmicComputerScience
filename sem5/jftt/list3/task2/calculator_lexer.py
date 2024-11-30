tokens = (
    "NUM",
    "ADD",
    "SUB",
    "MUL",
    "DIV",
    "POW",
    "LPAREN",
    "RPAREN",
    "EOL",
    "INVALID",
)

t_ignore = " \t"
t_ignore_COMMENT = r"^\#(.|\\\n)*\n"
t_ignore_LINE_CONTINUATION = r"\\\n"


def t_NUM(t):
    r"[0-9]+"
    t.value = int(t.value)
    return t


t_EOL = r"\n"
t_ADD = r"\+"
t_SUB = r"\-"
t_MUL = r"\*"
t_DIV = r"/"
t_POW = r"\^"
t_LPAREN = r"\("
t_RPAREN = r"\)"
t_INVALID = r"."


def t_error(t):
    pass
