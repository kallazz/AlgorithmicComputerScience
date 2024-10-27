# Michał Kallas, 272398

function is_invertible(number::Float64)
    return number * (Float64(1.0) / (number)) == 1
end

function find_smallest_uninvertible_number(range::Pair)
    smallest_uninvertible_number::Float64 = range.first
    smallest_uninvertible_number = nextfloat(smallest_uninvertible_number)

    while smallest_uninvertible_number < range.second && is_invertible(smallest_uninvertible_number)
        smallest_uninvertible_number = nextfloat(smallest_uninvertible_number)
    end

    if smallest_uninvertible_number >= range.second
        return nothing
    end

    return smallest_uninvertible_number
end

found_number = find_smallest_uninvertible_number(Pair(1.0, 2.0))

println("Smallest uninvertible number in range (1.0, 2.0) is $found_number")
