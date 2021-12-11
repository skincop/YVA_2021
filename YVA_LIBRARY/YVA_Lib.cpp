#include <iostream>
#include <string>
extern "C" {


	unsigned long _stdcall _strln(char* str) {
		if (str == NULL)
		{
			std::cout << std::endl;
			return 0;
		}
		unsigned long z = strlen(str);
		return strlen(str);
	}

	void _stdcall _outInt(unsigned long value)
	{
		std::cout << value << std::endl;
		return;
	}
	void _stdcall _out(char* ptr)
	{
		setlocale(0, "");
		if (ptr == NULL)
		{
			std::cout << " !!  null  !!" << std::endl;
			return;
		}
		std::cout << ptr << std::endl;
		return;
	}
	int _stdcall _converter(char* str) 
	{
		int temp = 0; // число
		int i = 0;
		int sign = 0; // знак числа 0- положительное, 1 — отрицательное
		if (str[i] == '-')
		{
			sign = 1;
			i++;
		}
		while (str[i] >= 0x30 && str[i] <= 0x39)
		{
			temp = temp + (str[i] & 0x0F);
			temp = temp * 10;
			i++;
		}
		temp = temp / 10;
		if (sign == 1)
			temp = -temp;
		return(temp);

	}

	
}