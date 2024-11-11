using JuMP
using GLPK

function solve(cities_amount::Int, starting_city::Int, ending_city::Int, max_time::Int,
	arch_exists_matrix::Matrix, arch_costs_matrix::Matrix, arch_times_matrix::Matrix)

	model = Model(GLPK.Optimizer)
	set_silent(model)

	# Czy łuk użyty?
	@variable(model, 0 <= arch_used[1:cities_amount, 1:cities_amount] <= 1 , Int)

	# Jak nie ma połączenia to nie
	for i in 1:cities_amount, j in 1:cities_amount
		if arch_exists_matrix[i, j] == 0
			@constraint(model, arch_used[i, j] == 0)
		end
	end

	# Wylatujemy ze startu i wlatujemy do celu
	@constraint(model, vec(sum(arch_used, dims = 2))[starting_city] == 1)
	@constraint(model, vec(sum(arch_used, dims = 1))[ending_city] == 1)

	# Dla każdego innego miasta - # połączeń wchodzących = # połączeń wychodzących
	for i in 1:cities_amount
		if i != starting_city && i != ending_city
			@constraint(model, vec(sum(arch_used, dims = 1))[i] == vec(sum(arch_used, dims = 2))[i])
		end
	end

	# Nie przekraczamy czasu
	@constraint(model, sum(arch_used .* arch_times_matrix) <= max_time)

	# Minimalny koszt
	@objective(model, Min, sum(arch_used .* arch_costs_matrix))

	optimize!(model)

	if termination_status(model) == MOI.OPTIMAL
		println("Użyte połączenia")
		for i in 1:cities_amount, j in 1:cities_amount
			if value.(arch_used[i, j]) == 1
				println(" - [$i, $j, $(arch_costs_matrix[i, j]), $(arch_times_matrix[i, j])]")
			end
		end
		println(value.(arch_used))
		println("Czas")
		println(sum(value.(arch_used) .* arch_times_matrix))
		println("Koszt")
		println(objective_value(model))
	elseif termination_status(model) == MOI.INFEASIBLE
		println("The model is infeasible. Check the constraints or data for inconsistencies.")
		return nothing
	else
		println("Solver did not find an optimal solution.")
		return nothing
	end
end

cities_amount = 10
starting_city = 1
ending_city = 10
max_time = 15
arches = [1, 2, 1, 3], [2, 3, 2, 2], [3, 10, 3, 5], [1, 4, 1, 10], [4, 10, 1, 6]

#= max_time = 12
arches = [[1, 2, 5, 4], [2, 3, 4, 2], [3, 10, 7, 6], [1, 4, 6, 5], [4, 10, 4, 8]] 
max_time = 15
arches = [[1, 2, 3, 4], [1, 3, 4, 9], [1, 4, 7, 10], [1, 5, 8, 12], [2, 3, 2, 3], [3, 4, 4, 6], [3, 5, 2, 2], [3, 10, 6, 11],
	[4, 5, 1, 1], [4, 7, 3, 5], [5, 6, 5, 6], [5, 7, 3, 3], [5, 10, 5, 8], [6, 1, 5, 8], [6, 7, 2, 2], [6, 10, 7, 11],
	[7, 3, 4, 6], [7, 8, 3, 5], [7, 9, 1, 1], [8, 9, 1, 2], [9, 10, 2, 2]] =#
arch_exists_matrix = zeros(cities_amount, cities_amount)
arch_costs_matrix = zeros(cities_amount, cities_amount)
arch_times_matrix = zeros(cities_amount, cities_amount)

for arch in arches
	arch_exists_matrix[arch[1], arch[2]] = 1
	arch_costs_matrix[arch[1], arch[2]] = arch[3]
	arch_times_matrix[arch[1], arch[2]] = arch[4]
end

solve(cities_amount, starting_city, ending_city, max_time, arch_exists_matrix, arch_costs_matrix, arch_times_matrix)
