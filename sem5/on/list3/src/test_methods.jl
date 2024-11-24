# Michał Kallas, 272398

include("methods.jl")
using .Methods
using Test

f(x::Float64) = -(3x^2) + 7x + 10
f_derivative(x::Float64) = 7 - 6x

delta = 0.0001
epsilon = 0.001
max_iterations = 10000

@testset "Root Approximation Finding Methods" begin
    # Bisection method tests
    approximation, value, _, error_type = bisection_method(f, -2.0, 0.0, delta, epsilon)
    @test value == f(approximation)
    @test abs(value) < epsilon
    @test error_type == 0

    approximation, value, _, error_type = bisection_method(f, 2.0, 4.0, delta, epsilon)
    @test value == f(approximation)
    @test abs(value) < epsilon
    @test error_type == 0

    approximation, value, _, error_type = bisection_method(f, 100.0, 110.0, delta, epsilon)
    @test error_type == 1

    # Newton's method tests
    approximation, value, _, error_type = newtons_method(f, f_derivative, 0.0, delta, epsilon, max_iterations)
    @test value == f(approximation)
    @test abs(value) < epsilon
    @test error_type == 0

    # Secant method tests
    approximation, value, _, error_type = secant_method(f, 1.0, 2.0, delta, epsilon, max_iterations)
    @test value == f(approximation)
    @test abs(value) < epsilon
    @test error_type == 0
end
