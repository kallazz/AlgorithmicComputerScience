#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
#include <thread>
#include <vector>

std::mt19937 GENERATOR(std::random_device{}()); // Mersenne Twister generator

void zeroVector(std::vector<int> &vec, int range) {
    for (int i = 0; i < range; i++) {
        vec[i] = 0;
    }
}

void firstExperiment() {
    const int minN = 10000; // initial number of bins and balls
    const int maxN = 1000000; // final number of bins and balls
    const int incrementN = 10000;
    const int k = 50; // number of experiment repeats

    std::ofstream meansFile("means.txt");
    std::ofstream valuesFile("values.txt");

    int maxBallsInBinL1, maxBallsInBinL2, L1sum, L2sum;
    std::vector<int> binsL1(maxN, 0);
    std::vector<int> binsL2(maxN, 0);

    for (int currentN = minN; currentN <= maxN; currentN += incrementN) {
        std::cout << currentN << '\n';

        L1sum = 0;
        L2sum = 0;

        for (int i = 0; i < k; i++) {
            maxBallsInBinL1 = 0;
            maxBallsInBinL2 = 0;

            for (int j = 0; j < currentN; j++) {
                std::uniform_int_distribution<> distribution(0, currentN - 1); // [0, n - 1]

                // Ln_1
                const int binNumber = distribution(GENERATOR);
                binsL1[binNumber]++;

                if (binsL1[binNumber] > maxBallsInBinL1) {
                    maxBallsInBinL1 = binsL1[binNumber];
                }

                //Ln_2
                const int firstBinNumber = distribution(GENERATOR);
                const int secondBinNumber = distribution(GENERATOR);
                const int binWithLessBalls = (binsL2[firstBinNumber] <= binsL2[secondBinNumber]) ? firstBinNumber : secondBinNumber;
                binsL2[binWithLessBalls]++;

                if (binsL2[binWithLessBalls] > maxBallsInBinL2) {
                    maxBallsInBinL2 = binsL2[binWithLessBalls];
                }
        }

            zeroVector(binsL1, currentN);
            zeroVector(binsL2, currentN);

            L1sum += maxBallsInBinL1;
            L2sum += maxBallsInBinL2;

            valuesFile << currentN << '\t' << maxBallsInBinL1 << '\t' << maxBallsInBinL2 << '\n';
        }
        meansFile << currentN << '\t'
            << (static_cast<float>(L1sum) / k) << '\t'
            << (static_cast<float>(L2sum) / k) << '\n';
    }

    meansFile.close();
    valuesFile.close();
}

std::pair<int, int> insertionSort(std::vector<int> &vec) {
    const int n = vec.size();
    int comparisons = 0;
    int shifts = 0;

    for (int i = 1; i < n; i++) {
        int key = vec[i];
        int j = i - 1;

        comparisons++;
        while (j >= 0 && vec[j] > key) {
            comparisons++;
            vec[j + 1] = vec[j];
            shifts++;
            j--;
        }
        vec[j + 1] = key;
        shifts++;
    }

    return std::make_pair(comparisons, shifts);
}

std::vector<int> generatePermutationVector(int n) {
    std::vector<int> vec(n);
    for (int i = 0; i < n; i++) {
        vec[i] = i + 1;
    }
    std::shuffle(vec.begin(), vec.end(), GENERATOR);

    return vec;
}

void secondExperiment() {
    const int minN = 100;
    const int maxN = 10000;
    const int incrementN = 100;
    const int k = 50; // number of experiment repeats

    std::ofstream meansFile("means2.txt");
    std::ofstream valuesFile("values2.txt");

    long comparisonSum, shiftSum;

    for (int currentN = minN; currentN <= maxN; currentN += incrementN) {
        std::cout << currentN << '\n';

        comparisonSum = 0;
        shiftSum = 0;

        for (int i = 0; i < k; i++) {
            std::vector<int> randomVector = generatePermutationVector(currentN);

            const auto [comparions, shifts] = insertionSort(randomVector);
            comparisonSum += comparions;
            shiftSum += shifts;

            valuesFile << currentN << '\t' << comparions << '\t' << shifts << '\n';
        }

        meansFile << currentN << '\t'
            << (static_cast<float>(comparisonSum) / k) << '\t'
            << (static_cast<float>(shiftSum) / k) << '\n';
    }
}

int main() {
    std::thread firstExperimentThread(firstExperiment);
    std::thread secondExperimentThread(secondExperiment);

    firstExperimentThread.join();
    secondExperimentThread.join();

    return 0;
}