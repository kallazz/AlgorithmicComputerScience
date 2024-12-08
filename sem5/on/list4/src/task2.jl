# Michał Kallas, 272398

function newtons_polynomial(x::Vector{Float64}, fx::Vector{Float64}, t::Float64)
    n = length(x)
    nt = fx[n]

    for i in n-1:-1:1
        nt = nt * (t - x[i]) + fx[i]
    end

    return nt
end