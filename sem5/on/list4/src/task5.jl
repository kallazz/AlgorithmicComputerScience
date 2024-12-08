# Michał Kallas, 272398

include("methods.jl")
using .Methods

f1(x::Float64) = ℯ^x
a1, b1 = 0.0, 1.0

f2(x::Float64) = x^2.0 * sin(x)
a2, b2 = -1.0, 1.0

ns = [5, 10, 15]

filename = splitext(basename(@__FILE__))[1]

for current_n in ns
    plot_nnfx(f1, a1, b1, current_n, filename, 1)
    plot_nnfx(f2, a2, b2, current_n, filename, 2)
end
