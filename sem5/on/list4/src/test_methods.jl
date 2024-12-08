# Michał Kallas, 272398

using Test
include("methods.jl")
using .Methods

@testset "difference_quotients" begin
    x = [1.0, 2.0, 3.0]
    y = [2.0, 4.0, 6.0]
    expected = [2.0, 2.0, 0.0]
    result = difference_quotients(x, y)
    @test result == expected
end

@testset "newtons_polynomial" begin
    x = [1.0, 2.0, 3.0]
    y = [2.0, 4.0, 6.0]
    t = 2.5
    expected = 12.5
    result = newtons_polynomial(x, y, t)
    @test result == expected
end

@testset "natural_form" begin
    x = [1.0, 2.0, 3.0]
    y = [2.0, 4.0, 6.0]
    expected = [10.0, -14.0, 6.0]
    result = natural_form(x, y)
    @test result == expected
end
