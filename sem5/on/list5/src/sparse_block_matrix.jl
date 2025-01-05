# Michał Kallas, 272398

module sparse_block_matrix

export SparseBlockMatrix

struct SparseBlockMatrix
    index_to_value::Dict{Tuple{Int, Int}, Float64}
    number_of_columns::Int
    number_of_rows::Int
end

function SparseBlockMatrix(number_of_columns::Int, number_of_rows::Int)
    SparseBlockMatrix(Dict{Tuple{Int, Int}, Float64}(), number_of_columns, number_of_rows)
end

function Base.getindex(matrix::SparseBlockMatrix, row_index::Int, column_index::Int)
    if row_index > matrix.number_of_rows || column_index > matrix.number_of_columns
        throw(ArgumentError("Index out of bounds"))
    end

    return get(matrix.index_to_value, (row_index, column_index), 0.0)
end

function Base.setindex!(matrix::SparseBlockMatrix, value::Float64, row_index::Int, column_index::Int)
    if row_index > matrix.number_of_rows || column_index > matrix.number_of_columns
        throw(ArgumentError("Index out of bounds"))
    end

    if value != 0.0
        matrix.index_to_value[(row_index, column_index)] = value
    else
        delete!(matrix.index_to_value, (row_index, column_index))
    end
end

function Base.:*(matrix::SparseBlockMatrix, vector::Vector{Float64})
    if matrix.number_of_columns != length(vector)
        throw(ArgumentError("Matrix column count must match vector length"))
    end

    result = zeros(Float64, matrix.number_of_rows)
    for ((row_index, column_index), value) in matrix.index_to_value
        result[row_index] += value * vector[column_index]
    end

    return result
end

end