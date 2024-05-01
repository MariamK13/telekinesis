#ifndef SPREADSHEET_CPP_
#define SPREADSHEET_CPP_

#include "../header/SpreadSheet.hpp"
#include <algorithm>

SpreadSheet::SpreadSheet() :m_rows(2), m_cols(2)
{
	m_board = new Cell*[m_rows];
	for (size_t i = 0; i < m_rows; ++i) {
		m_board[i] = new Cell[m_cols];	
		}
}

SpreadSheet::SpreadSheet(const SpreadSheet& rhv) {
	std::cout << "copy ctor";
	m_rows = rhv.m_rows;
        m_cols = rhv.m_cols;
	m_board = rhv.m_board;
    	for (size_t i = 0; i < m_rows; ++i) {
        	for (size_t j = 0; j < m_cols; ++j) {
           		 m_board[i][j] = rhv.m_board[i][j];
        }
    }
}

SpreadSheet::SpreadSheet(SpreadSheet&& rhv) {
	std::cout << "move ctor";
	if (this != &rhv) {
		m_board = std::move(rhv.m_board);
	}
}

SpreadSheet::SpreadSheet(size_t size) {
	if (size < 1) {
		throw std::out_of_range("Out of Range!");
	}
	m_rows = size;
	m_cols = size;
	m_board = new Cell*[m_rows];
	for (size_t i = 0; i < m_rows; ++i) {
		m_board[i] = new Cell[m_cols];	
	}
}

SpreadSheet::SpreadSheet(size_t row, size_t col) {
	if (row < 1 || col < 1) {
		throw std::out_of_range("Out of Range!");
	}
	m_rows = row;
	m_cols = col;
	m_board = new Cell*[m_rows];
	for (size_t i = 0; i < m_rows; ++i) {
		m_board[i] = new Cell[m_cols];
	}
}

SpreadSheet::~SpreadSheet() {
	SpreadSheet::clear();
}

const SpreadSheet& 
SpreadSheet::operator=(const SpreadSheet& rhv) {
	m_rows = rhv.m_rows;
        m_cols = rhv.m_cols;
	m_board = rhv.m_board;
    	for (size_t i = 0; i < m_rows; ++i) {
        	for (size_t j = 0; j < m_cols; ++j) {
           		 m_board[i][j] = rhv.m_board[i][j];
        }
    }
    return *this;
}

const SpreadSheet& 
SpreadSheet::operator=(SpreadSheet&& rhv) {
	if (this != &rhv) {
		m_rows = rhv.m_rows;
		m_cols = rhv.m_cols;
		m_board = rhv.m_board;
		rhv.m_rows = 0;
		rhv.m_cols = 0;
		rhv.m_board = nullptr;
	}
	return *this;
}

SpreadSheet::Column SpreadSheet::operator[](size_t pos) {
	return Column(m_board[pos]);
}

const SpreadSheet::Column SpreadSheet::operator[](size_t pos) const {
	return Column(m_board[pos]);
}

void SpreadSheet::clear() noexcept {
	for (size_t i = 0; i < m_rows; ++i) {
		delete [] m_board[i];
	}
	delete [] m_board;
	m_board = nullptr;
        m_rows = 0;
   	m_cols = 0;
	
}

size_t SpreadSheet::row() const {
	return m_rows;
}

size_t SpreadSheet::col() const {
	return m_cols;
}

const Cell* SpreadSheet::getRow(size_t pos) const {
    return m_board[pos];
}

//horizontal 
void SpreadSheet::mirrorH() {
	for (size_t i = 0; i < row()/2; ++i) {
       		 for (size_t j = 0; j < col(); ++j) {
     	       		std::swap(m_board[i][j], m_board[row() - 1 - i][j]);
        }
    }
}

//vertical
void SpreadSheet::mirrorV() {
	for (size_t i = 0; i < row(); ++i) {
     		   for (size_t j = 0; j < col()/2; ++j) {
         		   std::swap(m_board[i][j], m_board[i][col() - 1 - j]);
            }
    }
}

//main diagonal
void SpreadSheet::mirrorD() {
	for (size_t i = 1; i < row(); ++i) {
      	  for (size_t j = 0; j < i; ++j) {
            std::swap(m_board[i][j], m_board[j][i]);
        }
    }
}

//secondary diagonal
void SpreadSheet::mirrorSD() {
	for (size_t i = 0; i < row() - 1; ++i) {
       		 for (size_t j = 0; j < col() - 1 - i; ++j) {
          		  std::swap(m_board[i][j], m_board[row() - 1 - j][col() - 1 - i]); //to be checked
        }
    }
}

void SpreadSheet::rotate(int cnt) {
	if (cnt < 1 || cnt > 3) {
		return;
	}
	if(cnt == 1) {
		SpreadSheet::mirrorSD();
	} else if (cnt == 2) {
		SpreadSheet::mirrorH();
	} else if (cnt == 3) {
		SpreadSheet::mirrorD();
	}
}

void SpreadSheet::removeRow(size_t row) 
{
	if (row >= m_rows) {
		return;
	}
	for (size_t i = row; i < m_rows - 1; ++i) {
		for (size_t j = 0; j < m_cols; ++j) {
			m_board[i][j] = m_board[i + 1][j];
		}
	}
		m_rows -= 1;
}


