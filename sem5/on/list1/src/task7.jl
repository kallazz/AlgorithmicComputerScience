# Michał Kallas, 272398

function approximate_derivative(func::Function, x0::Float64, h::Float64)
    return (func(x0 + h) - func(x0)) / h
end

f(x::Float64) = sin(x) + cos(3x)
f_derivative(x::Float64) = cos(x) - 3sin(3x)

for n::Float64 in 0:54
    x0 = 1.0
    h = 2.0^(-n)
    approximate_result = approximate_derivative(f, x0, h)
    exact_result = f_derivative(x0)
    approximation_error = abs(exact_result - approximate_result)

    println("Approximate result for n=-$n is $approximate_result Approximation error: $approximation_error")
end
