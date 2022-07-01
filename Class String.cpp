#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class String
{
private:
	char* Str; //сама строка, массив char
	int length; //длина строки

public:

	/*Определение функции*/
	char& operator()(int i);
	char& operator[](int index);
	bool operator!=(const String& other);
	bool operator==(const String& other);

	//Конструктор копирования 
	String(const String &other)
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
	String(int n,char symbol)
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
	~String()
	{
		delete[]this->Str;
		this->length = 0;
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
		int count = strlen(this->Str) + strlen(other.Str);
		ResStr.Str = new char[count+1];
		int i = 0;
		for (; i < this->length;i++)
		{
			ResStr[i] = this->Str[i];
		}
		for (int j = 0; j < other.length; j++,i++)
		{
			ResStr[i] = other.Str[j];
		}
		ResStr.Str[count]='\0';
		return ResStr;
	}
	//Перераспределение размера стркои
	String& Resize(int n)
	{
		if (this->Str != nullptr && n >this->length)
		{
			String TempStr;
			int OrigSize =this->length,count=0, temp = (OrigSize + abs(OrigSize - n)); //Здесь вычисляется размер строки
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
			this->Str = new char[length+1]; //Выделение новой памяти
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
			int OrigSize = this->length - abs(n);
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
	String& Resize(int n,char symbol)
	{
		if (this->Str != nullptr && n >length)
		{
			String TempStr;
			int size = strlen(this->Str);
			int temp = (strlen(this->Str)+ abs(size - n) + 1);
			int j = 0,count=0;
			TempStr.Str = new char[temp];
			TempStr.length = this->length;
			for (int i = 0; i < temp-1; i++)
			{	if(i >= strlen(this->Str))
					TempStr[i] = symbol;
			else
				TempStr[i] = this->Str[i];
			}
			TempStr[temp-1] = '\0';
			delete[]this->Str;
			this->length = strlen(TempStr.Str);
			this->Str = new char[length+1];
			for (int j = 0; TempStr[j]!='\0'; j++)
			{
				this->Str[j] = TempStr[j];
			}
			this->Str[length] = '\0';
			return *this;
		}
		else
		{
			String TempStr;
			int OrigSize = this->length - abs(n);
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
			int n = this->length + 1;
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
		int j = 0, n = (this->length - pos);
		TempStr.Str = new char[n+ 1];
		for (int i = pos; i < length; j++,i++)
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
			int j = 0;
			TempStr.Str = new char[count + 1]; /*В данном случае выделение памяти происходит просто:
											   Начиная с позиции pos(в том числе и она) копируются символы до count,
											    в таком случае рационально будет взять count копируемых символов и использовать в качестве
												размера строки*/
			for (int i = pos; i < count + pos; j++, i++)
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
			TempStr.Str = new char[(this->length - pos)+1];
			for (int i = pos; i < length; j++,i++)
			{
				TempStr[j] = this->Str[i];
			}
			TempStr[length-pos] = '\0';
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
				Temp[position] = this->Str[position+1];
				j = position + 1;
				i++;
			}
			else
			{
				Temp[j] = this->Str[i];
				j++;
			}

		}
		Temp[length-1] = '\0';
		delete[] this->Str;
		Str = new char[length];
		for (int i = 0; i < length-1; i++)
		{
			Str[i] = Temp[i];
		}
		length--;
		Str[length] = '\0';
		return *this;
	}
	String& Erase(size_t index,size_t num)
	{
		String Temp;
		int j = 0;
		size_t n = (length-(num-index))-1;
		Temp.Str = new char[n+1];
		for (int i = 0; i < length; i++)
		{
			if (i == index)
			{
				i+=num-1;
			}
			else
			{
				Temp[j] = this->Str[i];
				j++;
			}

		}
		Temp[n] = '\0';
		delete[] this->Str;
		Str = new char[n+1];
		for (int i = 0; i < n; i++)
		{
			Str[i] = Temp[i];
		}
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
	int Size()
	{
		return this->length=strlen(Str);
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
		if (L>0)
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
	String str ="01234567890";
	cout << str.Erase(10, 10);
	return 0;
}