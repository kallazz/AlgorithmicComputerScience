# Michał Kallas, 272398

include("methods.jl")
using .Methods

f1(x::Float64) = ℯ^(1 - x) - 1
f2(x::Float64) = x * ℯ^(-x)
f1_derivative(x::Float64) = -ℯ^(1 - x)
f2_derivative(x::Float64) = -(x - 1) * ℯ^(-x)

delta = 10^(-5)
epsilon = 10^(-5)
max_iterations = 10000

bisection_result1 = bisection_method(f1, -10000.0, 10000.0, delta, epsilon)
newtons_result1 = newtons_method(f1, f1_derivative, 7.0, delta, epsilon, max_iterations)
secant_result1 = secant_method(f1, -5.0, 2.0, delta, epsilon, max_iterations)

bisection_result2 = bisection_method(f2, -20000.0, 15000.0, delta, epsilon)
newtons_result2 = newtons_method(f2, f2_derivative, 30.0, delta, epsilon, max_iterations)
secant_result2 = secant_method(f2, -10.0, 3.0, delta, epsilon, max_iterations)

println("Bisection method result: $bisection_result1")
println("Newton's method result: $newtons_result1")
println("Secant method result: $secant_result1")
