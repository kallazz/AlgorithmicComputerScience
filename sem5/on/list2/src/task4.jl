# Michał Kallas, 272398

using Polynomials

function run_experiment(modify_coefficient::Bool)
    coefficients = [
        1, -210.0, 20615.0, -1256850.0,
        53327946.0, -1672280820.0, 40171771630.0, -756111184500.0,
        11310276995381.0, -135585182899530.0,
        1307535010540395.0, -10142299865511450.0,
        63030812099294896.0, -311333643161390640.0,
        1206647803780373360.0, -3599979517947607200.0,
        8037811822645051776.0, -12870931245150988800.0,
        13803759753640704000.0, -8752948036761600000.0,
        2432902008176640000.0
    ]
    if modify_coefficient
        coefficients[2] -= 2^(-23)
    end
    coefficients = reverse(coefficients)

    P = Polynomial(coefficients)
    p = fromroots(1:20)

    P_roots = roots(P)

    for k in 1:20
        current_root = P_roots[k]
        println("$k & $current_root & $(abs(P(current_root))) & $(abs(p(current_root))) & $(abs(current_root - k))\\\\\n\\hline")
    end

    println()
    for k in 1:20
        println("$k & $(abs(P(k))) & $(abs(p(k)))\\\\\n\\hline")
    end
end

run_experiment(false)
println()
run_experiment(true)
