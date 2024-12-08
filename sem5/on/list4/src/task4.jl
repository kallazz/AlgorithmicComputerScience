# Michał Kallas, 272398

include("task1.jl")
include("task2.jl")

using Plots

function plot_nnfx(f::Function, a::Float64, b::Float64, n::Int, filename::String, function_number::Int)
    amount_of_points = 100 * n

    h = (b - a) / n
    interpolation_nodes = collect(a:h:b)
    f_values_for_interpolation_nodes = map(f, interpolation_nodes)

    quotients = difference_quotients(interpolation_nodes, f_values_for_interpolation_nodes)

    x_step = (b - a) / (amount_of_points - 1)
    xs = collect(a .+ (0:(amount_of_points - 1)) * x_step)
    polynomial_values = zeros(amount_of_points)
    function_values = zeros(amount_of_points)

    polynomial_values[1] = function_values[1] = f_values_for_interpolation_nodes[1]

    for i in 2:amount_of_points
        polynomial_values[i] = newtons_polynomial(interpolation_nodes, quotients, xs[i])
        function_values[i] = f(xs[i])
    end

    # plot(xs, [polynomial_values, function_values], label=["Polynomial" "Function f_$function_number"], title="Interpolation of function f_$function_number with n = $n")
    plot(xs, [polynomial_values, function_values], label=["Wielomian" "Funkcja f_$function_number"], title="Interpolacja funkcji f_$function_number z n = $n")
    savefig("../plots/$(filename)_f$(function_number)_n$n")
end
