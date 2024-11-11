# Michał Kallas, 272398

using JuMP;
import GLPK;

function solve_jet_fuel_problem(fuel_supply::Vector, fuel_demand::Vector, fuel_prices::Matrix)
    model = Model(GLPK.Optimizer)

    n = length(fuel_supply)
    m = length(fuel_demand)
    supply_range = 1:n
    demand_range = 1:m

    # x[f, l] to wysyłane paliwo z firmy f do lotniska l
    @variable(model, x[supply_range, demand_range] >= 0)

    # firmy nie przekraczają swoich zasobów
    @constraint(model, [s in supply_range], sum(x[s, :]) <= fuel_supply[s])
    # musi być osiągnięte zapotrzebowanie
    @constraint(model, [d in demand_range], sum(x[:, d]) == fuel_demand[d])

    # koszt ma być jak najmniejszy
    @objective(model, Min, sum(fuel_prices[d, s] * x[s, d] for s in supply_range, d in demand_range))

    optimize!(model)

    minimal_cost = objective_value(model)
    println("Minimal cost: $minimal_cost")

    println("Fuel delivered to airpots by companies:")
    display(value.(x))

    println("Sum of fuel delivered by each company:")
    for s in supply_range
        println("Company $s: $(value(sum(x[s, :])))")
    end
end

fuel_supply_from_companies = [275000, 550000, 660000]
fuel_demand_on_airports = [110000, 220000, 330000, 440000]
fuel_prices = [10 7 8; 10 11 14; 9 12 4; 11 13 9]

solve_jet_fuel_problem(fuel_supply_from_companies, fuel_demand_on_airports, fuel_prices)
