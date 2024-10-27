# Michał Kallas, 272398

function find_macheps(type::Type)
    ε::type = 1.0

    while (ε / type(2.0)) + type(1.0) != type(1.0)
        ε /= 2.0
    end

    return ε
end

function find_eta(type::Type)
    η::type = 1.0

    while (η / type(2.0)) != 0.0
        η /= 2.0
    end

    return η
end

function find_max_float(type::Type)
    max_float::type = 1.0

    while !isinf(max_float * type(2.0))
        max_float *= 2.0
    end

    return max_float * (type(2.0) - find_macheps(type))
end

float16_macheps = find_macheps(Float16)
float32_macheps = find_macheps(Float32)
float64_macheps = find_macheps(Float64)

# (2.0^(-1.0) * 2.0^(1.0 - t)), t = mantissa size + 1
float16_precision = Float16(2.0^(-1.0) * 2.0^(1.0 - 11.0))
float32_precision = Float32(2.0^(-1.0) * 2.0^(1.0 - 24.0))
float64_precision = Float64(2.0^(-1.0) * 2.0^(1.0 - 53.0))

println("Macheps for Float16: $float16_macheps, $(float16_macheps == eps(Float16)), $(float16_macheps == 2.0 * float16_precision)")
println("Macheps for Float32: $float32_macheps, $(float32_macheps == eps(Float32)), $(float32_macheps == 2.0 * float32_precision)")
println("Macheps for Float64: $float64_macheps, $(float64_macheps == eps(Float64)), $(float64_macheps == 2.0 * float64_precision)")
println()

float16_eta = find_eta(Float16)
float32_eta = find_eta(Float32)
float64_eta = find_eta(Float64)

# (2.0^(3.0 - 2.0^K - N)), K = exponent size - 1, N = mantissa size + 1
float16_min_sub = Float16(2.0^(3.0 - 2.0^(4.0) - 11.0))
float32_min_sub = Float32(2.0^(3.0 - 2.0^(7.0) - 24.0))
float64_min_sub = Float64(2.0^(3.0 - 2.0^(10.0) - 53.0))

println("Eta for Float16: $float16_eta, $(float16_eta == nextfloat(Float16(0.0))), $(float16_eta == float16_min_sub)")
println("Eta for Float32: $float32_eta, $(float32_eta == nextfloat(Float32(0.0))), $(float32_eta == float32_min_sub)")
println("Eta for Float64: $float64_eta, $(float64_eta == nextfloat(Float64(0.0))), $(float64_eta == float64_min_sub)")
println()

float16_max = find_max_float(Float16)
float32_max = find_max_float(Float32)
float64_max = find_max_float(Float64)

println("Max Float16: $float16_max, $(float16_max == floatmax(Float16))")
println("Max Float32: $float32_max, $(float32_max == floatmax(Float32))")
println("Max Float64: $float64_max, $(float64_max == floatmax(Float64))")
println()

float32_min = floatmin(Float32)
float64_min = floatmin(Float64)

# (2.0^(2.0 - 2.0^K)), K = exponent size - 1
float32_min_nor = Float32(2.0^(2.0 - 2.0^7.0))
float64_min_nor = Float64(2.0^(2.0 - 2.0^10.0))

println("Min Float32: $float32_min, $(float32_min == float32_min_nor)")
println("Min Float64: $float64_min, $(float64_min == float64_min_nor)")
