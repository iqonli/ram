// [ram.cpp]
// Copyright (C) [2025] [IQ Online Studio / PerryDing]
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <filesystem>

namespace fs = std::filesystem;

// R.I.P.算法实现类
class RIPAlgorithm
{
public:
    // 压缩方法
    static std::vector<unsigned char> compress(const std::vector<unsigned char>& data, int mode)
    {
        std::vector<unsigned char> result;
        
        switch (mode)
        {
            case 0: // 精准模式
                result = preciseMode(data);
                break;
            case 1: // 快速前压模式
                result = fastFrontMode(data);
                break;
            case 2: // 快速后压模式
                result = fastBackMode(data);
                break;
            case 3: // 极速天命模式
                result = destinyMode(data);
                break;
            default:
                std::cerr << "不支持的压缩模式: " << mode << std::endl;
                exit(1);
        }
        
        // 确保结果只有1B，且内容为00000000或00000001
        return normalizeResult(result);
    }
    
    // 解压方法 - 死循环实现TLE
    static void decompress(const std::string& filePath, const std::string& outputPath)
    {
        std::cout << "开始解压...这可能需要很长时间(约-2147483647年), 可以按Ctrl+C终止" << std::endl;
        
        // 创建输出目录
        fs::create_directories(outputPath);
        
        // 死循环模拟长时间解压
        while (true)
        {
            // 防止CPU占用过高
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

private:
    // 精准模式
    static std::vector<unsigned char> preciseMode(const std::vector<unsigned char>& data)
    {
        if (data.empty())
        {
            return {0};
        }
        
        std::vector<unsigned char> current = data;
        
        while (current.size() > 1)
        {
            std::vector<unsigned char> next;
            
            for (size_t i = 0; i < current.size() - 1; ++i)
            {
                next.push_back(current[i] ^ current[i + 1]);
            }
            
            current = next;
        }
        
        return current;
    }
    
    // 快速前压模式
    static std::vector<unsigned char> fastFrontMode(const std::vector<unsigned char>& data)
    {
        if (data.empty())
        {
            return {0};
        }
        
        std::vector<unsigned char> current = data;
        
        for (size_t i = 1; i < current.size(); ++i)
        {
            current[0] ^= current[i];
        }
        
        return {current[0]};
    }
    
    // 快速后压模式
    static std::vector<unsigned char> fastBackMode(const std::vector<unsigned char>& data)
    {
        if (data.empty())
        {
            return {0};
        }
        
        std::vector<unsigned char> current = data;
        
        for (size_t i = 0; i < current.size() - 1; ++i)
        {
            current.back() ^= current[i];
        }
        
        return {current.back()};
    }
    
    // 极速天命模式
    static std::vector<unsigned char> destinyMode(const std::vector<unsigned char>& data)
    {
        if (data.empty())
        {
            return {0};
        }
        
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, data.size() - 1);
        
        return {data[distrib(gen)]};
    }
    
    // 归一化结果为1B，且只能是00000000或00000001
    static std::vector<unsigned char> normalizeResult(const std::vector<unsigned char>& result)
    {
        if (result.empty())
        {
            return {0};
        }
        
        // 取结果的最后一个字节，并与1进行与运算，确保只有两种可能值
        unsigned char value = result.back() & 1;
        
        return {value};
    }
};

// 文件操作工具类
class FileUtils
{
public:
    // 读取文件
    static std::vector<unsigned char> readFile(const std::string& filePath)
    {
        std::ifstream file(filePath, std::ios::binary);
        
        if (!file)
        {
            std::cerr << "无法打开文件: " << filePath << std::endl;
            exit(1);
        }
        
        // 获取文件大小
        file.seekg(0, std::ios::end);
        size_t size = file.tellg();
        file.seekg(0, std::ios::beg);
        
        // 读取文件内容
        std::vector<unsigned char> data(size);
        file.read(reinterpret_cast<char*>(data.data()), size);
        
        return data;
    }
    
    // 写入文件
    static void writeFile(const std::string& filePath, const std::vector<unsigned char>& data)
    {
        std::ofstream file(filePath, std::ios::binary);
        
        if (!file)
        {
            std::cerr << "无法创建文件: " << filePath << std::endl;
            exit(1);
        }
        
        file.write(reinterpret_cast<const char*>(data.data()), data.size());
    }
    
