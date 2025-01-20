/*
 * MIT License
 * 
 * Copyright (c) 2025 Dilyan Grigorov
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <cctype>

// Function to encode a URL properly
// Converts non-alphanumeric characters into their percent-encoded equivalents
std::string encodeUrl(const std::string& url) {
    std::ostringstream encodedUrl;
    for (const auto& ch : url) {
        // Check if the character is alphanumeric or a safe symbol, and append it as is
        if (isalnum(ch) || ch == '-' || ch == '_' || ch == '.' || ch == '~') {
            encodedUrl << ch;
        } else {
            // Encode other characters as % followed by their hexadecimal representation
            encodedUrl << '%' << std::uppercase << std::hex << static_cast<int>(static_cast<unsigned char>(ch));
        }
    }
    return encodedUrl.str();
}

// Function to generate a sitemap XML file
// Takes a vector of URLs and the name of the output file as arguments
void generateSitemap(const std::vector<std::string>& urls, const std::string& outputFileName) {
    std::ofstream outputFile(outputFileName);

    // Check if the output file was opened successfully
    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open the output file: " << outputFileName << std::endl;
        return;
    }

    // Write the XML header and opening tags for the sitemap
    outputFile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    outputFile << "<urlset xmlns=\"http://www.sitemaps.org/schemas/sitemap/0.9\">\n";

    // Loop through each URL, encode it, and add it to the sitemap
    for (const auto& url : urls) {
        outputFile << "  <url>\n";
        outputFile << "    <loc>" << encodeUrl(url) << "</loc>\n";
        outputFile << "  </url>\n";
    }

    // Write the closing tag for the sitemap
    outputFile << "</urlset>\n";
    outputFile.close();
}

// Function to read URLs from an input file
// Each line in the file is treated as a separate URL
std::vector<std::string> readUrlsFromFile(const std::string& inputFileName) {
    std::ifstream inputFile(inputFileName);
    std::vector<std::string> urls;
    std::string line;

    // Check if the input file was opened successfully
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the input file: " << inputFileName << std::endl;
        return urls;
    }

    // Read each line from the file and add it to the vector of URLs
    while (std::getline(inputFile, line)) {
        if (!line.empty()) {
            urls.push_back(line);
        }
    }

    inputFile.close();
    return urls;
}

// Main function to execute the program
// Takes two command-line arguments: input file name and output file name
int main(int argc, char* argv[]) {
    // Check if the correct number of arguments are provided
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
        return 1;
    }

    std::string inputFileName = argv[1]; // Input file containing URLs
    std::string outputFileName = argv[2]; // Output file for the sitemap

    // Read URLs from the input file
    auto urls = readUrlsFromFile(inputFileName);
    if (urls.empty()) {
        std::cerr << "No URLs found in the input file." << std::endl;
        return 1;
    }

    // Generate the sitemap file with the given URLs
    generateSitemap(urls, outputFileName);
    return 0;
}
