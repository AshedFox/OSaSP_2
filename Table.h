#pragma once
#include <vector>
#include <string>
#include <tchar.h>
using namespace std;

#ifdef _UNICODE
using tstring = std::wstring;
#else
using tstring = std::string;
#endif

class Table
{
private:
	vector<vector<tstring>> table;
	int rowCount = 0;
	int columnCount = 0;

public:
	Table(int rowCount, int columnCount)
	{
		if (rowCount <= 0 || columnCount <= 0) {
			throw;
		}

		this->rowCount = rowCount;
		this->columnCount = columnCount;

		table = *new vector<vector<tstring>>(rowCount);

		for (int i = 0; i < rowCount; i++)
		{
			table.at(i) = *new vector<tstring>(columnCount, _T(""));
		}
	}

	Table(vector<vector<tstring>> initTable) {
		table = initTable;

		rowCount = initTable.size();
		for (auto row : initTable) {
			if (row.size() > columnCount) {
				columnCount = row.size();
			}
		}
	}

	void SetCellValue(tstring value, int row, int column) {
		table.at(row).at(column) = value;
	}

	tstring GetCellValue(int row, int column) {
		return table.at(row).at(column);
	}

	vector<vector<tstring>> GetTable() {
		return table;
	}

	int GetColumnCount() {
		return columnCount;
	}

	int GetRowCount() {
		return rowCount;
	}
};

