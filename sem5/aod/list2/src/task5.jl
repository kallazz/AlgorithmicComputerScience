# Michał Kallas, 272398

using JuMP;
import GLPK;

function solve_police_car_problem(min_police_cars_matrix , max_police_cars_matrix, min_police_cars_per_shift, min_police_cars_per_district)
    model = Model(GLPK.Optimizer)

    n, m = size(min_police_cars_matrix) # n - ilość dzielnic, m - ilość zmian

    # x[i, j] to ilość radiowozów przydzielonych do dzielnicy i w zmianie j
    @variable(model, x[1:n, 1:m] >= 0)

    # dla każdego [i, j] musi być >= radiowozów niż min i <= radiowozów niż max
    @constraint(model, min_police_cars_matrix .<= x .<= max_police_cars_matrix)
    # ilość radiowozów dla zmian musi być większa od min
    @constraint(model, vec(sum(x, dims = 1)) .>= min_police_cars_per_shift)
    # ilość radiowozów dla dzielnic musi być większa od min
    @constraint(model, vec(sum(x, dims = 2)) .>= min_police_cars_per_district)

    # minimalizujemy liczbę radiowozów
    @objective(model, Min, sum(x))

    optimize!(model)

    println("Min number of police cars: $(objective_value(model))")
    println("Police cars per district per shift: $(value.(x))")
end

min_police_cars_matrix = [
    2 4 3;
    3 6 5;
    5 7 6;
]
max_police_cars_matrix = [
    3 7 5;
    5 7 12;
    8 12 10;
]
min_police_cars_per_shift = [10, 20, 18]
min_police_cars_per_district = [10, 14, 13]


solve_police_car_problem(min_police_cars_matrix , max_police_cars_matrix, min_police_cars_per_shift, min_police_cars_per_district)
