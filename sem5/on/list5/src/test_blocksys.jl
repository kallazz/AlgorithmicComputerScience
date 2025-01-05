# Michał Kallas, 272398

using Test

include("blocksys.jl")
using .blocksys
include("matrixgen.jl")
using .matrixgen

TEST_DATA_DIR = "../testData/"

function test_blocksys()
    @testset "Blocksys Module Tests" begin
        # blockmat(1000, 10, 10.0, "A.txt")
        A, matrix_size, block_size = parse_sparse_block_matrix(TEST_DATA_DIR * "A16.txt")
        b = parse_right_hand_side_vector(TEST_DATA_DIR * "b16.txt")

        @testset "Gaussian Elimination" begin
            @testset "Without Pivoting" begin
                @test isapprox(A * gauss(deepcopy(A), deepcopy(b), matrix_size, block_size), b)
            end

            @testset "With Pivoting" begin
                @test isapprox(A * gauss_with_pivoting(deepcopy(A), deepcopy(b), matrix_size, block_size), b)
            end

            @testset "Non-optimized" begin
                @test isapprox(A * non_optimized_gauss(deepcopy(A), deepcopy(b), matrix_size, block_size), b)
            end
        end
    end

    println("All tests passed.")
end

test_blocksys()
