#include "stdafx.h"
#include "Semantic.h"
#include"Error.h"
#include"IT.h"
#include"LT.h"
#include"Regs.h"
#include"Lex.h"
#include <vector>
#include <iostream>


//TODO: После декларе идет тип данных 
//TODO: После типа данных  идет функция или индиф
//TODO: Проверка возвращаемого значения функции
//TODO: Соответсвие типа переменной и присваемового значения
//TODO: Область значения переменной
//TODO присвоение функции значения


namespace Semantic
{
	bool semanticsCheck(LT::LexTable& lexTable, IT::IdTable& idTable)
	{
		bool is_ok = true;
		bool is_main = false;
		int b = 0,o=0,p=0;
		int funcArgv = 0;
		auto scopeFunc = TI_SCOPE_DEFAULT;
		auto typeVar = idTable.table[0].iddatatype;

		IT::IDDATATYPE ret;
		IT::IDDATATYPE retFunc;
		IT::IDDATATYPE funcType;


		/*std::array<std::string, 10> codeWord = {
			REG_MAIN,REG_DECLARE,REG_INTEGER,REG_SYMBOL,
			REG_FUNCTION,REG_RETURN,REG_PRINT,REG_MAIN,
			REG_IF,REG_ELSE

		};*/
		
		for (auto i = 0; i < lexTable.size; i++)
		{

			switch (lexTable.table[i].lexema)
			{

			case LEX_DECLARE:
				if (lexTable.table[i + 1].lexema == LEX_DATATYPE && lexTable.table[i + 2].lexema == LEX_ID) {
					p = lexTable.table[i + 2].idxTI;
					while (idTable.table[lexTable.table[i + 2].idxTI].scope == idTable.table[p].scope) {
						p--;
						if (idTable.table[lexTable.table[i + 2].idxTI].id == idTable.table[p].id && idTable.table[lexTable.table[i + 2].idxTI].idtype!=IT::IDTYPE::L) {
							std::cout << "name" + idTable.table[p].id << std::endl;
							std::cout << "scope" + idTable.table[p].scope << std::endl;
							is_ok = false;
							throw ERROR_THROW(315);
						}

					}
				}
				break;
			case LEX_EQUAL:
				
				if (idTable.table[lexTable.table[i - 1].idxTI].idtype == IT::IDTYPE::F) {// функции нельзя присовить значение
					
					is_ok = false;
					throw ERROR_THROW(304);

				}

				// индиф = функция

				if (lexTable.table[i - 1].lexema == LEX_ID && idTable.table[lexTable.table[i + 1].idxTI].idtype == IT::IDTYPE::F)
				{
				
					int j = i + 2;
					std::vector<std::string> funcArguments;
					std::vector<std::string> arguments;

					//считает аргументы при объявлении
					while (lexTable.table[j].lexema != LEX_RIGHTTHESIS)
					{
						if (lexTable.table[j].lexema == LEX_ID || lexTable.table[j].lexema == LEX_LITERAL)
						{
							
							if (idTable.table[lexTable.table[j].idxTI].iddatatype == IT::IDDATATYPE::Number)
								arguments.push_back("0");
							if (idTable.table[lexTable.table[j].idxTI].iddatatype == IT::IDDATATYPE::Line)
								arguments.push_back("1");
							if (idTable.table[lexTable.table[j].idxTI].iddatatype == IT::IDDATATYPE::Symbol)
								arguments.push_back("2");
						}
						j++;
					}

					// номер первого упоминания функции в табл лексем
					int l = idTable.table[lexTable.table[i + 1].idxTI].idxfirstLE + 1;

					while (lexTable.table[l].lexema != LEX_RIGHTTHESIS)
					{
						if (lexTable.table[l].lexema == LEX_ID || lexTable.table[l].lexema == LEX_LITERAL)
						{
							
							if (idTable.table[lexTable.table[l].idxTI].iddatatype == IT::IDDATATYPE::Number)
								funcArguments.push_back("0");
							else if (idTable.table[lexTable.table[l].idxTI].iddatatype == IT::IDDATATYPE::Line)
								funcArguments.push_back("1");
							else if (idTable.table[lexTable.table[l].idxTI].iddatatype == IT::IDDATATYPE::Symbol)
								funcArguments.push_back("2");

						}
						l++;
					}
					if (arguments.size() != funcArguments.size())
					{
						is_ok = false;
						throw ERROR_THROW(303);
						std::cout << "123";
					}
					if (arguments.size() == funcArguments.size() && arguments != funcArguments)
					{
						is_ok = false;
						std::cout << "456";
						throw ERROR_THROW(302);
					}

				}


					o = i;
					while (lexTable.table[o].lexema != LEX_SEMICOLON)
					{
						if (lexTable.table[o].lexema == LEX_ID || lexTable.table[o].lexema == LEX_LITERAL)
						{
							if (idTable.table[lexTable.table[o].idxTI].idtype == IT::IDTYPE::F) {
								while (lexTable.table[o].lexema != LEX_RIGHTTHESIS) {
									o++;
								}
							}
							if (lexTable.table[o].lexema == LEX_ID || lexTable.table[o].lexema == LEX_LITERAL)
							{
								if (idTable.table[lexTable.table[i - 1].idxTI].iddatatype != idTable.table[lexTable.table[o].idxTI].iddatatype)
								{

									is_ok = false;
									throw ERROR_THROW(305);
									break;
								}
							}
						}
						o++;
					}
				break;

				case LEX_FUNCTION:
					
					

				if (lexTable.table[i + 1].lexema == LEX_ID && lexTable.table[i + 2].lexema == LEX_LEFTTHESIS && lexTable.table[i - 2].lexema != LEX_DECLARE) // функция
				{
					int p = i;

					scopeFunc = idTable.table[lexTable.table[i + 1].idxTI].id.c_str();


					retFunc = idTable.table[lexTable.table[i + 1].idxTI].iddatatype;
					while (lexTable.table[p].lexema != LEX_RETURN)
					{
						p++;
					}
					ret = idTable.table[lexTable.table[p + 1].idxTI].iddatatype;
					if (retFunc != ret) {
						throw ERROR_THROW_IN(301, lexTable.table[i + 1].sn, -1);
						is_ok = false;
					}



				}
				break;
			case LEX_MAIN:
				
				b = i;
				retFunc = IT::IDDATATYPE::Number;
				while (lexTable.table[b].lexema != LEX_RETURN)
				{
					b++;
				}
				ret = idTable.table[lexTable.table[b + 1].idxTI].iddatatype;
				is_main = true;
				scopeFunc = "main";
				if (retFunc != ret) {
					throw ERROR_THROW(300);
					is_ok = false;
				}
				break;

			case LEX_LSEQUAL:
			
				scopeFunc = TI_SCOPE_DEFAULT;
				break;




			case LEX_ID:
			
				// если id(лит) = ,то не была объявленна //

				if (lexTable.table[i + 1].lexema == LEX_EQUAL && idTable.table[lexTable.table[i].idxTI].idtype == IT::IDTYPE::L)
				{
					is_ok = false;
					throw ERROR_THROW(317);
				}
				break;

				
				

			}
		}
		return is_ok;
	}
	
}
