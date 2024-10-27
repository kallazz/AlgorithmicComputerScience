# Michał Kallas, 272398

function find_macheps_kahan(type::Type)
    return type(3.0) * (type(4.0) / type(3.0) - type(1.0)) - type(1.0)
end

float16_macheps = find_macheps_kahan(Float16)
float32_macheps = find_macheps_kahan(Float32)
float64_macheps = find_macheps_kahan(Float64)

println("Kahan macheps for Float16: $float16_macheps")
println("Julia macheps for Float16: $(eps(Float16))")
println("Kahan macheps for Float32: $float32_macheps")
println("Julia macheps for Float32: $(eps(Float32))")
println("Kahan macheps for Float64: $float64_macheps")
println("Julia macheps for Float64: $(eps(Float64))")
println()

println("Float16 is the opposite: $(-float16_macheps == eps(Float16))")
println("Float32 is the same: $(float32_macheps == eps(Float32))")
println("Float64 is the opposite: $(-float64_macheps == eps(Float64))")