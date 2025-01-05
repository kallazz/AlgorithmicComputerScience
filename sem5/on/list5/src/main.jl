# Michał Kallas, 272398

using LinearAlgebra

include("blocksys.jl")
using .blocksys

function save_output_to_file(output_file_path::String, result_vector::Vector{Float64}, relative_error::Union{Nothing, Float64}=nothing)
    open(output_file_path, "w") do file
        if relative_error !== nothing
            println(file, relative_error)
        end

        for result in result_vector
            println(file, result)
        end
    end
end

function main()
    should_calculate_relative_error = false

    println("Enter matrix file path: ")
    matrix_file_path = readline()
    A, matrix_size, block_size = parse_sparse_block_matrix(matrix_file_path )

    println("Would you like to provide vector b?(yes/no): ")
    choice = readline()
    if choice == "yes"
        println("Enter vector file path: ")
        vector_file_path = readline()
        b = parse_right_hand_side_vector(vector_file_path)
        should_calculate_relative_error = true
    else
        b = A * ones(Float64, matrix_size)
    end

    println("Choose the algorithm:")
    println("1. Optimized Gaussian Elimination")
    println("2. Optimized Gaussian Elimination with Partial Pivoting")
    choice = readline()

    if choice == "1" || choice == "2"
        algorithm = (choice == "1") ? gauss : gauss_with_pivoting
        x = algorithm(A, b, matrix_size, block_size)
        println("The result is $x")

        println("Would you like to save the result?(yes/no): ")
        choice = readline()
        if choice == "yes"
            println("Enter output file path: ")
            output_file_path = readline()

            if should_calculate_relative_error 
                ones_vector = ones(Float64, matrix_size)
                relative_error = norm(x - ones_vector) / norm(x)
            else
                relative_error = nothing
            end

            save_output_to_file(output_file_path, x, relative_error)
        end
    else
        println("$choice is not a valid option.")
    end

end

main()