    // 分卷写入文件
    static void writePartialFiles(const std::string& basePath, const std::vector<unsigned char>& data, int partSize)
    {
        // 对于1B的数据，无论分卷大小是多少，都只会有一个分卷
        std::string partPath = basePath + ".1.raw";
        writeFile(partPath, data);
        
        std::cout << "已创建分卷压缩文件: " << partPath << std::endl;
    }
    
    // 删除文件
    static void deleteFile(const std::string& filePath)
    {
        if (std::remove(filePath.c_str()) != 0)
        {
            std::cerr << "无法删除文件: " << filePath << std::endl;
        }
        else
        {
            std::cout << "已删除原文件: " << filePath << std::endl;
        }
    }
};

// 命令行参数解析类
class CommandLineParser
{
public:
    CommandLineParser(int argc, char* argv[])
        : argc_(argc)
        , argv_(argv)
        , mode_(0)
        , partMode_(false)
        , partNum_(-1)
        , partSize_(-1)
        , autoDelete_(false)
        , isCompress_(true)
    {
        parse();
    }
    
    int getMode() const
    {
        return mode_;
    }
    
    bool isPartMode() const
    {
        return partMode_;
    }
    
    int getPartNum() const
    {
        return partNum_;
    }
    
    int getPartSize() const
    {
        return partSize_;
    }
    
    bool isAutoDelete() const
    {
        return autoDelete_;
    }
    
    const std::string& getInputFile() const
    {
        return inputFile_;
    }
    
    const std::string& getOutputFile() const
    {
        return outputFile_;
    }
    
    bool isCompress() const
    {
        return isCompress_;
    }

private:
    void parse()
    {
        if (argc_ < 2)
        {
            printHelp();
            exit(0);
        }
        
        std::string mode = argv_[1];
        
        if (mode == "-en")
        {
            isCompress_ = true;
            parseCompressArgs();
        }
        else if (mode == "-de")
        {
            isCompress_ = false;
            parseDecompressArgs();
        }
        else
        {
            std::cerr << "无效的模式: " << mode << std::endl;
            printHelp();
            exit(1);
        }
    }
    
    void parseCompressArgs()
    {
        int i = 2;
        
        while (i < argc_)
        {
            std::string arg = argv_[i];
            
            if (arg == "-mode")
            {
                if (i + 1 < argc_)
                {
                    mode_ = std::stoi(argv_[i + 1]);
                    i += 2;
                }
                else
                {
                    std::cerr << "缺少模式参数" << std::endl;
                    exit(1);
                }
            }
            else if (arg == "-part")
            {
                partMode_ = true;
                i++;
                
                if (i < argc_)
                {
                    std::string partArg = argv_[i];
                    
                    if (partArg == "-n")
                    {
                        if (i + 1 < argc_)
                        {
                            partNum_ = std::stoi(argv_[i + 1]);
                            i += 2;
                        }
                        else
                        {
                            std::cerr << "缺少分卷数量参数" << std::endl;
                            exit(1);
                        }
                    }
                    else if (partArg == "-b")
                    {
                        if (i + 1 < argc_)
                        {
                            partSize_ = std::stoi(argv_[i + 1]);
                            i += 2;
                        }
                        else
                        {
                            std::cerr << "缺少分卷大小参数" << std::endl;
                            exit(1);
                        }
                    }
                    // 这里可以添加其他分卷大小单位的处理
                }
            }
            else if (arg == "-autodel")
            {
                autoDelete_ = true;
                i++;
            }
            else if (arg == "-to")
            {
                if (i + 1 < argc_)
                {
                    outputFile_ = argv_[i + 1];
                    i += 2;
                }
                else
                {
                    std::cerr << "缺少输出文件参数" << std::endl;
                    exit(1);
                }
            }
            else
            {
                inputFile_ = arg;
                i++;
            }
        }
        
        if (inputFile_.empty())
        {
            std::cerr << "缺少输入文件" << std::endl;
            exit(1);
        }
        
        if (outputFile_.empty())
        {
            // 默认输出文件名
            size_t dotPos = inputFile_.find_last_of('.');
            
            if (dotPos != std::string::npos)
            {
                outputFile_ = inputFile_.substr(0, dotPos) + ".raw";
            }
            else
            {
                outputFile_ = inputFile_ + ".raw";
            }
        }
    }
    
