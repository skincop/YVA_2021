#include "stdafx.h"
#include "IT.h"
#include "Error.h"

namespace IT
{
	IT::Entry::Entry(int idxfirstLE, std::string id, std::string scope, IDTYPE idtype, int value)
		: idxfirstLE(idxfirstLE), iddatatype(IDDATATYPE::Numbers), idtype(idtype), id(id), scope(scope)
	{
		this->value.vint = value;
	}

	IT::Entry::Entry(int idxfirstLE, std::string id, std::string scope, const char* value, IDTYPE idtype)
		: idxfirstLE(idxfirstLE), iddatatype(IDDATATYPE::Symbol), idtype(idtype), id(id), scope(scope)
	{
		this->value.vpin.len = (char)strlen(value);
		strcpy_s(this->value.vpin.str, value);
	}
	IT::Entry::Entry(int idxfirstLE, std::string id, std::string scope, IDTYPE idtype, const char* value)
		: idxfirstLE(idxfirstLE), iddatatype(IDDATATYPE::Line), idtype(idtype), id(id), scope(scope)
	{
		this->value.vstr.len = (char)strlen(value);
		strcpy_s(this->value.vstr.str, value);
	}



	IT::Entry::Entry(int idxfirstLE, std::string id, std::string scope, IDDATATYPE iddatatype, IDTYPE idtype)
		: idxfirstLE(idxfirstLE), iddatatype(iddatatype), idtype(idtype), id(id), scope(scope)
	{
		if (this->iddatatype == IDDATATYPE::Numbers) {
			value.vint = TI_INT_DEFAULT;
		}
		else if (this->iddatatype == IDDATATYPE::Symbol) {
			value.vpin.len = TI_SYMBOL_DEFAULT;
		}
		else {
			value.vstr.len = TI_STR_DEFAULT;
		}
	}


	IdTable Create(int size) {
		if (size > TI_MAXSIZE) {
			throw ERROR_THROW(125);
		}
		IdTable* table = new IdTable;
		table->maxsize = size;
		table->size = 0;
		table->table = new Entry[size];
		return *table;
	}

	void Add(IdTable& idtable, Entry entry) {
		if (idtable.size + 1 > idtable.maxsize) {
			throw ERROR_THROW(126);
		}
		idtable.table[idtable.size] = entry;
		++idtable.size;
	}

	Entry GetEntry(IdTable& idtable, int n) {
		if (n > idtable.size) {
			throw ERROR_THROW(128);
		}
		return idtable.table[n];
	}

	int IsId(IdTable& idtable, std::string id, std::vector<std::string> scope) {
		for (int i = scope.size() - 1; i >= 0; --i)
		{
			for (int j = 0; j < idtable.size; ++j)
			{
				if (idtable.table[j].id == id && idtable.table[j].scope == scope[i])
				{
					return j;
				}
			}
		}
		return TI_NULLIDX;
	}

	int isLit(IdTable& idtable, int lit) {
		for (int i = 0; i < idtable.size; ++i) {
			if (idtable.table[i].value.vint == lit && idtable.table[i].idtype == IDTYPE::L)
			{
				return i;
			}
		}
		return TI_NULLIDX;
	}

	int isLit(IdTable& idtable, std::string lit) {
		for (int i = 0; i < idtable.size; ++i) {
			if (idtable.table[i].value.vstr.str == lit && idtable.table[i].idtype == IDTYPE::L)
			{
				return i;
			}
		}
		return TI_NULLIDX;
	}

	int isLit(std::string lit1, IdTable& idtable) {
		for (int i = 0; i < idtable.size; ++i) {
			if (idtable.table[i].value.vpin.str == lit1 && idtable.table[i].idtype == IDTYPE::L)
			{
				return i;
			}
		}
		return TI_NULLIDX;
	}


	void ShowTable(IdTable& idtable, std::ofstream* stream)
	{
		*stream << std::setw(5) << "index" << std::setw(10) << "name" << std::setw(10) << "type" << std::setw(15) << "id type" << std::setw(10) << "scope" << std::setw(20) << "lexTable index" << '\n';
		for (int i = 0; i < idtable.size; ++i) 
		{
			*stream << std::setw(5) << i << std::setw(10) << idtable.table[i].id << std::setw(10);
			if (idtable.table[i].iddatatype == IDDATATYPE::Numbers)
				*stream << "int ";
			else if (idtable.table[i].iddatatype == IDDATATYPE::Symbol)
				*stream << "pin ";
			else if (idtable.table[i].iddatatype == IDDATATYPE::Line)
				*stream << "str ";

			*stream << std::setw(10);
			if (idtable.table[i].idtype == IDTYPE::F)
				*stream << "f ";
			else if (idtable.table[i].idtype == IDTYPE::L)
				*stream << "l ";
			else if (idtable.table[i].idtype == IDTYPE::P)
				*stream << "p ";
			else if (idtable.table[i].idtype == IDTYPE::V)
				*stream << "v ";

			*stream << std::setw(15);
			*stream << idtable.table[i].scope;

			*stream << std::setw(15) << idtable.table[i].idxfirstLE;
			*stream << '\n';
		}
		*stream << '\n';
	}
}