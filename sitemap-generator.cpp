#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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
        outputFile << "    <loc>" << url << "</loc>\n";
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
