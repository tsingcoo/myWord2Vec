#include <iostream>
#include <fstream>
#include <sstream>

#include "word2vec.h"

void readDefs(std::string wordF, std::string defF, std::string resF, std::string modelF) {
    std::ifstream fin1(wordF);
    std::string line;
    std::string word;
    std::vector<std::string> words;
    std::vector<int> defs;

    while (getline(fin1, line)) {
        words.push_back(line);
    }
    fin1.close();

    //载入模型
    std::unique_ptr<w2v::w2vModel_t> w2vModel;
    w2vModel.reset(new w2v::w2vModel_t());
    w2vModel->load(modelF);


    std::ifstream fin2(defF);
    std::ofstream fout1(resF);
    int wordindex = 0;
    while (getline(fin2, line)) {
        std::istringstream iss(line);
        w2v::word2vec_t temp(w2vModel, "微软");
        while (iss >> word) {
            w2v::word2vec_t temp1(w2vModel, word);
            for (auto i = 0; i != temp.size(); ++i) {
                temp[i] += temp1[i];
            }
        }
        fout1 << words[wordindex] << '\t';
        ++wordindex;
        bool firstword = true;
        for (int i = 0; i != temp.size(); ++i) {
            if (firstword) {
                firstword = false;
            } else {
                fout1 << " ";
            }
            fout1 << temp[i];
        }
        fout1 << std::endl;
    }
    fin2.close();
    fout1.close();

}

int main() {

    readDefs("/Users/wangqinglong/Library/Mobile Documents/com~apple~CloudDocs/Shanbay/defs_processed_word.txt",
             "/Users/wangqinglong/Library/Mobile Documents/com~apple~CloudDocs/Shanbay/defs_processed_def.txt",
             "/Users/wangqinglong/Windows/800/defs_processed_vec.txt",
                     "/Users/wangqinglong/Downloads/word2vec-master-2/bin/model.w2v");

//    std::unique_ptr<w2v::w2vModel_t> w2vModel;
//    try {
//        w2vModel.reset(new w2v::w2vModel_t());
//        if (!w2vModel->load("/Users/wangqinglong/Downloads/word2vec-master-2/bin/model.w2v")) {
//            throw std::runtime_error(w2vModel->errMsg());
//        }
//    } catch (const std::exception &_e) {
//        std::cerr << _e.what() << std::endl;
//        return 2;
//    } catch (...) {
//        std::cerr << "unknown error" << std::endl;
//        return 2;
//    }
//
//    w2v::word2vec_t a1(w2vModel, "苹果");
//    w2v::word2vec_t a2(w2vModel, "梨");
//    w2v::word2vec_t a3(w2vModel, "微软");
//
//    float ret = 0.0f;
//    for (uint16_t i = 0; i < a1.size(); ++i) {
//        std::cout << a1[i] << " " << a2[i] << " " << a3[i] << std::endl;
//        ret += a1[i] * a2[i];
//    }
//    std::cout << ret << std::endl;

    return 0;
}