#ifndef CONFIG_PARSE_H
#define CONFIG_PARSE_H

#include <yaml-cpp/yaml.h>
#include <iostream>

//Struct for config parameters
struct ConfigProperties
{   
    double dropout_rate;
    double learning_rate;
    bool with_bias;
    int epochs;
    int output_stepsize; 
    int classes;
    
    std::string G_path;
    std::string labels_path;
    std::string features_path;
    std::vector<int> hidden_dims;
};

//Function to parse config file
ConfigProperties ParseConfig(const std::string& config_path){
    YAML::Node config = YAML::LoadFile(config_path);
    std::cout << "Using config in path: " << config_path << std::endl;

    ConfigProperties config_properties;
    config_properties.dropout_rate = config["model"]["dropout_rate"].as<double>();
    config_properties.learning_rate = config["trainer"]["learning_rate"].as<double>();
    config_properties.with_bias = config["model"]["with_bias"].as<bool>();
    config_properties.epochs = config["trainer"]["epochs"].as<int>();
    config_properties.output_stepsize = config["trainer"]["output_stepsize"].as<int>();
    config_properties.classes = config["model"]["classes"].as<int>();
    config_properties.G_path = config["data"]["G_path"].as<std::string>();
    config_properties.labels_path = config["data"]["labels_path"].as<std::string>();
    config_properties.features_path = config["data"]["features_path"].as<std::string>();
    config_properties.hidden_dims = config["model"]["hidden_dims"].as<std::vector<int>>();

    return config_properties;
}

#endif