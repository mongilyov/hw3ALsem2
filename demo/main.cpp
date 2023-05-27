#include <HandleFunctions.hpp>

int main(int argc, char** argv) {
    po::options_description desc("General options");
    desc.add_options()
            ("help,h", "Show help")
            ("type,t", po::value<std::string>(), "Cipher type: block or stream")
            ("cipher,c", "Cipher mode")
            ("decipher,d", "Decipher mode")
            ("key,k", po::value<std::string>(), "Select path to key")
            ("file,f", po::value<std::string>(), "Select file to operate with")
            ("output,o", po::value<std::string>(), "Select output file");
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << std::endl;
        return 0;
    }
    if (vm.count("cipher")) {
        if (vm.count("decipher")) {
            std::cerr << "Cipher and decipher modes can't be chosen together" << std::endl;
            return -1;
        }
        try {
            if (vm["type"].as<std::string>() == "block") {
                return handleBlockCipher(vm);
            } else if (vm["type"].as<std::string>() == "stream") {
                return handleStreamCipher(vm);
            } else {
                std::cerr << "Specified type is not supported" << std::endl;
                return -1;
            }
        } catch(...) {
            std::cerr << "Cipher type is not specified" << std::endl;
            return -1;
        }
    }
    if (vm.count("decipher")) {
        try {
            if (vm["type"].as<std::string>() == "block") {
                return handleBlockDecipher(vm);
            } else if (vm["type"].as<std::string>() == "stream") {
                return handleStreamDecipher(vm);
            } else {
                std::cerr << "Specified type is not supported" << std::endl;
                return -1;
            }
        } catch(...) {
            std::cerr << "Decipher is not specified" << std::endl;
            return -1;
        }
    }
}
