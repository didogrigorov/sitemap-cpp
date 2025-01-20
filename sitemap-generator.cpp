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
std::string encodeUrl(const std::string& url) {
    std::ostringstream encodedUrl;
    for (const auto& ch : url) {
        if (isalnum(ch) || ch == '-' || ch == '_' || ch == '.' || ch == '~') {
            encodedUrl << ch;
        } else {
            encodedUrl << '%' << std::uppercase << std::hex << static_cast<int>(static_cast<unsigned char>(ch));
        }
    }
    return encodedUrl.str();
}

void generateSitemap(const std::vector<std::string>& urls, const std::string& outputFileName) {
    std::ofstream outputFile(outputFileName);

    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open the output file: " << outputFileName << std::endl;
        return;
    }

    outputFile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    outputFile << "<urlset xmlns=\"http://www.sitemaps.org/schemas/sitemap/0.9\">\n";

    for (const auto& url : urls) {
        outputFile << "  <url>\n";
        outputFile << "    <loc>" << encodeUrl(url) << "</loc>\n";
        outputFile << "  </url>\n";
    }

    outputFile << "</urlset>\n";
    outputFile.close();
}

std::vector<std::string> readUrlsFromFile(const std::string& inputFileName) {
    std::ifstream inputFile(inputFileName);
    std::vector<std::string> urls;
    std::string line;

    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the input file: " << inputFileName << std::endl;
        return urls;
    }

    while (std::getline(inputFile, line)) {
        if (!line.empty()) {
            urls.push_back(line);
        }
    }

    inputFile.close();
    return urls;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
        return 1;
    }

    std::string inputFileName = argv[1];
    std::string outputFileName = argv[2];

    auto urls = readUrlsFromFile(inputFileName);
    if (urls.empty()) {
        std::cerr << "No URLs found in the input file." << std::endl;
        return 1;
    }

    generateSitemap(urls, outputFileName);
    return 0;
}
