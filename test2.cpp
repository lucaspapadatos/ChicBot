// MAC: g++ test2.cpp -o test2 -lcurl -std=c++11
// WINDOWS: g++ -I"curl-8.10.1_6-win64-mingw\include" -L"curl-8.10.1_6-win64-mingw\lib" test2.cpp -o test2 -lcurl -std=c++11 

#include <iostream>
#include <fstream>
#include <string>
#include <curl/curl.h>
#include <vector>
#include "json.hpp"
#include <algorithm>
#include <cctype>

// For convenience
using json = nlohmann::json;

// Define attributes
enum class Color {RED, BLUE, GREEN, YELLOW, INVALID};
enum class Size {XXS, XS, S, M, L, XL, XXL, INVALID};
enum class Type {
    Shirt,
    Pants,
    Jacket,
    Shorts,
    Skirt,
    Dress,
    Sweater,
    Coat,
    Hat,
    Socks,
    Shoes,
    Scarf,
    Gloves,
    Belt,
    Underwear,
    INVALID
};
enum class Brand {
    Nike,
    Adidas,
    Puma,
    Reebok,
    UnderArmour,
    NewBalance,
    Gucci,
    LouisVuitton,
    Prada,
    Chanel,
    INVALID
};
enum class Material {
    Cotton,
    Polyester,
    Wool,
    Silk,
    Leather,
    Denim,
    Nylon,
    Linen,
    Suede,
    Spandex,
    INVALID
};

void addRowToCSV(const std::string& filename, const std::string& name,
                 const std::string& description, const std::string& color,
                 const std::string& size, const std::string& type,
                 double price, const std::string& brand,
                 const std::string& material, int quantity) {
    
    // Open the file in append mode
    std::ofstream outFile(filename, std::ios::app);
    
    if (!outFile) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
    
    // Prepare the new row
    outFile << name << "," 
            << description << ","
            << color << ","
            << size << ","
            << type << ","
            << price << ","
            << brand << ","
            << material << ","
            << quantity << "\n";

    outFile.close(); // Close the file
    std::cout << "New row added to the CSV file." << std::endl;
}

