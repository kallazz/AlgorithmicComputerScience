# Michał Kallas, 272398

function compute_next_population(p, r)
    return p + r * p * (1 - p)
end

function run_experiment()
    r = 3
    p32 = Float32(0.01)
    p32_with_cut = Float32(0.01)
    p64 = Float64(0.01)

    println("0 & $p32 & $p32_with_cut & $p64\\\\\n\\hline")

    for i in 1:40
        p32 = compute_next_population(p32, r)
        p32_with_cut = compute_next_population(p32_with_cut, r)
        p64 = compute_next_population(p64, r)

        if i == 10
            p32_with_cut = floor(p32_with_cut, digits=3)
        end

        println("$i & $p32 & $p32_with_cut & $p64\\\\\n\\hline")
    end
end

run_experiment()
