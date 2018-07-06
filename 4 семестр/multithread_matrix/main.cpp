#define BENCHPRESS_CONFIG_MAIN
#include <iostream>
#include <utility>
#include <vector>
#include <iostream>

#define DTYPE int

using std::vector;
using std::cout;
using std::ostream;

class Matrix {
public:
    explicit Matrix(const vector<vector<DTYPE>> &data) : data_(data), sizerow_(data.size()),
                                                         sizecol_(data[0].size()) {}

    void GetMultiplyResultRow(int i, const Matrix &that, vector<DTYPE> &result_row) {
        for (int j = 0; j < result_row.size(); ++j) {
            for (int r = 0; r < that.sizerow_; ++r) {
                result_row[j] += this->data_[i][r] * that.data_[r][j];
            }
        }
    }

    friend ostream &operator<<(ostream &stream, const Matrix &matrix) {
        for (int i = 0; i < matrix.sizerow_; ++i) {
            stream << "[ ";
            for (int j = 0; j < matrix.sizecol_; ++j) {
                stream << matrix.data_[i][j] << " ";
            }
            stream << "]" << std::endl;
        }
    }

    Matrix Multiply(const Matrix &that) {
        vector<vector<DTYPE>> result_data(this->sizerow_, vector<DTYPE>(that.sizecol_, 0));
        for (int i = 0; i < this->sizerow_; ++i) {
            GetMultiplyResultRow(i, that, result_data[i]);
        }
        return Matrix(result_data);
    }

protected:
    vector<vector<DTYPE>> data_;
    int sizerow_, sizecol_;
};

int main() {
    vector<vector<DTYPE>> a_data = {{5, 3, 1},
                                    {2, 3, 6}};
    Matrix a(a_data);
    vector<vector<DTYPE>> b_data = {{3, 1},
                                    {5, 2},
                                    {7, 3}
    };
    Matrix b(b_data);
    Matrix c = a.Multiply(b);
    cout << c;

    return 0;
}