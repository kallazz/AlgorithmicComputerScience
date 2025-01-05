# Michał Kallas, 272398

include("blocksys.jl")
using .blocksys

EXPERIMENT_OUTPUT_DIR = "../experimentOutput/"
TIME_OUTPUT_FILENAME = "timeResults.csv"
MEMORY_OUTPUT_FILENAME = "memoryResults.csv"
TEST_DATA_DIR = "../testData/"
MATRIX_FILENAMES = ["A16.txt", "A10000.txt", "A50000.txt", "A100000.txt", "A300000.txt", "A500000.txt"]
RIGHT_HAND_SIDE_VECTOR_FILENAMES = ["b16.txt", "b10000.txt", "b50000.txt", "b100000.txt", "b300000.txt", "b500000.txt"]

function clear_file(file_path::String)
    open(file_path, "w") do file
        write(file, "")
    end
end

function run_experiment()
    output_time_file_path = joinpath(EXPERIMENT_OUTPUT_DIR, TIME_OUTPUT_FILENAME)
    output_memory_file_path = joinpath(EXPERIMENT_OUTPUT_DIR, MEMORY_OUTPUT_FILENAME)

    clear_file(output_time_file_path)
    clear_file(output_memory_file_path)

    for i in eachindex(MATRIX_FILENAMES)
        matrix_path = joinpath(TEST_DATA_DIR, MATRIX_FILENAMES[i])
        vector_path = joinpath(TEST_DATA_DIR, RIGHT_HAND_SIDE_VECTOR_FILENAMES[i])

        A, matrix_size, block_size = parse_sparse_block_matrix(matrix_path)
        b = parse_right_hand_side_vector(vector_path)

        gauss_timed_result = @timed gauss(deepcopy(A), deepcopy(b), matrix_size, block_size)
        pivot_gauss_timed_result = @timed gauss_with_pivoting(deepcopy(A), deepcopy(b), matrix_size, block_size)

        open(output_time_file_path, "a") do file
            write(file, "$matrix_size;$(gauss_timed_result.time);$(pivot_gauss_timed_result.time);\n")
        end
        open(output_memory_file_path, "a") do file
            write(file, "$matrix_size;$(gauss_timed_result.bytes);$(pivot_gauss_timed_result.bytes);\n")
        end
    end
end

run_experiment()
