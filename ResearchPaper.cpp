#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <unordered_map>

using namespace std;
using namespace chrono;

// Functions required
void readNumbers(const string &filename, vector<int> &numbers);
void writeResults(const string &filename, int min, int max, double mean, double median, int mode, double stddev);
double calculateMean(const vector<int> &numbers);
double calculateMedian(vector<int> &numbers);
int calculateMode(const vector<int> &numbers);
double calculateStdDev(const vector<int> &numbers, double mean);

int main() {
    string inputFile = "input.txt";
    string outputFile = "output.txt";
    vector<int> numbers;

    // Read numbers from file
    readNumbers(inputFile, numbers);

    // Start timing
    auto start = high_resolution_clock::now();

    // Calculate stats
    sort(numbers.begin(), numbers.end());
    int min = numbers.front();
    int max = numbers.back();
    double mean = calculateMean(numbers);
    double median = calculateMedian(numbers);
    int mode = calculateMode(numbers);
    double stddev = calculateStdDev(numbers, mean);

    // End timing
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start).count();

    // Write results to file
    writeResults(outputFile, min, max, mean, median, mode, stddev);

    // Output timing information
    cout << "Computation completed in " << duration << " ms." << endl;

    return 0;
}

// Function to read numbers from a file
void readNumbers(const string &filename, vector<int> &numbers) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        exit(EXIT_FAILURE);
    }

    int num;
    while (file >> num) {
        numbers.push_back(num);
    }
    file.close();
}

// Function to write results to a file
void writeResults(const string &filename, int min, int max, double mean, double median, int mode, double stddev) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        exit(EXIT_FAILURE);
    }

    file << "Results:" << endl;
    file << "Minimum: " << min << endl;
    file << "Maximum: " << max << endl;
    file << "Mean: " << mean << endl;
    file << "Median: " << median << endl;
    file << "Mode: " << mode << endl;
    file << "Standard Deviation: " << stddev << endl;
    file.close();
}

// Function to calculate the mean
double calculateMean(const vector<int> &numbers) {
    double sum = 0;
    for (int num : numbers) {
        sum += num;
    }
    return sum / numbers.size();
}

// Function to calculate the median
double calculateMedian(vector<int> &numbers) {
    size_t size = numbers.size();
    if (size % 2 == 0) {
        return (numbers[size / 2 - 1] + numbers[size / 2]) / 2.0;
    } else {
        return numbers[size / 2];
    }
}

// Function to calculate the mode
int calculateMode(const vector<int> &numbers) {
    unordered_map<int, int> freq;
    for (int num : numbers) {
        freq[num]++;
    }

    int mode = numbers[0];
    int maxCount = 0;
    for (const auto &pair : freq) {
        if (pair.second > maxCount) {
            maxCount = pair.second;
            mode = pair.first;
        }
    }
    return mode;
}

// Function to calculate the standard deviation
double calculateStdDev(const vector<int> &numbers, double mean) {
    double variance = 0;
    for (int num : numbers) {
        variance += (num - mean) * (num - mean);
    }
    variance /= numbers.size();
    return sqrt(variance);
}
