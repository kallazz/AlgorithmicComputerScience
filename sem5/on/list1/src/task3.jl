# Michał Kallas, 272398

function are_numbers_equally_distributed_with_step(
    step::Float64,
    start_value::Float64,
    number_of_iterations::Int,
    float_function::Function
)
    current_float::Float64 = start_value
    current_julia_float::Float64 = start_value

    for i in 1:number_of_iterations
        if current_float != current_julia_float
            return false
        end

        current_float += step
        current_julia_float = float_function(current_julia_float)
    end

    return true
end

function print_bitstrings_for_next_floats(start_value::Float64, number_of_iterations::Int)
    current_value::Float64 = start_value

    for i in 1:number_of_iterations
        println(bitstring(current_value))
        current_value = nextfloat(current_value)
    end
end

result1 = are_numbers_equally_distributed_with_step(2.0^(-52.0), 1.0, 10000, nextfloat)
result2 = are_numbers_equally_distributed_with_step(-2.0^(-52.0), 2.0, 10000, prevfloat)

calculated_step1 = nextfloat(0.5) - 0.5
println("Step in [1/2, 1]: $calculated_step1")
result3 = are_numbers_equally_distributed_with_step(calculated_step1, 0.5, 10000, nextfloat)
result4 = are_numbers_equally_distributed_with_step(-calculated_step1, 1.0, 10000, prevfloat)

calculated_step2 = nextfloat(2.0) - 2.0
println("Step in [2, 4]: $calculated_step2")
result5 = are_numbers_equally_distributed_with_step(calculated_step2, 2.0, 10000, nextfloat)
result6 = are_numbers_equally_distributed_with_step(-calculated_step2, 4.0, 10000, prevfloat)

println("Are numbers distributed with the specified step in [1, 2]? $(result1 && result2)")
println("Are numbers distributed with the specified step in [1/2, 1]? $(result3 && result4)")
println("Are numbers distributed with the specified step in [2, 4]? $(result5 && result6)")

println("\nBitstrings starting from 1.0:")
print_bitstrings_for_next_floats(1.0, 5)

println("\nBitstrings starting from 0.5:")
print_bitstrings_for_next_floats(0.5, 5)

println("\nBitstrings starting from 2.0:")
print_bitstrings_for_next_floats(2.0, 5)
