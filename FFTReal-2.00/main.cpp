#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include "FFTReal.h" // Include the FFTReal header file


// Function to generate random numbers with a specified mean and standard deviation
std::vector<double> generateRandomNumbers(double mean, double stddev, int count) {
    // Create random number generator engine
    std::random_device rd;
    std::mt19937 gen(rd());

    // Create normal distribution with mean and standard deviation
    std::normal_distribution<double> dist(mean, stddev);

    // Generate random numbers from the distribution
    std::vector<double> randomNumbers(count);
    for (int i = 0; i < count; ++i) {
        randomNumbers[i] = dist(gen);
    }

    return randomNumbers;
}

int main() {
    const long signalLength = 1024; // Signal length for FFT
    FFTReal<double> fft(signalLength); // Instantiate FFTReal with double precision

    // Mean and standard deviation for random signal generation
    double mean = 0.0;
    double stddev = 1.0;
    int count = signalLength; // Number of random samples

    // Generate random signal
    std::vector<double> randomSignal = generateRandomNumbers(mean, stddev, count);

    // Save the generated signal to a file (optional)
    std::ofstream outFile("random_signal.txt");
    if (outFile.is_open()) {
        for (size_t i = 0; i < randomSignal.size(); ++i) {
            outFile << randomSignal[i] << std::endl;
        }
        outFile.close();
        std::cout << "Random signal saved to 'random_signal.txt'" << std::endl;
    } else {
        std::cerr << "Unable to open file for writing!" << std::endl;
        return 1;
    }

    // Perform FFT
    const int numFFTComponents = signalLength / 2 + 1; // Number of FFT components (DC + Nyquist + positive frequencies)
    double fftResult[numFFTComponents]; // Array to store FFT result

    fft.do_fft(fftResult, randomSignal.data()); // Pass pointer to the data

    // Print the first few FFT components (magnitude or complex values as needed)
    const int numComponentsToPrint = 10;
    std::cout << "FFT coefficients:" << std::endl;
    for (int i = 0; i < numComponentsToPrint; ++i) {
        std::cout << "Component " << i << ": " << fftResult[i] << std::endl;
    }

  
    // Your program logic goes here

    std::cout << "Press enter to exit...";
    std::cin.get(); // Wait for user to press enter

    return 0;

}
