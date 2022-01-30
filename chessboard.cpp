#include "chessboard.h"
#include <algorithm>
#include <set>

using namespace std;

inline bool operator< (const chessboard_map& lhs, const chessboard_map& rhs) {
    return true;
}

Chessboard::Chessboard(size_t chessboard_size) {
    chessboard_map_.resize(chessboard_size); // создали chessboard_size строк(y)
    for (vector<uint16_t>& x : chessboard_map_) { // создали chessboard_size столбцов(x)
        x.resize(chessboard_size, 1);    //заполнили true
    }
}

set<chessboard_map> Chessboard::results = {};

void PrintChess(const chessboard_map& chessboard) {
    for (const auto& y : chessboard) {
        for (const auto& x : y) {
            cout << x << " ";
        }
        cout << endl;
    }
    cout << endl;
}

std::set<chessboard_map> Chessboard::PrintHardDecision(int start, int end) {
    vector <pair<size_t, size_t>> coordinates;
    for (size_t i = 0; i < chessboard_map_.size(); ++i) {
        for (size_t j = 0; j < chessboard_map_.size(); ++j) {
            coordinates.push_back({ i,j });
        }
    }
    for (int i = start; i < end; i++)
    {
        int x = i / chessboard_map_.size();
        int y = i % chessboard_map_.size();
        AddMagaraja(chessboard_map_, x, y);
    }
    return results;
}

void Chessboard::AddMagaraja(chessboard_map initial_chessboard_map, size_t x, size_t y) const { // Здесь мы КОПИРУЕМ initial_chessboard
    CloseTargetFields(initial_chessboard_map, x, y);
    initial_chessboard_map[y][x] = 2;// Cтавим Магараджу
    bool no_fields = true;

    for (size_t i = 0; i < initial_chessboard_map.size(); ++i) {//y
        for (size_t j = 0; j < initial_chessboard_map.size(); ++j) {//x
            if (initial_chessboard_map[i][j] == 1) {
                no_fields = false;
                AddMagaraja(initial_chessboard_map, j, i);
            }
        }
    }

    if (no_fields) {
        results.insert(move(initial_chessboard_map));
    }
}

void Chessboard::CloseTargetFields(chessboard_map& initial_chessboard_map, size_t x, size_t y) const {
    CloseVerticalAndHorizontalFields(initial_chessboard_map, x, y);
    CloseDiagonalFields(initial_chessboard_map, x, y);
    CloseKnightFields(initial_chessboard_map, x, y);
}


void Chessboard::CloseVerticalAndHorizontalFields(chessboard_map& initial_chessboard_map, size_t x, size_t y) const {
    for (size_t i = 0; i < initial_chessboard_map.size(); ++i) {
        initial_chessboard_map[i][x] = 0;
        initial_chessboard_map[y][i] = 0;
    }
}

void Chessboard::CloseDiagonalFields(chessboard_map& initial_chessboard_map, size_t x, size_t y) const {
    CloseTopLeftDiagonalFields(initial_chessboard_map, x, y);
    CloseTopRightDiagonalFields(initial_chessboard_map, x, y);
    CloseDownLeftDiagonalFields(initial_chessboard_map, x, y);
    CloseDownRightDiagonalFields(initial_chessboard_map, x, y);
}

void Chessboard::CloseKnightFields(chessboard_map& initial_chessboard_map, size_t x, size_t y) const {
    if (x > 0 && y > 1) {//TL
        initial_chessboard_map[y - 2][x - 1] = 0;
    }
    if (x > 1 && y > 0) {//LT
        initial_chessboard_map[y - 1][x - 2] = 0;
    }
    if ( (x + 1 < initial_chessboard_map.size()) && y > 1) {//TR
        initial_chessboard_map[y - 2][x + 1] = 0;
    }
    if (x > 1 && (y + 1 < initial_chessboard_map.size()) ) {//LD
        initial_chessboard_map[y + 1][x - 2] = 0;
    }
    if ((x + 2 < initial_chessboard_map.size()) && y > 0) {//RT
        initial_chessboard_map[y - 1][x + 2] = 0;
    }
    if (x > 0 && (y + 2 < initial_chessboard_map.size())) {//DL
        initial_chessboard_map[y + 2][x - 1] = 0;
    }
    if ((x + 1 < initial_chessboard_map.size()) && (y + 2 < initial_chessboard_map.size())) {//DR
        initial_chessboard_map[y + 2][x + 1] = 0;
    }
    if ((x + 2 < initial_chessboard_map.size()) && (y + 1 < initial_chessboard_map.size())) {//RD
        initial_chessboard_map[y + 1][x + 2] = 0;
    }
}

void Chessboard::CloseTopLeftDiagonalFields(chessboard_map& initial_chessboard_map, size_t x, size_t y) const {
    while ((x != 0) && (y != 0)) {
        initial_chessboard_map[y][x] = 0;//левую верхнюю диагональ
        x -= 1;
        y -= 1;
    }
    initial_chessboard_map[y][x] = 0;
}

void Chessboard::CloseTopRightDiagonalFields(chessboard_map& initial_chessboard_map, size_t x, size_t y) const {
    while ((x < initial_chessboard_map.size()) && (y != 0)) {
        initial_chessboard_map[y][x] = 0;//заполняет правую верхнюю диагональ
        x += 1;
        y -= 1;
    }

    if (y == 0 && x != initial_chessboard_map.size()) {
        initial_chessboard_map[y][x] = 0;
    }
}

void Chessboard::CloseDownLeftDiagonalFields(chessboard_map& initial_chessboard_map, size_t x, size_t y) const {
    while ((x != 0) && (y < initial_chessboard_map.size())) {
        initial_chessboard_map[y][x] = 0;//заполняет левую нижнюю диагональ
        x -= 1;
        y += 1;
    }

    if (x == 0 && y != initial_chessboard_map.size()) {
        initial_chessboard_map[y][x] = 0;
    }
}

void Chessboard::CloseDownRightDiagonalFields(chessboard_map& initial_chessboard_map, size_t x, size_t y) const {
    while (((x += 1) < initial_chessboard_map.size()) && ((y += 1) < initial_chessboard_map.size())) {
        initial_chessboard_map[y][x] = 0;//заполняет правую нижнюю диагональ нулями
    }
}


void Chessboard::Print(ofstream& out) const {       // вывод в файл chessboard_map
    for (const auto& map : results) {
        for (const auto& y : map) {
            for (const auto& x : y) {
                out << x << " ";
            }
            out << endl;
        }
        out << endl;
    }
}