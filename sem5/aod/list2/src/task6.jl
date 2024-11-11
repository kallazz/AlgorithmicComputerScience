# Michał Kallas, 272398

using JuMP;
import GLPK;

function solve_camera_problem(containers_matrix::Matrix, camera_range::Int)
    model = Model(GLPK.Optimizer)

    m, n = size(containers_matrix)

    # x[i, j] to 1, jeśli tam jest kamera, 0 w przeciwnym wypadku
    @variable(model, 0 <= x[1:m, 1:n] <= 1, Int)

    for i in 1:m
        for j in 1:n
            if containers_matrix[i, j] == 1
                # kamera nie może znajdować się na kontenerze
                @constraint(model, x[i, j] == 0)
                # w zasięgu kamery od kontenera musi znajdować się przynajmniej 1 kamera
                @constraint(model, sum(x[max(i - camera_range, 1):min(i + camera_range, m), j]) + sum(x[i, max(j - camera_range, 1):min(j + camera_range, n)]) >= 1)
            end
        end
    end

    # minimalizujemy liczbę kamer
    @objective(model, Min, sum(x))

    optimize!(model)

    println("Min number of cameras: $(objective_value(model))")
    println("Cameras matrix: $(value.(x))")
end

# 1 tam gdzie są kontenery
containers_matrix = [
    1 0 1 0 1;
    0 0 0 0 0;
    0 1 0 1 0;
    0 0 1 0 0;
    1 0 0 0 1;
]
camera_range = 2


solve_camera_problem(containers_matrix, camera_range)
