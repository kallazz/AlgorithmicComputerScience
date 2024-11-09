# Michał Kallas, 272398

function sum_forward(x::Vector, y::Vector, type::Type)
    result::type = 0.0

    for i in eachindex(x)
        result += x[i] * y[i]
    end

    return result
end

function sum_backward(x::Vector, y::Vector, type::Type)
    result::type = 0.0

    for i in reverse(eachindex(x))
        result += x[i] * y[i]
    end

    return result
end

function sum_from_biggest_to_smallest(x::Vector, y::Vector, type::Type)
    positive_sum::type = 0.0
    negative_sum::type = 0.0
    xy = zeros(length(x))
    for i in (eachindex(x))
        xy[i] = x[i] * y[i]
    end

    positive_xy = xy[xy .>= -1]
    negative_xy = xy[xy .< -1]
    positive_xy = sort(positive_xy, rev=true)
    negative_xy = sort(negative_xy)

    for i in eachindex(positive_xy)
        positive_sum += positive_xy[i]
    end

    for i in eachindex(negative_xy)
        negative_sum += negative_xy[i]
    end

    return positive_sum + negative_sum
end

function sum_from_smallest_to_biggest(x::Vector, y::Vector, type::Type)
    positive_sum::type = 0.0
    negative_sum::type = 0.0
    xy = zeros(length(x))
    for i in (eachindex(x))
        xy[i] = x[i] * y[i]
    end

    positive_xy = xy[xy .>= -1]
    negative_xy = xy[xy .< -1]
    positive_xy = sort(positive_xy)
    negative_xy = sort(negative_xy, rev=true)

    for i in eachindex(positive_xy)
        positive_sum += positive_xy[i]
    end

    for i in eachindex(negative_xy)
        negative_sum += negative_xy[i]
    end

    return positive_sum + negative_sum
end

old_x32::Vector{Float32} = [2.718281828, −3.141592654, 1.414213562, 0.5772156649, 0.3010299957]
x32::Vector{Float32} = [2.718281828, −3.141592654, 1.414213562, 0.577215664, 0.301029995]
y32::Vector{Float32} = [1486.2497, 878366.9879, −22.37492, 4773714.647, 0.000185049]

old_x64::Vector{Float64} = [2.718281828, −3.141592654, 1.414213562, 0.5772156649, 0.3010299957]
x64::Vector{Float64} = [2.718281828, −3.141592654, 1.414213562, 0.577215664, 0.301029995]
y64::Vector{Float64} = [1486.2497, 878366.9879, −22.37492, 4773714.647, 0.000185049]

println("Old Float32 x: $old_x32")
println("New Float32 x: $x32")
println()
println("Old Float64 x: $old_x64")
println("New Float64 x: $x64")
println()

expected_result = −1.00657107000000 * 10^(-11)
println("Expected result: $expected_result")
println()

println("Float32 forward sum: $(sum_forward(x32, y32, Float32))")
println("Float32 backward sum: $(sum_backward(x32, y32, Float32))")
println("Float32 biggest to smallest sum: $(sum_from_biggest_to_smallest(x32, y32, Float32))")
println("Float32 smallest to biggest sum: $(sum_from_smallest_to_biggest(x32, y32, Float32))")
println()

println("Float64 forward sum: $(sum_forward(x64, y64, Float64))")
println("Float64 backward sum: $(sum_backward(x64, y64, Float64))")
println("Float64 biggest to smallest sum: $(sum_from_biggest_to_smallest(x64, y64, Float64))")
println("Float64 smallest to biggest sum: $(sum_from_smallest_to_biggest(x64, y64, Float64))")
