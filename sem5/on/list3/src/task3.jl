# Michał Kallas, 272398

function secant_method(f::Function, x0::Float64, x1::Float64, δ::Float64, ϵ::Float64, maxit::Int)
    fx0::Float64 = f(x0)
    fx1::Float64 = f(x1)

    for it in 1:maxit
        if abs(fx0) > abs(fx1)
            x0, x1 = x1, x0
            fx0, fx1 = fx1, fx0
        end
        
        s::Float64 = (x1 - x0) / (fx1 - fx0)
        x1 = x0
        fx1 = fx0
        x0 = x0 - fx0 * s
        fx0 = f(x0)
        
        if abs(x1 - x0) < δ || abs(fx0) < ϵ
            return x0, fx0, it, 0
        end
    end
    
    return x0, fx0, maxit, 1
end
