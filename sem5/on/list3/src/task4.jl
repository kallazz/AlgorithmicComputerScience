# Michał Kallas, 272398

include("methods.jl")
using .Methods

f(x::Float64) = sin(x) - (x / 2.0)^2.0
f_derivative(x::Float64) = cos(x) - (x / 2.0)

delta = 0.5 * 10^(-5)
epsilon = 0.5 * 10^(-5)
max_iterations = 10000

bisection_result = bisection_method(f, 1.5, 2.0, delta, epsilon)
newtons_result = newtons_method(f, f_derivative, 1.5, delta, epsilon, max_iterations)
secant_result = secant_method(f, 1.0, 2.0, delta, epsilon, max_iterations)

println("Bisection method result: $bisection_result")
println("Newton's method result: $newtons_result")
println("Secant method result: $secant_result")
