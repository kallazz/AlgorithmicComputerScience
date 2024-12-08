# Michał Kallas, 272398

function natural_form(x::Vector{Float64}, fx::Vector{Float64})
    n = length(x)
    a = zeros(Float64, n)

    a[n] = fx[n]

    for i in n-1:-1:1
        a[i] = fx[i] - x[i] * a[i+1]
        for j in i+1:n-1
            a[j] += -x[i] * a[j+1]
        end
    end

    return a
end
