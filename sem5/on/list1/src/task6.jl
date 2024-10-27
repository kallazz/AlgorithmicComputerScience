# Michał Kallas, 272398

f(x::Float64) = sqrt(x^2 + 1.0) - 1.0
g(x::Float64) = (x^2.0) / (sqrt(x^2.0 + 1.0) + 1.0)

for i::Float64 in 1:180
    x = (8.0^(-i))

    println("Input: 8^(-$i)")
    println("f($x) = $(f(x))")
    println("g($x) = $(g(x))")
    println()
end