void SpreadSheet::removeRows(std::initializer_list<size_t> rows) {
	std::vector<size_t> rowsToRemove(rows);
	std::sort(rowsToRemove.rbegin(), rowsToRemove.rend());
	for (auto r : rowsToRemove) {
		if (r < m_rows) {
			for (size_t i = r; i < m_rows - 1; ++i) {
				for (size_t j = 0; j < m_cols; ++j) {
					m_board[i][j] = m_board[i + 1][j];
					}
			}
			for (size_t j = 0; j < m_cols; ++j) {
              			m_board[m_rows - 1][j] = Cell(); // Assuming Cell has a default constructor
       			     }
		--m_rows;	
  		  }
 	}
}


void SpreadSheet::removeCol(size_t col) {
	if (col >= m_cols) {
		return;
	}
	for (size_t i = 0; i < m_rows; ++i) {
		for (size_t j = col; j < m_cols - 1; ++j) {
			m_board[i][j] = m_board[i][j + 1];
			}
		}
	m_cols -= 1;
	
}

void SpreadSheet::removeCols(std::initializer_list<size_t> cols) {
	std::vector<size_t> colsToRemove(cols);
	std::sort(colsToRemove.rbegin(), colsToRemove.rend());
	for(auto c : colsToRemove) {
		if(c < m_cols) {
			for (size_t i = 0; i < m_rows; ++i) {
				for (size_t j = c; j < m_cols - 1; ++j) {
					m_board[i][j] = m_board[i][j + 1];
					}
			}
			for (size_t i = 0; i < m_rows; ++i) {
				m_board[i][m_cols - 1] = Cell();
			}
			--m_cols;
		}
	}
}

void SpreadSheet::resizeRow(size_t r) {
	Cell** tmp = new Cell*[r];
	for (size_t i = 0; i < r; ++i) {
		tmp[i] = new Cell[m_cols];
			for (size_t j = 0; j < m_cols; ++j) {
			 tmp[i][j] = '_';
			}
		}
		
	for (size_t i = 0; i < m_rows; ++i) {
        	delete[] m_board[i];
        }
	 delete[] m_board;
   	 m_board = tmp;
  	 m_rows = r;
}

void SpreadSheet::resizeCol(size_t c) {
	Cell** tmp = new Cell*[m_rows];
	for (size_t i = 0; i < m_rows; ++i) {
		tmp[i] = new Cell[c];
			for (size_t j = 0; j < c; ++j) {
				tmp[i][j] = '_';
			}
		}
	for (size_t i = 0; i < m_rows; ++i) {
		 delete[] m_board[i];
	}
	 delete[] m_board;
   	 m_board = tmp;
   	 m_cols = c;
}

void SpreadSheet::resize(size_t r, size_t c) {
	Cell** tmp = new Cell*[r];
	for (size_t i = 0; i < r; ++i) {
		tmp[i] = new Cell[c];
			for (size_t j = 0; j < c; ++j) {
				if (i < m_rows && j < m_cols) {
					tmp[i][j] = m_board[i][j];
				} else {
				tmp[i][j] = '_';
				}
			}
		}
	SpreadSheet::clear();
	
}


SpreadSheet SpreadSheet::slice(std::initializer_list<size_t> rows, std::initializer_list<size_t> cols) { //need to be improved
    std::vector<size_t> selectRows(rows);
    std::vector<size_t> selectCols(cols);

    if (selectRows.size() > m_rows || selectCols.size() > m_cols) {
        throw std::out_of_range("Out of Range");
    }

    SpreadSheet result(selectRows.size(), selectCols.size());

    for (size_t i = 0; i < selectRows.size(); ++i) {
        for (size_t j = 0; j < selectCols.size(); ++j) {
            try {
                result.m_board[i][j] = m_board[selectRows[i]][selectCols[j]];
            } catch (const std::out_of_range& e) {
                for (size_t k = 0; k < i; ++k) {
                    delete[] result.m_board[k];
                }
                delete[] result.m_board;
                throw;
            }
        }
    }

    return result;
}



SpreadSheet::Column::Column(Cell* col) : col(col) {}
Cell& SpreadSheet::Column::operator[](size_t pos) {
	return col[pos];
}
const Cell& SpreadSheet::Column::operator[](size_t pos) const {
	return col[pos];
}


bool operator==(const SpreadSheet& lhv, const SpreadSheet& rhv) {
	if (lhv.row() != rhv.row() || lhv.col() != rhv.col()) {
		return false;
	}
	for (size_t i = 0; i < lhv.row(); ++i) {
		for (size_t j = 0; j < lhv.col(); ++j) {
			if (lhv[i][j] != rhv[i][j]) {
				return false;
			}
		}
	}
	return true;
}

bool operator!=(const SpreadSheet& lhv, const SpreadSheet& rhv) {
	return !(lhv == rhv);
}

std::ostream& operator<<(std::ostream& out, const SpreadSheet& ob) {// beauty output using iomanip library
	size_t new_rows = ob.row();
	size_t new_cols = ob.col();
	
	for (auto i = 0; i < new_rows; ++i) {
		const Cell* pos = ob.getRow(i);
		for (auto j = 0; j < new_cols; ++j) {
			out << std::setw(10) << static_cast<std::string>(pos[j]) << " "; 
		} 
		out << "\n";
	}
	return out;
}

#endif