// Helper function to convert a string to lowercase
std::string toLowerCase(const std::string& str) {
    std::string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

// Case-insensitive comparison function
bool equalsIgnoreCase(const std::string& str1, const std::string& str2) {
    return toLowerCase(str1) == toLowerCase(str2);
}

// Function to convert input to color enum
Color getColorFromInput(const std::string& colorStr) {
    if (equalsIgnoreCase(colorStr, "red")) return Color::RED;
    else if (equalsIgnoreCase(colorStr, "blue")) return Color::BLUE;
    else if (equalsIgnoreCase(colorStr, "green")) return Color::GREEN;
    else if (equalsIgnoreCase(colorStr, "yellow")) return Color::YELLOW;
    return Color::INVALID;  // If the input is not a valid color
}

// Function to convert color enum to string for csv storage
std::string colorToString(Color color) {
    switch (color) {
        case Color::RED: return "RED";
        case Color::BLUE: return "BLUE";
        case Color::GREEN: return "GREEN";
        case Color::YELLOW: return "YELLOW";
        default: return "INVALID";
    }
}

// Function to convert input to size enum
Size getSizeFromInput(const std::string& sizeStr) {
    std::string lowerSizeStr = toLowerCase(sizeStr); // Convert input to lowercase
    if (lowerSizeStr == "xxs") return Size::XXS;
    else if (lowerSizeStr == "xs") return Size::XS;
    else if (lowerSizeStr == "s") return Size::S;  // Accept "small"
    else if (lowerSizeStr == "m") return Size::M; // Accept "medium"
    else if (lowerSizeStr == "l") return Size::L;   // Accept "large"
    else if (lowerSizeStr == "xl") return Size::XL;
    else if (lowerSizeStr == "xxl") return Size::XXL;

    return Size::INVALID; // If the input is not a valid size
}

// Function to convert size enum to string for csv storage
std::string sizeToString(Size size) {
    switch (size) {
        case Size::XXS: return "XXS";
        case Size::XS: return "XS";
        case Size::S: return "S";
        case Size::M: return "M";
        case Size::L: return "L";
        case Size::XL: return "XL";
        case Size::XXL: return "XXL";
        default: return "INVALID";
    }
}

// Function to convert input to type enum
Type getTypeFromInput(const std::string& typeStr) {
    if (equalsIgnoreCase(typeStr, "shirt")) return Type::Shirt;
    else if (equalsIgnoreCase(typeStr, "pants")) return Type::Pants;
    else if (equalsIgnoreCase(typeStr, "jacket")) return Type::Jacket;
    else if (equalsIgnoreCase(typeStr, "shorts")) return Type::Shorts;
    else if (equalsIgnoreCase(typeStr, "skirt")) return Type::Skirt;
    else if (equalsIgnoreCase(typeStr, "dress")) return Type::Dress;
    else if (equalsIgnoreCase(typeStr, "sweater")) return Type::Sweater;
    else if (equalsIgnoreCase(typeStr, "coat")) return Type::Coat;
    else if (equalsIgnoreCase(typeStr, "hat")) return Type::Hat;
    else if (equalsIgnoreCase(typeStr, "socks")) return Type::Socks;
    else if (equalsIgnoreCase(typeStr, "shoes")) return Type::Shoes;
    else if (equalsIgnoreCase(typeStr, "scarf")) return Type::Scarf;
    else if (equalsIgnoreCase(typeStr, "gloves")) return Type::Gloves;
    else if (equalsIgnoreCase(typeStr, "belt")) return Type::Belt;
    else if (equalsIgnoreCase(typeStr, "underwear")) return Type::Underwear;
    return Type::INVALID; // If the input is not a valid type
}

// Function to convert type enum to string for csv storage
std::string typeToString(Type type) {
    switch (type) {
        case Type::Shirt: return "Shirt";
        case Type::Pants: return "Pants";
        case Type::Jacket: return "Jacket";
        case Type::Shorts: return "Shorts";
        case Type::Skirt: return "Skirt";
        case Type::Dress: return "Dress";
        case Type::Sweater: return "Sweater";
        case Type::Coat: return "Coat";
        case Type::Hat: return "Hat";
        case Type::Socks: return "Socks";
        case Type::Shoes: return "Shoes";
        case Type::Scarf: return "Scarf";
        case Type::Gloves: return "Gloves";
        case Type::Belt: return "Belt";
        case Type::Underwear: return "Underwear";
        default: return "INVALID";
    }
}

// Function to convert input to brand enum
Brand getBrandFromInput(const std::string& brandStr) {
    if (equalsIgnoreCase(brandStr, "nike")) return Brand::Nike;
    else if (equalsIgnoreCase(brandStr, "adidas")) return Brand::Adidas;
    else if (equalsIgnoreCase(brandStr, "puma")) return Brand::Puma;
    else if (equalsIgnoreCase(brandStr, "reebok")) return Brand::Reebok;
    else if (equalsIgnoreCase(brandStr, "underarmour")) return Brand::UnderArmour;
    else if (equalsIgnoreCase(brandStr, "newbalance")) return Brand::NewBalance;
    else if (equalsIgnoreCase(brandStr, "gucci")) return Brand::Gucci;
    else if (equalsIgnoreCase(brandStr, "louisvuitton")) return Brand::LouisVuitton;
    else if (equalsIgnoreCase(brandStr, "prada")) return Brand::Prada;
    else if (equalsIgnoreCase(brandStr, "chanel")) return Brand::Chanel;
    return Brand::INVALID; // If the input is not a valid brand
}

// Function to convert brand enum to string for csv storage
std::string brandToString(Brand brand) {
    switch (brand) {
        case Brand::Nike: return "Nike";
        case Brand::Adidas: return "Adidas";
        case Brand::Puma: return "Puma";
        case Brand::Reebok: return "Reebok";
        case Brand::UnderArmour: return "UnderArmour";
        case Brand::NewBalance: return "NewBalance";
        case Brand::Gucci: return "Gucci";
        case Brand::LouisVuitton: return "LouisVuitton";
        case Brand::Prada: return "Prada";
        case Brand::Chanel: return "Chanel";
        default: return "INVALID";
    }
}

// Function to convert input to brand enum
Material getMaterialFromInput(const std::string& materialStr) {
    if (equalsIgnoreCase(materialStr, "cotton")) return Material::Cotton;
    else if (equalsIgnoreCase(materialStr, "polyester")) return Material::Polyester;
    else if (equalsIgnoreCase(materialStr, "wool")) return Material::Wool;
    else if (equalsIgnoreCase(materialStr, "silk")) return Material::Silk;
    else if (equalsIgnoreCase(materialStr, "leather")) return Material::Leather;
    else if (equalsIgnoreCase(materialStr, "denim")) return Material::Denim;
    else if (equalsIgnoreCase(materialStr, "nylon")) return Material::Nylon;
    else if (equalsIgnoreCase(materialStr, "linen")) return Material::Linen;
    else if (equalsIgnoreCase(materialStr, "suede")) return Material::Suede;
    else if (equalsIgnoreCase(materialStr, "spandex")) return Material::Spandex;
    return Material::INVALID; // If the input is not a valid material
}

// Function to convert material enum to string for csv storage
std::string materialToString(Material material) {
    switch (material) {
        case Material::Cotton: return "Cotton";
        case Material::Polyester: return "Polyester";
        case Material::Wool: return "Wool";
        case Material::Silk: return "Silk";
        case Material::Leather: return "Leather";
        case Material::Denim: return "Denim";
        case Material::Nylon: return "Nylon";
        case Material::Linen: return "Linen";
        case Material::Suede: return "Suede";
        case Material::Spandex: return "Spandex";
        default: return "INVALID";
    }
}

// Callback function to capture the response data
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    size_t totalSize = size * nmemb;
    ((std::string*)userp)->append((char*)contents, totalSize);
    return totalSize;
}

