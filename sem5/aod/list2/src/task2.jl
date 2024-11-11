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

    n = length(product_profits)
    m = length(machine_costs)
    products_range = 1:n
    machines_range = 1:m

    machine_availibility_times_in_mins = machine_availibility_times * 60.0
    machine_costs_per_minute = machine_costs / 60.0

    # zyski - koszty materiałowe dla produktów
    product_actual_profits = product_profits .- product_costs

    # x[p] to ilość wyprodukowanych kg produktu p
    @variable(model, x[products_range] >= 0)

    # maszyny produkują maksymalnie tyle ile można sprzedać
    @constraint(model, x .<= product_demands)
    # maszyny nie mogą pracować dłużej niż są dostępne
    @constraint(model, [m in machines_range], sum(x[p] * machine_product_creation_times[p, m] for p in products_range) <= machine_availibility_times_in_mins[m])

    # maksymalizujemy zysk = wyprodukowane produkty - koszty materiałowe - koszty maszyn
    @objective(model, Max,
        sum(x .* product_actual_profits) - sum(sum(x[p] * machine_product_creation_times[p, m] for p in products_range) * machine_costs_per_minute[m] for m in machines_range))
    optimize!(model)

    println("Amount of produced products: $(value.(x))")
    println("Profit: $(objective_value(model))")
end

product_profits = [9, 7, 6, 5]
product_costs = [4, 1, 1, 1]
product_demands = [400, 100, 150, 500]
machine_costs = [2, 2, 3]
machine_product_creation_times = [5 10 6; 3 6 4; 4 5 3; 4 2 1]
machine_availibility_times = [60, 60, 60]

solve_production_problem(product_profits, product_costs, product_demands, machine_costs, machine_product_creation_times, machine_availibility_times)
