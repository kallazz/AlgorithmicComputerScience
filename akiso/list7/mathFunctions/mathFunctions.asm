;------------------------------------------------------------------------------------
; double f1(double a, float b, double c, int d)
; returns a / b + c * d in result
; parameters: eax = a, ebx = b, ecx = c, edx = d
f1:
    fild    dword [edx]         ; load d
    fmul    qword [ecx]         ; st0 = c * d

    fld     qword [eax]         ; load a
    fdiv    dword [ebx]         ; st0 = a / b

    fadd                        ; st0 = a / b + c * d

    fst     qword [result]      ; load the result to eax
    ret


;------------------------------------------------------------------------------------
; double f2(double a, int b)
; returns log_b(a) in result
; parameters: eax = a, ebx = b
f2:
    ; push 1 * log2(a) to stack
    fld1
    fld         qword [eax]
    fyl2x

    ; push 1 * log2(b) to stack
    fld1
    fild        dword [ebx]
    fyl2x

    fdiv                        ; log2(a) / log2(b) = logb(a)

    fst         qword [result]
    ret


;------------------------------------------------------------------------------------
; double f3(double a, int b)
; returns b^a in result
; parameters: eax = a, ebx = b
; this function uses the fact that 2^(a * log2(b)) = b^a
f3:
    fld         qword [eax]
    fild        dword [ebx]

    fyl2x                       ; st0 = st1 * log2(st0) = a * log2(b)
    fld         st0             ; duplicate

    frndint                     ; get integer part
    fxch                        ; swap st0 with st1
    fsub        st0, st1        ; get fractional part
    f2xm1                       ; 2^frac(a * log2(b))
    fld1
    faddp

    fxch                        ; swap st0 with st1
    fld1
    fscale                      ; 1 * 2^int(a * log2(b))
    fstp        st1             ; pop 1 from the stack
    fmulp                       ; 2^frac(a * log2(b)) * 2^int(a * log2(b)) = 2^(a * log2(b)) = b^a

    fst         qword [result]
    ret


;------------------------------------------------------------------------------------
; double f4(float a, int b)
; returns the b-th root of a in result
; parameters: eax = a, ebx = b
; this function uses the fact that 2^(a * log2(b)) = b^a
f4:
    fld1
    fild        dword [ebx]
    fdiv                        ; b = 1 / b

    fld         dword [eax]

    fyl2x                       ; st0 = st1 * log2(st0) = 1/b * log2(a)
    fld         st0             ; duplicate

    frndint                     ; get integer part
    fxch                        ; swap st0 with st1
    fsub        st0, st1        ; get fractional part
    f2xm1                       ; 2^frac(1/b * log2(a))
    fld1
    faddp

    fxch                        ; swap st0 with st1
    fld1
    fscale                      ; 1 * 2^int(1/b * log2(a))
    fstp        st1             ; pop 1 from the stack
    fmulp                       ; 2^frac(1/b * log2(a)) * 2^int(1/b * log2(a)) = 2^(1/b * log2(a)) = a^(1/b)

    fst         qword [result]
    ret