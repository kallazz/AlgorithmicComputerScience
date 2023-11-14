#include <iostream>
#include <random>
#include <fstream>
#include <vector>

int main() {
    const int minN = 1000; // initial number of bins
    const int maxN = 100000; // final number of bins
    const int k = 50; // number of experiment repeats

    int B_n, U_n, C_n, D_n;
    int B_nSum, U_nSum, C_nSum, D_nSum;
    std::ofstream meansFile("means.txt");
    std::ofstream valuesFile("values.txt");

    std::mt19937 generator(std::random_device{}());

    for (int currentN = minN; currentN <= maxN; currentN += 1000) {
        std::cout << currentN << '\n';
        B_nSum = 0;
        U_nSum = 0;
        C_nSum = 0;
        D_nSum = 0;

        for (int i = 0; i < k; i++) {
            std::vector<int> bins(currentN, 0);
            std::uniform_int_distribution<> distribution(0, currentN - 1); // [0, n - 1]

            int numberOfBalls = 0;
            bool ballsCollided = false;
            bool oneBallInEachBin = false;
            int emptyBins = currentN;
            int binsWithLessThanTwoBalls = currentN;
            while (true) {
                numberOfBalls++;
                const int binNumber = distribution(generator);
                bins[binNumber]++;

                // B_n
                if (!ballsCollided && bins[binNumber] > 1) {
                    B_n = numberOfBalls;
                    B_nSum += B_n;
                    ballsCollided = true;
                }

                if (bins[binNumber] == 1) {
                    emptyBins--;
                }
                else if (bins[binNumber] == 2) {
                    binsWithLessThanTwoBalls--;
                }

                // U_n
                if (numberOfBalls == currentN) {
                    U_n = emptyBins;
                    U_nSum += U_n;
                }

                if (!oneBallInEachBin) {
                    // C_n
                    if (emptyBins == 0) {
                        C_n = numberOfBalls;
                        C_nSum += C_n;
                        oneBallInEachBin = true;
                    }
                }
                else {
                    // D_n
                    if (binsWithLessThanTwoBalls == 0) {
                        D_n = numberOfBalls;
                        D_nSum += D_n;
                        break;
                    }
                }
            }
            valuesFile << currentN << '\t' << B_n << '\t' << U_n << '\t' << C_n
                << '\t' << D_n << '\t' << (D_n - C_n) << '\n';
        }

        meansFile << currentN << '\t'
            << (static_cast<float>(B_nSum) / k) << '\t'
            << (static_cast<float>(U_nSum) / k) << '\t'
            << (static_cast<float>(C_nSum) / k) << '\t'
            << (static_cast<float>(D_nSum) / k) << '\t'
            << (static_cast<float>(D_nSum - C_nSum) / k) << '\n';
    }

    meansFile.close();
    valuesFile.close();

    return 0;
}