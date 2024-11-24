# Michał Kallas, 272398

function newtons_method(f::Function, pf::Function, x0::Float64, δ::Float64, ϵ::Float64, maxit::Int)
    v::Float64 = f(x0)

    if abs(v) < ϵ
        return x0, v, 0, 0
    end

    for it in 1:maxit
        dfx = pf(x0)

        if abs(dfx) < ϵ
            return x0, v, it, 2
        end

        x1 = x0 - (v / dfx)
        v = f(x1)

        if abs(x1 - x0) < δ || abs(v) < ϵ
            return x1, v, it, 0
        end

        x0 = x1
    end

    return x0, v, maxit, 1
end
