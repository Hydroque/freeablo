
#pragma once

#include <cstdint>
#include <string>

namespace Serial
{
    class ReadStreamInterface;
    class WriteStreamInterface;

    class Loader
    {
    public:
        Loader(ReadStreamInterface& stream);

        template <typename T> T load();

        void startCategory(const std::string& name);
        void endCategory(const std::string& name);

    private:
        ReadStreamInterface& mStream;
    };

    template <> bool Loader::load<bool>();
    template <> int64_t Loader::load<int64_t>();
    template <> uint64_t Loader::load<uint64_t>();
    template <> int32_t Loader::load<int32_t>();
    template <> uint32_t Loader::load<uint32_t>();
    template <> int16_t Loader::load<int16_t>();
    template <> uint16_t Loader::load<uint16_t>();
    template <> int8_t Loader::load<int8_t>();
    template <> uint8_t Loader::load<uint8_t>();
    template <> std::string Loader::load<std::string>();

    class Saver
    {
    public:
        Saver(WriteStreamInterface& stream);

        void save(bool val);
        void save(int64_t val);
        void save(uint64_t val);
        void save(int32_t val);
        void save(uint32_t val);
        void save(int16_t val);
        void save(uint16_t val);
        void save(int8_t val);
        void save(uint8_t val);
        void save(const std::string& val);

        void startCategory(const std::string& name);
        void endCategory(const std::string& name);

    private:
        WriteStreamInterface& mStream;
    };

    template <typename T> class ScopedCategory
    {
    public:
        ScopedCategory(std::string&& name, T& saverOrLoader);
        ~ScopedCategory();

    private:
        std::string mName;
        T& mSaverOrLoader;
    };

    using ScopedCategorySaver = ScopedCategory<Saver>;
}
