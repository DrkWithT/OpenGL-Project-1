#ifndef READING_HPP
#define READING_HPP

#include <string>

namespace GLProject1::FileUtils {
    enum class ReadStatus {
        ok,
        file_not_found,
        file_io_failure,
        general_error,
        last = general_error
    };

    struct ReadResult {
        std::string blob;
        ReadStatus status;
    };

    [[nodiscard]] ReadResult readFileSync(const char* filename_cstr);

    void reportError(ReadStatus status);
}

#endif