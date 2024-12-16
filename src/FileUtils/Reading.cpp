/**
 * @file Reading.cpp
 * @author DrkWithT
 * @brief Implements simple file reading functions. In this pet project, I won't intend to modify the files while reading is done, so TOCTOU may not matter.
 * @date 2024-12-15
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <array>
#include <string_view>
#include <memory>
#include <fstream>
#include <iostream>

#include "FileUtils/Reading.hpp"

namespace GLProject1::FileUtils {
    static constexpr std::size_t max_file_error_code = static_cast<std::size_t>(ReadStatus::last) + 1;
    static constexpr std::array<std::string_view, max_file_error_code> file_error_msgs = {
        "OK",
        "File not found!",
        "File I/O error!",
        "Unknown error!"
    };

    ReadResult readFileSync(const char* filename_cstr) {
        std::ifstream reader {filename_cstr};

        if (!reader.is_open()) {
            return {"", ReadStatus::file_not_found};
        }

        reader.seekg(0, reader.end);
        std::size_t file_len = reader.tellg();
        reader.seekg(0, reader.beg);

        auto raw_data = std::make_unique<char[]>(file_len + 1);
        raw_data[file_len] = '\0';

        if (reader.read(raw_data.get(), file_len).bad()) {
            return {
                "",
                ReadStatus::file_io_failure
            };
        }

        return {
            raw_data.get(),
            ReadStatus::ok
        };
    }

    void reportError(ReadStatus status) {
        if (status > ReadStatus::ok && status <= ReadStatus::general_error) {
            std::cerr << "FileUtils Error: \"" << file_error_msgs[static_cast<int>(status)] << "\"\n";
        }
    }
}
