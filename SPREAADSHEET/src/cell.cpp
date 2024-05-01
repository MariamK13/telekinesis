#ifndef CELL_CPP_
#define CELL_CPP_

#include "../header/Cell.hpp"

std::ostream& operator<<(std::ostream& out, const std::vector<int>& ob) {
	for (const auto v : ob) {
		out << std::to_string(v);
	}
	return out;
}


Cell::Cell() {m_val = "_";}
Cell::Cell(const Cell& rhv) {m_val = rhv.m_val;}
Cell::Cell(Cell&& rhv) {m_val = std::move(rhv.m_val);}
Cell::Cell(int val) {m_val = std::to_string(val);}
Cell::Cell(double val) {m_val = std::to_string(val);}
Cell::Cell(char val) {m_val = std::to_string(val);}
Cell::Cell(bool val) {m_val = std::to_string(val);}
Cell::Cell(std::string val) {m_val = val;}
Cell::Cell(const std::vector<int>& val) {
	for (const auto& v : val) {
		m_val += std::to_string(v);
	}
}

const Cell& Cell::operator=(const Cell& rhv) {
	this->m_val = rhv.m_val;
	return *this;
}

const Cell& Cell::operator=(Cell&& rhv) {
	if (this != &rhv) {
		m_val = std::move(rhv.m_val); 
		rhv.m_val = "";
	}
	return *this;
}

const Cell& Cell::operator=(int rhv) {
	m_val = std::to_string(rhv);
	return *this;
}  
const Cell& Cell::operator=(double rhv) {
	m_val = std::to_string(rhv);
	return *this;
}

const Cell& Cell::operator=(char rhv) {
	 m_val = std::string(1, rhv);
   	 return *this;
}
 
const Cell& Cell::operator=(bool rhv) {
	m_val = rhv ? "true" : "false";
    	return *this;
}
 
const Cell& Cell::operator=(std::string rhv) {
	m_val = rhv;
	return *this;
}
const Cell& Cell::operator=(const std::vector<int>& rhv) {
	 m_val.clear();
	for (int i : rhv) {
		m_val += std::to_string(i);
	}
	return *this;
}


Cell::operator int() const {
	 try {
        return std::stoi(m_val);
    } catch (const std::invalid_argument&) {
        return 0; 
    }
}

Cell::operator double() const {
	try {
        return std::stod(m_val);
    } catch (const std::invalid_argument&) {
        return 0.0;
    }
}

Cell::operator char() const {
	if (!m_val.empty()) {
        return m_val[0]; 
    } 
        return '\0'; 
}
 
Cell::operator bool() const {
	return !m_val.empty();
}
 
Cell::operator std::string() const {
	return m_val;
}
 
Cell::operator std::vector<int>() { //need to be improved
    std::vector<int> result;
    std::stringstream ss(m_val);
    int num;
    while (ss >> num) {
        result.push_back(num);
    }
    return result;
}  

std::string Cell::getVal() const {
	return m_val;
}

bool operator==(const Cell& lhv, const Cell& rhv) {
	return lhv.getVal() == rhv.getVal();
	
}
bool operator!=(const Cell& lhv, const Cell& rhv) {
	return !(lhv.getVal() == rhv.getVal());
}

std::ostream& operator<<(std::ostream& out, Cell& ob) {
	out << static_cast<std::string>(ob);
	return out;
}

std::istream& operator>>(std::istream& in, Cell& ob) {
	std::string tmp;
	in >> tmp;
	ob = tmp;
	return in;
}

#endif

