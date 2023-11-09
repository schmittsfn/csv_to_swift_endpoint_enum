//
//  enumGenerator.cpp
//  
//
//  Created by Stefan Schmitt on 09/10/2023.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

struct Endpoint {
    std::string name;
    std::string url;
    std::string method;
    
    Endpoint(const std::string& _name, const std::string& _url, const std::string& _method)
            : name(_name), url(_url), method(_method) {}
};

// Function to parse a CSV file and store the data in a vector of Endpoint structs
std::vector<Endpoint> parseCSV(const std::string& filename) {
    std::vector<Endpoint> endpoints;
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        // Skip the header line if present
        std::getline(file, line);
        
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string name, url, method;
            // Assuming CSV format: url, method
            if (std::getline(iss, name, ',') && std::getline(iss, url, ',') && std::getline(iss, method, ',')) {
                endpoints.push_back(Endpoint(name, url, method));
            }
        }
        file.close();
        
    } else {
        std::cout << "Error opening file." << std::endl;
    }
    return endpoints;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " input.csv > output.swift" << std::endl;
        return 1;
    }

    const std::string inputFilename = argv[1];
    
    const std::vector<Endpoint> endpoints = parseCSV(inputFilename);
    // Generate the Swift enum code
    std::cout << "// auto generated using csv_to_swift_enum" << std::endl;
    std::cout << std::endl;
    std::cout << "import AsyncHTTPClient" << std::endl;
    std::cout << "import NIOHTTP1" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "public enum Endpoint {" << std::endl;
    for (const Endpoint& endpoint : endpoints) {
        std::cout << "    case " << endpoint.name << std::endl;
    }
    
    std::cout << std::endl;
    
    std::cout << "    var url: String {" << std::endl;
    std::cout << "        switch self {" << std::endl;
    
    for (const Endpoint& endpoint : endpoints) {
        std::cout << "        case ." << endpoint.name << ": return \"" << endpoint.url << "\"" << std::endl;
    }
    std::cout << "        }" << std::endl;
    std::cout << "    }" << std::endl;
    
    std::cout << "    var httpMethod: HTTPMethod {" << std::endl;
    std::cout << "        switch self {" << std::endl;
    for (const Endpoint& endpoint : endpoints) {
        std::cout << "        case ." << endpoint.name << ": return ." << endpoint.method << std::endl;
    }
    std::cout << "        }" << std::endl;
    std::cout << "    }" << std::endl;
    
    std::cout << "    func requestBody() -> HTTPClient.Body? {" << std::endl;
    std::cout << "        switch self {" << std::endl;
    for (const Endpoint& endpoint : endpoints) {
        std::cout << "        case ." << endpoint.name << ": return nil" << std::endl;
    }
    std::cout << "        }" << std::endl;
    std::cout << "    }" << std::endl;
    
    std::cout << "}" << std::endl;
    return 0;
}
