# Michał Kallas, 272398

using JuMP;
import GLPK;

function solve_optimal_path_between_cities_problem(cities::Vector, edges::Vector, edge_costs::Matrix, edge_times::Matrix, start_city::Int, end_city::Int, max_time::Int)
    model = Model(GLPK.Optimizer)

    n = length(cities)

    adjacency_matrix = zeros(Int, n, n)
    for edge in edges
        adjacency_matrix[edge[1], edge[2]] = 1
    end

    # x[i, j] to 1, jeśli dana krawędź znajduje się w ścieżce, 0 w przeciwnym wypadku
    @variable(model, 0 <= x[1:n, 1:n] <= 1, Int)

    # czas przejazdu nie może być większy niż maksymalny
    @constraint(model, sum(x .* edge_times) <= max_time)

    # jeśli nie ma połączeń między miastami i oraz j, to x[i][j] = 0
    for i in 1:n
        for j in 1:n
            if adjacency_matrix[i, j] == 0
                @constraint(model, x[i, j] == 0)
            end
        end
    end

    # z miasta początkowego da się wyjść tylko na jeden sposób
    @constraint(model, sum(x[start_city, :]) == 1)
    # do miasta docelowego da się wejść tylko na jeden sposób
    @constraint(model, sum(x[:, end_city]) == 1)

    # miasta mają tyle samo połączeń wchodzących co wychodzących
    for city in cities
        if city != start_city && city != end_city
            @constraint(model, sum(x[city, :]) == sum(x[:, city]))
        end
    end

    # minimalizujemy koszty podróży
    @objective(model, Min, sum(x .* edge_costs))

    optimize!(model)

    println("Cost: $(objective_value(model))")
    println("Time: $(sum(value.(x) .* edge_times))")
    println("Edges: $([(i, j) for i in 1:n, j in 1:n if value(value.(x)[i, j]) == 1]))")
end

cities = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
edges_with_cost_and_time = [
    [1, 2, 3, 4], [1, 3, 4, 9], [1, 4, 7, 10], [1, 5, 8, 12], [2, 3, 2, 3],
    [3, 4, 4, 6], [3, 5, 2, 2], [3, 10, 6, 11], [4, 5, 1, 1], [4, 7, 3, 5],
    [5, 6, 5, 6], [5, 7, 3, 3], [5, 10, 5, 8], [6, 1, 5, 8], [6, 7, 2, 2],
    [6, 10, 7, 11], [7, 3, 4, 6], [7, 8, 3, 5], [7, 9, 1, 1], [8, 9, 1, 2],
    [9, 10, 2, 2]
]
edges_with_cost_and_time = [
    [1, 2, 1, 3], [2, 3, 2, 2], [3, 10, 3, 5], [1, 4, 1, 10], [4, 10, 1, 6]
]
start_city = 1
end_city = 10
max_time = 15

edges = []
edge_costs = zeros(length(cities), length(cities))
edge_times = zeros(length(cities), length(cities))

for edge in edges_with_cost_and_time
    push!(edges, [edge[1], edge[2]])
    edge_costs[edge[1], edge[2]] = edge[3]
    edge_times[edge[1], edge[2]] = edge[4]
end

solve_optimal_path_between_cities_problem(cities, edges, edge_costs, edge_times, start_city, end_city, max_time)
