# Michał Kallas, 272398

function difference_quotients(x::Vector{Float64}, f::Vector{Float64})
    n = length(x)
    fx = copy(f)

    for i in 2:n
        for j in n:-1:i
            fx[j] = (fx[j] - fx[j-1]) / (x[j] - x[j-i+1])
        end
    end

    return fx
end
