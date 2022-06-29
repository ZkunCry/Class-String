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
		this->Str = nullptr;
		this->length = 0;
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
			ResStr.Str[i] = this->Str[i];
		}
		for (int j = 0; j < other.length; j++,i++)
		{
			ResStr.Str[i] = other.Str[j];
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
				TempStr.Str[i] = this->Str[i]; //Пробегаемся циклом до конца строки, которой делаем resize
			}
			TempStr.Str[temp] = '\0'; // Дописываем в конце строки ноль
			count = OrigSize;
			while (TempStr.Str[count] != '\0') //Заполнение выделенных ячеек массива пустотой(нужно для того, чтобы не выводились мусорные значения)
			{
				TempStr.Str[count] = ' ';
				count++; //Увеличиваем индекс
			}

			delete[]this->Str; /*Очищаем память для того, чтобы потом изменить размер строки при выделении памяти*/
			this->length = temp; //Присваиваем размер новый
			this->Str = new char[length+1]; //Выделение новой памяти
			for (int i = 0; i < TempStr.length; i++)
			{
				this->Str[i] = TempStr.Str[i]; //Присваиваем уже измененный массив исходному с новыми элементами
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
				TempStr.Str[i] = this->Str[i];
			}
			TempStr.Str[OrigSize] = '\0';
			delete[] this->Str;
			this->length = OrigSize;
			this->Str = new char[OrigSize + 1];
			for (int i = 0; i < OrigSize; i++)
			{
				this->Str[i] = TempStr.Str[i];
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
					TempStr.Str[i] = symbol;
			else
				TempStr.Str[i] = this->Str[i];
			}
			TempStr.Str[temp-1] = '\0';
			delete[]this->Str;
			this->length = strlen(TempStr.Str);
			this->Str = new char[length+1];
			for (int j = 0; TempStr.Str[j]!='\0'; j++)
			{
				this->Str[j] = TempStr.Str[j];
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
				TempStr.Str[i] = this->Str[i];
			}
			TempStr.Str[OrigSize] = '\0';
			delete[] this->Str;
			this->length = OrigSize;
			this->Str = new char[OrigSize + 1];
			for (int i = 0; i < OrigSize; i++)
			{
				this->Str[i] = TempStr.Str[i];
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
					TempStr.Str[i] = c;
				else
					TempStr.Str[i] = this->Str[i];
			}
			TempStr.Str[n] = '\0';
			delete[]this->Str;
			this->length = n;
			this->Str = new char[n + 2];
			for (int i = 0; TempStr.Str[i] != '\0'; i++)
			{
				this->Str[i] = TempStr.Str[i];
			}
			this->Str[n] = '\0';
			return *this;
		}
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
	String& isClear()
	{
		this->length = 0;
		this->Str[0] = '\0';
		return *this;
	}
	bool operator==(const String& other)
	{
		return strcmp(this->Str, other.Str)==0;
	}
	bool operator!=(const String& other)
	{
		return strcmp(this->Str,other.Str)<0 || strcmp(this->Str, other.Str)>0;
	}
};
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
		cout << other(i);
	}
	return (out);
}

int main()
{
	setlocale(LC_ALL,"rus");
	String str2("Good");
	String str1("good");
	str2.isClear();
	if (str2 == str1)
	{
		cout << "Строки идентичны";
	}
	else if (str2 != str1)
		cout << "Отличаются";
	return 0;
}