// Function to extract clothing information from the structured output API response
json extract_clothing_info(const std::string& response_string)
{
    // Parse the response JSON
    auto response_json = json::parse(response_string);
    
    // Navigate through the JSON structure
    if (response_json.contains("choices") && 
        response_json["choices"].is_array() && 
        !response_json["choices"].empty() &&
        response_json["choices"][0].contains("message") &&
        response_json["choices"][0]["message"].contains("content")) {
        
        std::string content = response_json["choices"][0]["message"]["content"];
        
        // Parse the content as JSON
        auto content_json = json::parse(content);
        
        if (content_json.is_array()) {
            // Validate each clothing item in the array
            for (const auto& item : content_json) {
                if (!(
                    item.contains("color") && item["color"].is_string() &&
                    item.contains("size") && item["size"].is_string() &&
                    item.contains("type") && item["type"].is_string() &&
                    item.contains("max_price") && item["max_price"].is_string() &&
                    item.contains("min_price") && item["min_price"].is_string() &&
                    item.contains("brand") && item["brand"].is_string() &&
                    item.contains("material") && item["material"].is_string()
                )) {
                    throw std::runtime_error("Invalid response format: One or more clothing items have missing or incorrect fields.");
                }
            }
            return content_json;
        }
    }
    
    throw std::runtime_error("Invalid response format: clothing information missing or incorrect.");
}

// Function to extract assistant's message from the conversational assistant API response
std::string extract_assistant_message(const std::string& response_string)
{
    // Parse the response JSON
    auto response_json = json::parse(response_string);
    
    // Extract the assistant's message from the response
    return response_json["choices"][0]["message"]["content"];
}

