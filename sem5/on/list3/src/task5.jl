# Michał Kallas, 272398

include("methods.jl")
using .Methods

f(x::Float64) = ℯ^x - 3 * x

delta = 10^(-4)
epsilon = 10^(-4)

result1 = bisection_method(f, 0.0, 1.0, delta, epsilon)
result2 = bisection_method(f, 1.0, 2.0, delta, epsilon)

println("Result1: $result1")
println("Result2: $result2")
