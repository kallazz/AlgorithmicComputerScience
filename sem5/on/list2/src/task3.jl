# Michał Kallas, 272398

using LinearAlgebra

function hilb(n::Int)
# Function generates the Hilbert matrix  A of size n,
#  A (i, j) = 1 / (i + j - 1)
# Inputs:
#	n: size of matrix A, n>=1
#
#
# Usage: hilb(10)
#
# Pawel Zielinski
        if n < 1
         error("size n should be >= 1")
        end
        return [1 / (i + j - 1) for i in 1:n, j in 1:n]
end

function matcond(n::Int, c::Float64)
# Function generates a random square matrix A of size n with
# a given condition number c.
# Inputs:
#	n: size of matrix A, n>1
#	c: condition of matrix A, c>= 1.0
#
# Usage: matcond(10, 100.0)
#
# Pawel Zielinski
        if n < 2
         error("size n should be > 1")
        end
        if c< 1.0
         error("condition number  c of a matrix  should be >= 1.0")
        end
        (U,S,V)=svd(rand(n,n))
        return U*diagm(0 =>[LinRange(1.0,c,n);])*V'
end

function compute_relative_error(computed_value, exact_value)
    return norm(exact_value - computed_value) / norm(computed_value)
end

function run_hilbert_matrix_experiment(max_n::Int)
    for n in 1:max_n
        x = ones(Float64, n)
        A = hilb(n)
        b = A * x

        gauss_x = A \ b
        inv_x = inv(A) * b

        gauss_error = compute_relative_error(gauss_x, x)
        inv_error = compute_relative_error(inv_x, x)

        println("$n & $(cond(A)) & $(rank(A)) & $gauss_error & $inv_error\\\\\n\\hline")
    end
end

function run_random_matrix_experiment()
    conditions = [1.0, 10.0, 10.0^3, 10.0^7, 10.0^12, 10.0^16]
    for n in [5, 10, 20]
        x = ones(Float64, n)
        for c in conditions
            A = matcond(n, c)
            b = A * x

            gauss_x = A \ b
            inv_x = inv(A) * b

            gauss_error = compute_relative_error(gauss_x, x)
            inv_error = compute_relative_error(inv_x, x)

            println("$n & $c & $(rank(A)) & $gauss_error & $inv_error\\\\\n\\hline")
        end
    end
end

run_hilbert_matrix_experiment(15)
println()
run_random_matrix_experiment()
