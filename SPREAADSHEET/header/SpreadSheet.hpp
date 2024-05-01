#ifndef __SPREADSHEET__HPP__
#define __SPREADSHEET__HPP__

#include <iostream>
#include <vector>
#include <string>
#include <initializer_list>
#include <iomanip>

#include "Cell.hpp"

class SpreadSheet
{
private:
    Cell** m_board;
    size_t m_rows;
    size_t m_cols;
private:
    class Column;
public:

    SpreadSheet();
    SpreadSheet(const SpreadSheet& rhv);
    SpreadSheet(SpreadSheet&& rhv);
    SpreadSheet(size_t size);
    SpreadSheet(size_t row, size_t col);
    ~SpreadSheet();

    const SpreadSheet& operator=(const SpreadSheet& rhv);
    const SpreadSheet& operator=(SpreadSheet&& rhv);

    Column operator[](size_t pos);
    const Column operator[](size_t pos) const;

    void clear() noexcept;

    size_t row() const;
    size_t col() const;
    const Cell* getRow(size_t pos) const;
    
    void mirrorH();
    void mirrorV();
    void mirrorD();
    void mirrorSD();

    void rotate(int cnt);

    void removeRow(size_t row);
    void removeRows(std::initializer_list<size_t> rows);
    void removeCol(size_t col);
    void removeCols(std::initializer_list<size_t> cols);

    void resizeRow(size_t r);
    void resizeCol(size_t c);
    void resize(size_t r, size_t c);


   SpreadSheet slice(std::initializer_list<size_t> rows, std::initializer_list<size_t> cols);        
};


class SpreadSheet::Column {
    private:
        Cell* col;
    public:
        explicit Column(Cell* col);
    public:
        Column() = delete;
        Column(const Column&) = delete;
        Column(Column&&) = delete;

        const Column& operator=(const Column&) = delete;
        const Column& operator=(Column&&) = delete;
    public:
        Cell& operator[](size_t pos);
        const Cell& operator[](size_t pos) const;
};

bool operator==(const SpreadSheet& lhv, const SpreadSheet& rhv);
bool operator!=(const SpreadSheet& lhv, const SpreadSheet& rhv);

std::ostream& operator<<(std::ostream& out, const SpreadSheet& ob); // beauty output using iomanip library

#include "../src/spreadsheet.cpp"

#endif //__SPREADSHEET__H__
