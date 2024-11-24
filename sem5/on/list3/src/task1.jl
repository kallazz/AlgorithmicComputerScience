# Michał Kallas, 272398

function bisection_method(f::Function, a::Float64, b::Float64, δ::Float64, ϵ::Float64)
    fa::Float64 = f(a)
    fb::Float64 = f(b)
    e::Float64 = b - a
    it::Int = 0

    if sign(fa) == sign(fb)
        return Nothing, Nothing, Nothing, 1
    end

    while true
        it += 1
        e /= 2
        r = a + e
        v = f(r)

        if abs(e) < δ || abs(v) < ϵ
            return r, v, it, 0
        end

        if sign(v) != sign(fa)
            b = r
            fb = v
        else
            a = r
            fa = v
        end
    end
end
