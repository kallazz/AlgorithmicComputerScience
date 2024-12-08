# Michał Kallas, 272398

include("methods.jl")
using .Methods

f1(x::Float64) = abs(x)
a1, b1 = -1.0, 1.0

f2(x::Float64) = 1 / (1 + x^2)
a2, b2 = -5.0, 5.0

ns = [5, 10, 15]

filename = splitext(basename(@__FILE__))[1]

for current_n in ns
    plot_nnfx(f1, a1, b1, current_n, filename, 1)
    plot_nnfx(f2, a2, b2, current_n, filename, 2)
end
