#pragma warning(disable: 4018)
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class String
{
private:
	char* Str; //сама строка, массив char
	size_t length; //длина строки

public:

	/*Определение функции*/
	char& operator()(int i);
	char& operator[](int index);
	bool operator!=(const String& other);
	bool operator==(const String& other);

	//Конструктор копирования 
	String(const String& other)
	{
		this->length = strlen(other.Str);
		this->Str = new char[length + 1];
		for (int i = 0; i < length; i++)
		{
			this->Str[i] = other.Str[i];
		}
		this->Str[length] = '\0';
	}

	//Конструктор по умолчанию
	String()
	{
		this->Str = new char[1];
		this->length = 0;
		this->Str[0] = '\0';
	}
	//Конструктор для строки
	String(const char* str)
	{

		this->length = strlen(str);
		this->Str = new char[length + 1];
		for (int i = 0; i < this->length; i++)
		{
			this->Str[i] = str[i];
		}
		this->Str[length] = '\0';

	}
	String(char symbol)
	{
		this->Str = new char[2];
		this->Str[0] = symbol;
		this->Str[1] = '\0';
		this->length = 1;
	}
	String(size_t n, char symbol)
	{
		this->Str = new char[n + 1];
		for (int i = 0; i < n; i++)
		{
			this->Str[i] = symbol;
		}
		this->Str[n] = '\0';
		this->length = strlen(this->Str);
	}
	//Деструктор
	~String() noexcept
	{
		if (Str != nullptr)
		{
			delete[]this->Str;
			this->length = 0;
		}
	}
	//Перегруженный оператор присваивания
	String& operator =(const String& other)
	{
		if (this->Str != nullptr)
		{
			delete[] this->Str;
		}
		this->length = strlen(other.Str);
		this->Str = new char[length + 1];
		for (int i = 0; i < length; i++)
		{
			this->Str[i] = other.Str[i];
		}
		this->Str[length] = '\0';
		return *this;
	}
	//Перегруженный оператор суммирования(конкатенация)
	String operator+(const String& other)
	{
		String ResStr;
		size_t count = strlen(this->Str) + strlen(other.Str);
		ResStr.Str = new char[count + 1];
		int i = 0;
		for (i = 0; i < this->length; i++)
		{
			ResStr[i] = this->Str[i];
		}
		for (int j = 0; j < strlen(other.Str); j++, i++)
		{
			ResStr[i] = other.Str[j];
		}
		ResStr.Str[count] = '\0';
		return ResStr;
	}
	//Перераспределение размера стркои
	String& Resize(int n)
	{
		if (this->Str != nullptr && n > this->length)
		{
			String TempStr;
			int OrigSize = this->length, count = 0, temp = (OrigSize + abs(OrigSize - n)); //Здесь вычисляется размер строки
			TempStr.Str = new char[temp + 1]; //Выделение памяти под временную строку, которая будет хранить результат
			TempStr.length = temp; //Присваиваем новый размер исходной строки
			for (int i = 0; i < OrigSize; i++)
			{
				TempStr[i] = this->Str[i]; //Пробегаемся циклом до конца строки, которой делаем resize
			}
			TempStr[temp] = '\0'; // Дописываем в конце строки ноль
			count = OrigSize;
			while (TempStr[count] != '\0') //Заполнение выделенных ячеек массива пустотой(нужно для того, чтобы не выводились мусорные значения)
			{
				TempStr[count] = ' ';
				count++; //Увеличиваем индекс
			}

			delete[]this->Str; /*Очищаем память для того, чтобы потом изменить размер строки при выделении памяти*/
			this->length = temp; //Присваиваем размер новый
			this->Str = new char[length + 1]; //Выделение новой памяти
			for (int i = 0; i < TempStr.length; i++)
			{
				this->Str[i] = TempStr[i]; //Присваиваем уже измененный массив исходному с новыми элементами
			}
			this->Str[temp] = '\0'; // и присваиваем последнему элементу 0
			return *this; // Возвращаем в качестве результата объект, который нужно было изменить
		}
		else
		{
			String TempStr;
			size_t OrigSize = this->length - abs(n);
			TempStr.Str = new char[OrigSize + 1];
			TempStr.length = OrigSize;
			for (int i = 0; i < OrigSize; i++)
			{
				TempStr[i] = this->Str[i];
			}
			TempStr[OrigSize] = '\0';
			delete[] this->Str;
			this->length = OrigSize;
			this->Str = new char[OrigSize + 1];
			for (int i = 0; i < OrigSize; i++)
			{
				this->Str[i] = TempStr[i];
			}
			this->Str[OrigSize] = '\0';
			return *this;

		}
	}
	//Перегруженный метод перераспределения размера строки
	String& Resize(short int n, char symbol)
	{
		if (this->Str != nullptr && n > length)
		{
			String TempStr;
			int size = strlen(this->Str);
			size_t temp = (strlen(this->Str) + abs(size - n) + 1);
			int j = 0, count = 0;
			TempStr.Str = new char[temp];
			TempStr.length = this->length;
			for (int i = 0; i < temp - 1; i++)
			{
				if (i >= strlen(this->Str))
					TempStr[i] = symbol;
				else
					TempStr[i] = this->Str[i];
			}
			TempStr[temp - 1] = '\0';
			delete[]this->Str;
			this->length = strlen(TempStr.Str);
			this->Str = new char[length + 1];
			for (int j = 0; TempStr[j] != '\0'; j++)
			{
				this->Str[j] = TempStr[j];
			}
			this->Str[length] = '\0';
			return *this;
		}
		else
		{
			String TempStr;
			size_t OrigSize = this->length - abs(n);
			TempStr.Str = new char[OrigSize + 1];
			TempStr.length = OrigSize;
			for (int i = 0; i < OrigSize; i++)
			{
				TempStr[i] = this->Str[i];
			}
			TempStr[OrigSize] = '\0';
			delete[] this->Str;
			this->length = OrigSize;
			this->Str = new char[OrigSize + 1];
			for (int i = 0; i < OrigSize; i++)
			{
				this->Str[i] = TempStr[i];
			}
			this->Str[OrigSize] = '\0';
			return *this;

		}
	}
	//Метод вставки символа в конец строки
	String& Push_back(char c)
	{
		if (this->Str != nullptr)
		{
			String TempStr;
			size_t n = this->length + 1;
			TempStr.Str = new char[this->length + 2];
			for (int i = 0; i < this->length + 1; i++)
			{
				if (i == n - 1)
					TempStr[i] = c;
				else
					TempStr[i] = this->Str[i];
			}
			TempStr.Str[n] = '\0';
			delete[]this->Str;
			this->length = n;
			this->Str = new char[n + 2];
			for (int i = 0; TempStr[i] != '\0'; i++)
			{
				this->Str[i] = TempStr[i];
			}
			this->Str[n] = '\0';
			return *this;
		}
	}
	//Возвращает подстроку дан	ой строки начиная с символа с индексом pos и до конца строки.
	String SubStr(size_t pos)
	{
		String TempStr;
		size_t j = 0, n = (this->length - pos);
		TempStr.Str = new char[n + 1];
		for (int i = pos; i < length; j++, i++)
		{
			TempStr[j] = this->Str[i];
		}
		TempStr[n] = '\0';
		return TempStr;
	}
	//возвращает подстроку данной строки начиная с символа с индексом pos количеством 
	//count или до конца строки, если pos + count > S.size().
	String SubStr(size_t pos, size_t count)
	{
		/*Если количество копируемых символов, начиная с pos превышает длину исходной строки
		,то в таком случае нужно будет копировать с pos до конца строки
		Если же количество копируемых символов начиная с pos не превышает длину исходной строки,
		То строка копируется с pos  и до count*/
		if (count < this->length)
		{
			String TempStr;
			size_t j = 0;
			TempStr.Str = new char[count + 1]; /*В данном случае выделение памяти происходит просто:
											   Начиная с позиции pos(в том числе и она) копируются символы до count,
												в таком случае рационально будет взять count копируемых символов и использовать в качестве
												размера строки*/
			for (size_t i = pos; i < count + pos; j++, i++)
			{
				TempStr[j] = this->Str[i];
			}
			TempStr[count] = '\0';
			return TempStr;
		}
		else if (count > this->length)
		{
			String TempStr;
			int j = 0;
			TempStr.Str = new char[(this->length - pos) + 1];
			for (int i = pos; i < length; j++, i++)
			{
				TempStr[j] = this->Str[i];
			}
			TempStr[length - pos] = '\0';
			return TempStr;
		}
	}
	String& Erase(int position)
	{
		String Temp;
		int j = 0;
		Temp.Str = new char[length];
		for (int i = 0; i < length; i++)
		{
			if (i == position)
			{
				Temp[position] = this->Str[position + 1];
				j = position + 1;
				i++;
			}
			else
			{
				Temp[j] = this->Str[i];
				j++;
			}

		}
		Temp[length - 1] = '\0';
		delete[] this->Str;
		Str = new char[length];
		for (int i = 0; i < length - 1; i++)
		{
			Str[i] = Temp[i];
		}
		length--;
		Str[length] = '\0';
		return *this;
	}
	String& Erase(size_t index, size_t num)
	{
		String Temp;
		size_t j = 0;
		size_t n = (length - (num - index)) - 1;
		Temp.Str = new char[n + 1];
		for (size_t i = 0; i < length; i++)
		{
			if (i == index)
				i += num - 1;
			else
			{
				Temp[j] = this->Str[i];
				j++;
			}

		}
		Temp[n] = '\0';
		delete[] this->Str;
		Str = new char[n + 1];
		for (int i = 0; i < n; i++)
			Str[i] = Temp[i];
		Str[n] = '\0';
		length = n;
		return *this;
	}
	String& Erase()
	{
		this->Str[0] = '\0';
		this->length = 0;
		return *this;
	}
	//Метод определения размера строки
	size_t Size()
	{
		return this->length = strlen(Str);
	}
	/*Геттер для строки, возвращает строку, которую запрашивает
	пользователь*/
	String GetStr()
	{
		return Str;
	}
	/*Проверка строки, пустая она или нет
	В качестве результата возвращает истину или ложь*/
	bool isEmpty()
	{
		int L = strlen(this->Str);
		if (L > 0)
			return 0;
		else
			return 1;
	}
	//Проверка пустая ли строка или нет
	String& isClear()
	{
		this->length = 0;
		this->Str[0] = '\0';
		return *this;
	}
	int Begin()
	{
		return 0;
	}
	int End()
	{
		return strlen(Str);
	}
	String& upper(size_t start, size_t end)
	{
		if (start <= Begin() && end <= End())
		{
			for (int i = start; i < end; i++)
			{
				if (Str[i] >= 65 && Str[i] <= 90)
					continue;
				else
					Str[i] -= 32;
			}
			return *this;
		}
	}
	String& lower(size_t start, size_t end)
	{
		if (start <= Begin() && end <= End())
		{
			for (int i = start; i < end; i++)
			{
				if (Str[i] >= 97 && Str[i] <= 122)
					continue;
				else
					Str[i] += 32;
			}
			return *this;
		}
	}
	size_t find(char symbol)
	{
		size_t result;
		for (int i =Begin(); i< End(); i++)
		{
			if (Str[i] == symbol)
				return result = i;
		}
	}
	size_t find(char symbol,size_t position)
	{
		size_t result;
		for (int i = position; i < End(); i++)
		{
			if (Str[i] == symbol)
				return result = i;
		}
	}
	size_t find(const char *str)
	{
		size_t result=0,j=0,q=0;
		for (int i = Begin(); i < End(); i++)
		{
			if (Str[i] == str[q])
			{
				q++;
				result++;
				j = i;
			}
		}
		if (result == strlen(str))
			return j - result + 1;
		else
			return 0;
	}
	String& append(String& other)
	{
		String TempStr;
		TempStr.Str = new char[this->length + 1];
		for (int i = 0; i < length; i++)
			TempStr[i] = this->Str[i];
		TempStr[length] = '\0';
		TempStr = other+TempStr;
		for (int i = 0; i < length; i++)
			TempStr[i] = this->Str[i];
		this->Str = new char[TempStr.Size() + 1];
		for (int i = 0; i < TempStr.Size(); i++)
			this->Str[i] = TempStr[i];
		this->Str[TempStr.length] = '\0';
		return *this;
	}
};
//Перегрузка операторов 
bool String::operator==(const String& other)
{
	return strcmp(this->Str, other.Str) == 0;
}
bool String::operator!=(const String& other)
{
	return strcmp(this->Str, other.Str) < 0 || strcmp(this->Str, other.Str) > 0;
}
char& String::operator[](int index)
{
	return Str[index];
}
//Перегрузка ()
char& String::operator()(int i)
{
	return (Str[i]);
}
//Перегрузка cout
ostream& operator<<(ostream& out, String other)
{
	other.GetStr();
	for (int i = 0; i < other.Size(); i++)
	{
		cout << other[i];
	}
	return out;
}

int main()
{
	setlocale(LC_ALL,"rus");
	String str;
	String str3 = " 10 ";
	String str2 = "print 10 and then 5 more";
	str = str3;
	cout << str << endl;
	str = str2;
	cout << str;
	return 0;
}