# Michał Kallas, 272398

using JuMP;
import GLPK;

function solve_production_and_storage_problem(
    production_costs_per_unit::Vector,
    production_costs_per_additional_unit::Vector,
    max_basic_units_to_produce::Vector,
    max_additional_units_to_produce::Vector,
    demand_in_units::Vector,
    initial_units_in_storage::Int,
    max_units_in_storage::Int,
    storage_cost_per_unit::Int,
)
    model = Model(GLPK.Optimizer)

    K = length(production_costs_per_unit) # ilość okresów

    # x[j] to ilość wyprodukowanych produktów w trybie normalnej produkcji
    @variable(model, x[1:K] >= 0, Int)
    # y[j] to ilość wyprodukowanych produktów w trybie ponadwymiarowej produkcji
    @variable(model, y[1:K] >= 0, Int)
    # m[j] to ilość wyprodukowanych produktów przechowywanych w magazynie na koniec okresu j - 1
    @variable(model, m[1:K+1] >= 0, Int)

    # nie produkujemy za dużo w trybie normalnym
    @constraint(model, x .<= max_basic_units_to_produce)
    # nie produkujemy za dużo w trybie ponadwymiarowym
    @constraint(model, y .<= max_additional_units_to_produce)

    # magazyn na początku ma określoną ilość produktów
    @constraint(model, m[1] == initial_units_in_storage)
    # magazyn na końcu zero produktów
    @constraint(model, m[K + 1] == 0)
    # w magazynie nie można przechowywać za dużo produktów
    @constraint(model, m .<= max_units_in_storage)

    # nie produkujemy więcej niż potrzebne
    @constraint(model, x .+ y .+ m[1:K] .- m[2:K+1] .== demand_in_units)

    # minimalizujemy koszt produkcji i przechowywania
    @objective(model, Min, sum(production_costs_per_unit .* x) + sum(production_costs_per_additional_unit .* y) + sum(storage_cost_per_unit .* m[2:K+1]))

    optimize!(model)

    println("Cost: $(objective_value(model))")
    println("Basic units produced: $(value.(x))")
    println("Additional units produced: $(value.(y))")
    println("Stored units: $(value.(m))")
end

production_costs_per_unit = [6000, 4000, 8000, 9000]
production_costs_per_additional_unit = [8000, 6000, 10000, 11000]
max_basic_units_to_produce = [100, 100, 100, 100]
max_additional_units_to_produce = [60, 65, 70, 60]
demand_in_units = [130, 80, 125, 195]
initial_units_in_storage = 15
max_units_in_storage = 70
storage_cost_per_unit = 1500

solve_production_and_storage_problem(
    production_costs_per_unit,
    production_costs_per_additional_unit,
    max_basic_units_to_produce,
    max_additional_units_to_produce,
    demand_in_units,
    initial_units_in_storage,
    max_units_in_storage,
    storage_cost_per_unit
)
