import matplotlib.pyplot as plt
import numpy as np

if __name__ == "__main__":
    n_arr = [n for n in range(1000, 100001, 1000)] # numbers of bins
    k = 50 # number of experiment repeats

    C_n_values = []
    for current_n in n_arr:
        print(current_n)
        B_n_sum = 0
        U_n_sum = 0
        C_n_sum = 0
        D_n_sum = 0

        b_file = open('B_n_values_.txt', 'a')
        u_file = open('U_n_values_.txt', 'a')
        c_file = open('C_n_values.txt', 'a')
        d_file = open('D_n_values_.txt', 'a')
        dc_file = open('D_C_n_values_.txt', 'a')

        for i in range(k):
            bins = np.zeros(current_n, dtype=int)
            number_of_balls = 0
            temp_C_number_of_balls = 0
            ballsCollided = False
            oneBallInEachBin = False
            empty_bins = current_n
            bins_with_less_than_two_balls = current_n
            while True:
                number_of_balls += 1
                binNumber = np.random.randint(0, current_n) # [0, n - 1]
                bins[binNumber] += 1

                # B_n
                if not ballsCollided and bins[binNumber] > 1:
                    B_n_sum += number_of_balls
                    b_file.write(str(number_of_balls) + '\n')
                    ballsCollided = True

                if bins[binNumber] == 1:
                    empty_bins -= 1
                elif bins[binNumber] == 2:
                    bins_with_less_than_two_balls -= 1

                # U_n
                if number_of_balls == current_n:
                    U_n_sum += empty_bins
                    u_file.write(str(empty_bins) + '\n')

                if not oneBallInEachBin:
                    # C_n
                    if empty_bins == 0:
                        C_n_sum += number_of_balls
                        temp_C_number_of_balls = number_of_balls
                        c_file.write(str(number_of_balls) + '\n')
                        oneBallInEachBin = True
                else:
                    # D_n
                    if bins_with_less_than_two_balls == 0:
                        D_n_sum += number_of_balls
                        d_file.write(str(number_of_balls) + '\n')
                        dc_file.write(str(number_of_balls - temp_C_number_of_balls) + '\n')
                        break

        b_file.write(str(B_n_sum / k) + '\n')
        u_file.write(str(U_n_sum / k) + '\n')
        c_file.write(str(C_n_sum / k) + '\n')
        d_file.write(str(D_n_sum / k) + '\n')
        dc_file.write(str((D_n_sum - C_n_sum) / k) + '\n')

    b_file.close()
    u_file.close()
    c_file.close()
    d_file.close()
    dc_file.close()