    void parseDecompressArgs()
    {
        int i = 2;
        
        while (i < argc_)
        {
            std::string arg = argv_[i];
            
            if (arg == "-to")
            {
                if (i + 1 < argc_)
                {
                    outputFile_ = argv_[i + 1];
                    i += 2;
                }
                else
                {
                    std::cerr << "缺少输出目录参数" << std::endl;
                    exit(1);
                }
            }
            else
            {
                inputFile_ = arg;
                i++;
            }
        }
        
        if (inputFile_.empty())
        {
            std::cerr << "缺少输入文件" << std::endl;
            exit(1);
        }
        
        if (outputFile_.empty())
        {
            // 默认输出目录
            size_t dotPos = inputFile_.find_last_of('.');
            
            if (dotPos != std::string::npos)
            {
                outputFile_ = inputFile_.substr(0, dotPos);
            }
            else
            {
                outputFile_ = inputFile_ + "_extracted";
            }
        }
    }
    
    void printHelp()
    {
        std::cout << "R.I.P. Archive Manager 使用帮助" << std::endl;
        std::cout << "压缩模式: ram -en [-mode num] [-part [-n num | -b byte]] [-autodel] file [-to file]" << std::endl;
        std::cout << "解压模式: ram -de file [-to path]" << std::endl;
        std::cout << "  -mode num: 压缩模式(0-精准模式, 1-快速前压模式, 2-快速后压模式, 3-极速天命模式)" << std::endl;
        std::cout << "  -part: 分卷压缩模式" << std::endl;
        std::cout << "    -n num: 分卷数量" << std::endl;
        std::cout << "    -b byte: 分卷大小(字节)" << std::endl;
        std::cout << "  -autodel: 压缩后自动删除原文件" << std::endl;
        std::cout << "  file: 输入文件" << std::endl;
        std::cout << "  -to file/path: 输出文件/目录" << std::endl;
    }
    
    int argc_;
    char** argv_;
    int mode_;
    bool partMode_;
    int partNum_;
    int partSize_;
    bool autoDelete_;
    std::string inputFile_;
    std::string outputFile_;
    bool isCompress_;
};

int main(int argc, char* argv[])
{
    std::cout << "R.I.P. Archive Manager v1.0" << std::endl;
    std::cout << "一款极具实用性、功能极其强大的压缩软件" << std::endl;
    std::cout << "by IQ Online Studio, github.com/iqonli/ram" << std::endl;
    std::cout << "本项目使用 GNU General Public License v3.0 许可证" << std::endl << std::endl;
    
    try
    {
        CommandLineParser parser(argc, argv);
        
        if (parser.isCompress())
        {
            std::cout << "开始压缩文件: " << parser.getInputFile() << std::endl;
            std::cout << "压缩模式: " << parser.getMode() << std::endl << std::endl;
            
            // 读取文件
            std::vector<unsigned char> data = FileUtils::readFile(parser.getInputFile());
            
            // 压缩数据
            std::vector<unsigned char> compressedData = RIPAlgorithm::compress(data, parser.getMode());
            
            // 写入文件
            if (parser.isPartMode())
            {
                int partSize = parser.getPartSize() != -1 ? parser.getPartSize() : 1;
                FileUtils::writePartialFiles(parser.getOutputFile(), compressedData, partSize);
            }
            else
            {
                FileUtils::writeFile(parser.getOutputFile(), compressedData);
                std::cout << "压缩完成，输出文件: " << parser.getOutputFile() << std::endl;
            }
            
            // 自动删除原文件
            if (parser.isAutoDelete())
            {
                FileUtils::deleteFile(parser.getInputFile());
            }
            
            std::cout << "压缩率: " << (static_cast<double>(compressedData.size()) / data.size() * 100) << "%" << std::endl;
        }
        else
        {
            std::cout << "开始解压文件: " << parser.getInputFile() << std::endl;
            
            // 解压数据
            RIPAlgorithm::decompress(parser.getInputFile(), parser.getOutputFile());
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "发生错误: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
