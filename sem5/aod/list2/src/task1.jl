# Michał Kallas, 272398

using JuMP;
import GLPK;

function solve_jet_fuel_problem(fuel_supply::Vector, fuel_demand::Vector, fuel_prices::Matrix)
    model = Model(GLPK.Optimizer)

    supply_range = 1:length(fuel_supply)
    demand_range = 1:length(fuel_demand)

    # f[s, d] is how much fuel company s is supplying to airport d
    @variable(model, f[supply_range, demand_range] >= 0)

    @constraint(model, [s in supply_range], sum(f[s, :]) <= fuel_supply[s])
    @constraint(model, [d in demand_range], sum(f[:, d]) == fuel_demand[d])

    @objective(model, Min, sum(fuel_prices[d, s] * f[s, d] for s in supply_range, d in demand_range))

    optimize!(model)

    minimal_cost = objective_value(model)
    println("Minimal cost: $minimal_cost")

    println("Fuel delivered by each company:")
    for s in supply_range
        println("Company $s: $(value(sum(f[s, :])))")
    end
end

fuel_supply_from_companies = [275000, 550000, 660000]
fuel_demand_on_airports = [110000, 220000, 330000, 440000]
fuel_prices = [10 7 8; 10 11 14; 9 12 4; 11 13 9]

solve_jet_fuel_problem(fuel_supply_from_companies, fuel_demand_on_airports, fuel_prices)
