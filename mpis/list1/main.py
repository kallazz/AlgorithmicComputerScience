import matplotlib.pyplot as plt
import numpy as np

def approximate(integral, a, b, n, M):
    x_arr = np.random.uniform(a, b, n)
    y_arr = np.random.uniform(0, M, n)
    C = sum(y_arr <= integral(x_arr))

    return C / n * (b - a) * M

def approximate_pi(n):
    x_arr = np.random.uniform(0, 1, n)
    y_arr = np.random.uniform(0, 1, n)
    C = sum(x_arr**2 + y_arr**2 <= 1)

    return C / n * 4

def findM(integral, a, b):
    M = 0
    loop_range = (b - a) * 1000
    i = 0
    x = a

    while i < loop_range:
        if (integral(x) > M):
            M = integral(x)
        i += 1
        x += 0.001

    return M

# Function definitions
def f(x):
    return x**(1/3)

def g(x):
    return np.sin(x)

def h(x):
    return 4 * x * (1 - x)**3

# Consts related to the integrals
INTEGRATION_LIMITS = [(0, 8), (0, np.pi), (0, 1)]
EXACT_INTEGRAL_VALUES = (12, 2, 0.2)
INTEGRAL_FORMULAS = (r"$\int_{0}^{8} \sqrt[3]{x} \,dx$", r"$\int_{0}^{\pi} \sin(x) \,dx$",
                     r"$\int_{0}^{1} 4x(1-x)^3 \,dx$")

def create_plot(n_arr, approximation_results, mean_results, formula, exact_value, plot_index):
    plt.figure()
    plt.title('Monte Carlo Approximation of ' + formula)
    plt.xlabel('Number of random points(n)')
    plt.ylabel('Value')

    for j in range(len(n_arr)):
        plt.scatter([n_arr[j]] * k, approximation_results[j], color='mediumblue', alpha=0.5, s=5, zorder=0)
    plt.scatter(n_arr, mean_results, color='red', s=20, zorder=1)
    plt.axhline(exact_value, color='lime', linewidth=2.5, zorder=2)

    legend_shapes = [plt.Line2D([0], [0], color='mediumblue', marker='o', linestyle='None'),
                     plt.Line2D([0], [0], color='red', marker='o', linestyle='None'),
                     plt.Line2D([0], [0], color='lime', lw=4)]
    plt.legend(legend_shapes, ['Approximation',
                               'Mean of the approximations for specific n',
                               'Actual value'])
    plt.xlim(0, 5000)
    plt.xticks(np.arange(0, 5001, 500))
    plt.grid()
    plt.tight_layout()
    plt.savefig('./plots/plot' + str(plot_index) + '.png')
    plt.show()

if __name__ == "__main__":
    n_arr = [n for n in range(50, 5001, 50)]
    k = 50

    # f(x)dx, g(x)dx, h(x)dx approximation
    for i, integral in enumerate([f, g, h]):
        a = INTEGRATION_LIMITS[i][0]
        b = INTEGRATION_LIMITS[i][1]
        M = findM(integral, a, b)
        approximation_results = np.zeros((len(n_arr), k))

        for j, n in enumerate(n_arr):
            for l in range(k):
                approximation_results[j][l] = approximate(integral, a, b, n, M)

        mean_results = np.mean(approximation_results, axis=1)

        create_plot(n_arr, approximation_results, mean_results, INTEGRAL_FORMULAS[i], EXACT_INTEGRAL_VALUES[i], i)

    # π approximation
    approximation_results = np.zeros((len(n_arr), k))
    for i, n in enumerate(n_arr):
        for j in range(k):
            approximation_results[i][j] = approximate_pi(n)

    mean_results = np.mean(approximation_results, axis=1)

    create_plot(n_arr, approximation_results, mean_results, 'π', np.pi, 3)