int main()
{
    try {
        // Initialize CURL once
        CURL* curl = curl_easy_init();
        if (!curl) {
            throw std::runtime_error("Failed to initialize CURL.");
        }

        // Headers
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");

        // Define the models and response_format for the structured output
        std::string structured_model = "lmstudio-community/Meta-Llama-3.1-8B-Instruct-GGUF/Meta-Llama-3.1-8B-Instruct-Q4_K_M.gguf";
        std::string response_format = R"({
            "type": "json_schema",
            "json_schema": {
                "name": "clothing_info",
                "strict": "true",
                "schema": {
                    "type": "array",
                    "items": {
                        "type": "object",
                        "properties": {
                            "color": { "type": "string" },
                            "size": { "type": "string" },
                            "type": { "type": "string" },
                            "max_price": { "type": "string" },
                            "min_price": { "type": "string" },
                            "brand": { "type": "string" },
                            "material": { "type": "string" }
                        },
                        "required": ["color", "size", "type", "max_price", "min_price", "brand", "material"]
                    }
                }
            }
        })";

        // Define the conversational assistant model
        std::string conversational_model = "your-conversational-model-name"; // Replace with your actual model name

        // Conversation history for conversational assistant
        std::vector<json> conversation_conversational = {
            {{"role", "system"}, {"content", "You are a helpful fashion assistant, your job is to take the user's clothing request and create recommendations"}}
        };

        // Conversation history for structured output
        std::vector<json> conversation_structured = {
            {{"role", "system"}, {"content", "You are a text extractor. Please extract clothing from the user's information in the requested format. For any field that the user does not specify, use NONE. Use comma separated list if multiple attributes for a field are specified."}}
        };

        while (true) {
            // Ask user for input message
            std::string user_message;
            std::cout << "Enter a clothing description (or type 'exit' to quit): ";
            std::cout << "Otherwise, type 'enter' to add clothing): ";
            std::getline(std::cin, user_message); // Get full line input from user
            std::cout << "User: " << user_message << std::endl;

            if (user_message == "exit") {
                break; // Exit the loop if the user types 'exit'
            }

            std::string user_input;
            Color user_color;
            Size user_size;
            Type user_type;
            int user_price;
            Brand user_brand;
            Material user_material;
            std::string name;
            std::string description;
            int quantity;
    

            
            if (user_message == "enter") {
                std::cout << "Enter color: ";
                std::cin >> user_input;
                user_color = getColorFromInput(user_input); 
                std::cout << colorToString(user_color) << std::endl;  

                std::cout << "Enter size: ";   
                std::cin >> user_input;
                user_size = getSizeFromInput(user_input); 
                std::cout << sizeToString(user_size) << std::endl;   

                std::cout << "Enter type of clothing: "; 
                std::cin >> user_input;
                user_type = getTypeFromInput(user_input);
                std::cout << typeToString(user_type) << std::endl;

                std::cout << "Enter price: ";
                std::cin >> user_price;
                std::cout << user_price << std::endl;

                std::cout << "Enter brand: ";   
                std::cin >> user_input;
                user_brand = getBrandFromInput(user_input);
                std::cout << brandToString(user_brand) << std::endl;

                std::cout << "Enter material: ";   
                std::cin >> user_input;
                user_material = getMaterialFromInput(user_input);
                std::cout << materialToString(user_material) << std::endl;

                std::cout << "Name: ";
                std::getline(std::cin, name);
                std::cout << name << std::endl;

                std::cout << "Description: "  << std::endl; 
                std::getline(std::cin, description);
                std::cout << description << std::endl;

                std::cout << "Enter quantity: ";   
                std::cin >> quantity;
                std::cout << quantity << std::endl;

                addRowToCSV("data.csv", name, description, colorToString(user_color), sizeToString(user_size), typeToString(user_type), user_price, brandToString(user_brand), materialToString(user_material), quantity);
            }

            // =======================
            // First API Call: Structured Output
            // =======================

            // Append the user's message to the structured conversation history
            conversation_structured.push_back({{"role", "user"}, {"content", user_message}});

            // Build the JSON payload for structured output
            json payload_structured;
            payload_structured["model"] = structured_model;
            payload_structured["messages"] = conversation_structured;
            payload_structured["response_format"] = json::parse(response_format);
            payload_structured["temperature"] = 0.0;
            payload_structured["max_tokens"] = 150;
            payload_structured["stream"] = false;

            // Convert the JSON payload to string
            std::string json_data_structured = payload_structured.dump();

            // Response string for structured output
            std::string response_string_structured;

            // Set the CURL options for structured output
            curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:1234/v1/chat/completions");
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
            curl_easy_setopt(curl, CURLOPT_POST, 1L);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_data_structured.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string_structured);

            // Perform the structured output request
            CURLcode res_structured = curl_easy_perform(curl);
            if (res_structured != CURLE_OK) {
                std::cerr << "CURL request for structured output failed: " << curl_easy_strerror(res_structured) << std::endl;
                continue; // Skip to the next iteration on failure
            }

            try {
                // Extract the clothing information from the response
                json clothing_info = extract_clothing_info(response_string_structured);
                // Append the assistant's response to the structured conversation history
                conversation_structured.push_back({{"role", "assistant"}, {"content", clothing_info.dump(4)}});

                // Display the structured clothing information
                std::cout << "\n--- Structured Clothing Information ---" << std::endl;
                for (size_t i = 0; i < clothing_info.size(); ++i) {
                    const auto& item = clothing_info[i];
                    std::cout << "Item " << (i + 1) << ":" << std::endl;
                    std::cout << "  Color: " << item["color"] << std::endl;
                    std::cout << "  Size: " << item["size"] << std::endl;
                    std::cout << "  Type: " << item["type"] << std::endl;
                    std::cout << "  Max Price: " << item["max_price"] << std::endl;
                    std::cout << "  Min Price: " << item["min_price"] << std::endl;
                    std::cout << "  Brand: " << item["brand"] << std::endl;
                    std::cout << "  Material: " << item["material"] << std::endl;
                    std::cout << "--------------------------------------" << std::endl;
                }
                std::cout << std::endl;

                // =======================
                // Second API Call: Conversational Assistant
                // =======================

                // Prepare a message for the conversational assistant using the structured data
                std::string conversational_input = "Here is the clothing information:\n" + clothing_info.dump(4) + "\nPlease provide a recommendation based on this information.";

                // Append this message to the conversational conversation history
                conversation_conversational.push_back({{"role", "user"}, {"content", conversational_input}});

                // Build the JSON payload for conversational assistant
                json payload_conversational;
                payload_conversational["model"] = conversational_model;
                payload_conversational["messages"] = conversation_conversational;
                payload_conversational["temperature"] = 0.7;
                payload_conversational["max_tokens"] = 150;
                payload_conversational["stream"] = false;

                // Convert the JSON payload to string
                std::string json_data_conversational = payload_conversational.dump();

                // Response string for conversational assistant
                std::string response_string_conversational;

                // Set the CURL options for conversational assistant
                curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:1234/v1/chat/completions"); // Replace with actual URL if different
                curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_data_conversational.c_str());
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string_conversational);

                // Perform the conversational assistant request
                CURLcode res_conversational = curl_easy_perform(curl);
                if (res_conversational != CURLE_OK) {
                    std::cerr << "CURL request for conversational assistant failed: " << curl_easy_strerror(res_conversational) << std::endl;
                    continue; // Skip to the next iteration on failure
                }

                // Extract the assistant's message and append it to the conversational history
                std::string assistant_message = extract_assistant_message(response_string_conversational);
                conversation_conversational.push_back({{"role", "assistant"}, {"content", assistant_message}});

                // Display the assistant's conversational response
                std::cout << "Assistant: " << assistant_message << "\n" << std::endl;
            }
            catch (const std::exception& ex) {
                std::cerr << "Error parsing response: " << ex.what() << std::endl;
                // Optionally, you can print the raw response for debugging
                std::cout << "Raw Response (Structured Output): " << response_string_structured << std::endl;
            }
        }

        // Clean up
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
