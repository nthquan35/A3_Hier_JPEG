#include "block_extractor.hpp"


BlockExtractor::BlockExtractor() {
    _block_vector = new std::vector<cv::Mat *>();
    _huf_vector = new std::vector<Huffman *>();
    _per_row = 0;
    _per_col = 0;
    _samples_number = 0;
}

BlockExtractor::~BlockExtractor() {
}

void BlockExtractor::add_huffman(Huffman *huf) {
    _huf_vector->push_back(huf);
}

Huffman *BlockExtractor::get_huffman(int index) {
    return _huf_vector->at(index);
}

void BlockExtractor::clear_huffman() {
    _huf_vector->clear();
}

void BlockExtractor::extract_blocks(const cv::Mat &mat) {
    _per_row = mat.cols / 8;
    _per_col = mat.rows / 8;

    _samples_number = _per_row * _per_col;

    // TODO Extract 8x8 blocks from mat, and push every block to _block_vector
    for (int i =0; i < _per_row; i++){
        for (int j = 0; j < _per_col; j++){
            cv::Mat *block = new cv::Mat(8,8,CV_32FC1);
            for (int x = 0; x< 8; x++){
                for (int y = 0; y < 8; y++){
                    block->at<float>(x,y) = mat.at<float>(i*8 + x, j*8 + y);
                }
            }
            //cv::Mat block = cv::Mat(8,8, CV_32FC1, subMatrix);
            _block_vector->push_back(block);
        }
    }
}

std::vector<cv::Mat *> *BlockExtractor::get_blocks() {
    return _block_vector;
}

int BlockExtractor::get_per_row() const {
    return _per_row;
}

int BlockExtractor::get_per_col() const {
    return _per_col;
}
