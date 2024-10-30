# Michał Kallas, 272398

using JuMP;
import GLPK;

function solve_production_problem(
    product_profits::Vector,
    product_costs::Vector,
    product_demands::Vector,
    machine_costs::Vector,
    machine_product_creation_times::Matrix,
    machine_availibility_times::Vector
)
    model = Model(GLPK.Optimizer)

    products_range = 1:length(product_profits)
    machines_range = 1:length(machine_costs)

    # x[p] is how many kg of product p was produced
    @variable(model, x[products_range] >= 0)

    @constraint(model, [p in products_range], x[p] <= product_demands[p])
    # entry will be created for each machine thanks to second arg [m in machines_range]
    @constraint(model, [m in machines_range], sum(x[p] * machine_product_creation_times[p, m] for p in products_range) <= machine_availibility_times[m])

    @objective(model, Max,
        sum(x[p] * product_profits[p] - product_costs[p] for p in products_range) -
        sum(x[p] * machine_product_creation_times[p, m] * machine_costs[m] for p in products_range, m in machines_range))

    optimize!(model)

    println(value.(x))
end

product_profits = [9, 7, 6, 5]
product_costs = [4, 1, 1, 1]
product_demands = [400, 100, 150, 500]
machine_costs = [2, 2, 3]
machine_product_creation_times = [5 10 6; 3 6 4; 4 5 3; 4 2 1]
machine_availibility_times = [60, 60, 60]

solve_production_problem(product_profits, product_costs, product_demands, machine_costs, machine_product_creation_times, machine_availibility_times)
