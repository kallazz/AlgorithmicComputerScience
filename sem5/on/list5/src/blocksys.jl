# Michał Kallas, 272398

module blocksys

export parse_sparse_block_matrix, parse_right_hand_side_vector, gauss, gauss_with_pivoting, non_optimized_gauss

using LinearAlgebra
include("sparse_block_matrix.jl")
using .sparse_block_matrix

# ******************************************* INPUT PARSING *******************************************

function parse_sparse_block_matrix(file_path::String)::Tuple{SparseBlockMatrix, Int64, Int64}
    open(file_path, "r") do file
        line = split(readline(file))
        matrix_size, block_size = parse(Int64, line[1]), parse(Int64, line[2])
        A = SparseBlockMatrix(matrix_size, matrix_size)
        for line in eachline(file)
            if !isempty(line)
                line = split(line)
                i, j, val = parse(Int64, line[1]), parse(Int64, line[2]), parse(Float64, line[3])
                A[i, j] = val
            end
        end

        return A, matrix_size, block_size
    end
end

function parse_right_hand_side_vector(file_path::String)::Vector{Float64}
    open(file_path, "r") do file
        vector_size = parse(Int64, readline(file))
        b = zeros(Float64, vector_size)
        counter = 1
        for line in eachline(file)
            if !isempty(line)
                b[counter] = parse(Float64, line)
            end
            counter += 1
        end

        return b
    end
end

# ********************************** GAUSSIAN ELIMINATION ALGORITHMS **********************************

function gauss(A::SparseBlockMatrix, b::Vector{Float64}, matrix_size::Int64, block_size::Int64)
    for k in 1:matrix_size-1
        last_row_index = min(k + block_size + 1, matrix_size)
        last_column_index = min(k + block_size, matrix_size)

        for i in k+1:last_row_index
            factor = A[i, k] / A[k, k]

            for j in k:last_column_index
                A[i, j] -= factor * A[k, j]
            end

            b[i] -= factor * b[k]
        end
    end

    x = zeros(Float64, matrix_size)
    for k in matrix_size:-1:1
        last_column_index = min(k + block_size + 1, matrix_size)
        x[k] = b[k]

        for i in k+1:last_column_index
            x[k] -= A[k, i] * x[i]
        end
        x[k] /= A[k, k]
    end

    return x
end

function gauss_with_pivoting(A::SparseBlockMatrix, b::Vector{Float64}, matrix_size::Int64, block_size::Int64)
	p = collect(1:matrix_size)

	for k in 1:matrix_size-1
        last_row_index = min(k + block_size + 1, matrix_size)
        last_column_index = min(k + 2 * block_size, matrix_size)

        pivot_row = k
        max_value = abs(A[p[k], k])
        for i in k+1:last_row_index
            current_value = abs(A[p[i], k])
            if current_value > max_value
                max_value = current_value
                pivot_row = i
            end
        end

		p[k], p[pivot_row] = p[pivot_row], p[k]

		for i in k+1:last_row_index
			factor = A[p[i], k] / A[p[k], k]

			for j in k:last_column_index
				A[p[i], j] -= factor * A[p[k], j]
			end

            b[p[i]] -= factor * b[p[k]]
		end
	end

    x = zeros(Float64, matrix_size)
    for k in matrix_size:-1:1
        last_column_index = min(k + 2 * block_size, matrix_size)
        x[k] = b[p[k]]

        for i in k+1:last_column_index
            x[k] -= A[p[k], i] * x[i]
        end
        x[k] /= A[p[k], k]
    end

	return x
end

function non_optimized_gauss(A::SparseBlockMatrix, b::Vector{Float64}, matrix_size::Int64, block_size::Int64)
    for k in 1:matrix_size-1
        for i in k+1:matrix_size
            factor = A[i, k] / A[k, k]
            for j in k:matrix_size
                A[i, j] -= factor * A[k, j]
            end
            b[i] -= factor * b[k]
        end
    end

    x = zeros(Float64, matrix_size)
    for k in matrix_size:-1:1
        x[k] = b[k]
        for j in k+1:matrix_size
            x[k] -= A[k, j] * x[j]
        end
        x[k] /= A[k, k]
    end

    return x
end

end