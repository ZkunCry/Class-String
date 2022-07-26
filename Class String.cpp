//Class String
#pragma warning(disable: 4018)
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <cmath>

using namespace std;
 
class String
{
	private:
		char*					Str; //сама строка, массив char
		mutable std::size_t		length; //длина строки

	public:
			/*Определение методов*/

			//Перегрузка операторов 
			char& operator()(int i);
			const char& operator[](int index)const;
			char& operator[](int index);
			const size_t operator!=(const String& other)const;
			const size_t operator==(const String& other)const;
			String& operator =(const String& other);
			String operator+(const String& other);
			const bool operator>(const String& other)const;
			const bool operator<(const String& other)const;
			size_t operator>=(const String& other);
			size_t operator<=(const String& other);
			friend String& operator+=(String& left, const String& right);
			friend String& operator+=(String& left, const char symbol);

			//Методы для работы со строками////
			const char* c_str() const;
			String& Resize(int n);
			String& Resize(short int n, char symbol);
			String SubStr(size_t pos, size_t count);
			String& Push_back(char c);
			String& pop_back();
			String& Erase(int position);
			String& Erase(size_t index, size_t num);
			String& Erase();
			size_t Size()const;
			const String GetStr();
			bool isEmpty();
			String& isClear();
			int Begin();
			int End();
			String& lower(size_t start, size_t end); //Метод, который делает все буквы строчными в строке
			String& upper(size_t start, size_t end);//Метод, который делает все буквы заглавными в строке
			size_t find(char symbol);
			size_t find(char symbol, size_t position);
			size_t find(const char* str);
			String& append(const String& other, size_t start);
			String& append(const char* other, size_t num);
			String& append(const String& other, size_t start, size_t end);
			String& insert(size_t num, const char* str);
			String& assign(const String& str);
			String& assign(const String& s, size_t st, size_t num);
			String& assign(const char* ps, size_t st, size_t num);
			void swap(String& str);
			char& at(size_t pos);
			int compare(size_t start, size_t num, const String& s) const;
			//Функции, которые возвращают ссылку на первый и последний объект строки
			constexpr char& front();
			constexpr char& back();

		////////////////Конструкторы////////////////////////////////////
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
		String(String&& other) noexcept // Конструктор перемещения
		{
			this->length = other.length;
			this->Str = other.Str;
			other.Str = nullptr;
		}
		//Конструктор по умолчанию
		String()
		{
			this->Str = new char[1];
			this->length = strlen(this->Str);
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

		//Деструктор//////////
		~String() noexcept
		{
			if (Str != nullptr)
			{
				delete[]this->Str;
				this->length = 0;
			}
		}

	};

	//Методы и перегрузки функций класса String///////////////////////////////

	//Перераспределение размера стркои
	String& String::Resize(int n)
	{
		if (this->Str != nullptr && n > this->length)
		{
			String TempStr;
			int OrigSize = this->length, count = 0, temp = (OrigSize + abs(OrigSize - n)); //Здесь вычисляется размер строки
			TempStr.Str = new char[temp + 1]; //Выделение памяти под временную строку, которая будет хранить результат
			TempStr.length = temp; //Присваиваем новый размер исходной строки
			count = OrigSize;
			for (int i = 0; i < OrigSize; i++)
			{
				TempStr[i] = this->Str[i]; //Пробегаемся циклом до конца строки, которой делаем resize
			}
			TempStr[temp] = '\0'; // Дописываем в конце строки ноль
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
			size_t OrigSize = n;
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
	String& String::Resize(short int n, char symbol)
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
			size_t OrigSize = abs(n);
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
	String& String::Push_back(char c)
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
	//Удаление элемента в конце строки
	String& String::pop_back()
	{
		if (this->length != 0 && this->Str != nullptr && this->length -1 !=0)
		{
			size_t size = length - 1;
			char* pc = new char[size + 1];
			for (int i = 0; i < size; i++)
				pc[i] = Str[i];
			pc[size] = '\0';
			delete[]Str;
			Str = new char[size + 1];
			for (int i = 0; i < size; i++)
				Str[i] = pc[i];
			Str[size] = '\0';
			length = size;
			return *this;
		}
		else if (this->length == 0 || this->length-1 == 0)
			return String::isClear();
	}

	//возвращает подстроку данной строки начиная с символа с индексом pos количеством 
	//count или до конца строки, если pos + count > S.size().
	String String::SubStr(size_t pos = 0, size_t count = 0)
	{
		if (pos == Size())
		{
			String TempStr;
			return TempStr;
		}
		/*Если количество копируемых символов, начиная с pos превышает длину исходной строки
		,то в таком случае нужно будет копировать с pos до конца строки
		Если же количество копируемых символов начиная с pos не превышает длину исходной строки,
		То строка копируется с pos  и до count*/
		if (count < this->length && pos != 0 && count != 0)
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
		else if (count > this->length && pos != 0 && count != 0)
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
		else if (pos == 0 && count == 0 || pos > 0 && count == 0)
		{
			String TempStr;
			return TempStr;
		}
		if (pos == 0 && count > 0)
		{
			String TempStr;
			size_t j = 0, n = (count);
			TempStr.Str = new char[n + 1];
			for (int i = pos; i < n; j++, i++)
			{
				TempStr[j] = this->Str[i];
			}
			TempStr[n] = '\0';
			return TempStr;
		}
	}
	//Удаление символов из строки начиная с position
	String& String::Erase(int position)
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
	//Перегруженный метод удаления символов из строки
	String& String::Erase(size_t index, size_t num)
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
	//Присваивание строк
	String& String::assign(const String& str)
	{
		size_t size = str.Size();
		if (this->length != 0)
			delete[] this->Str;
		this->Str = new char[size + 1];
		for (int i = 0; i < size; i++)
			this->Str[i] = str[i];
		this->Str[size] = '\0';
		return *this;

	}
	//Перегруженный метод удаления символов из строки
	String& String::Erase()
	{
		this->Str[0] = '\0';
		this->length = 0;
		return *this; // В качестве результата возвращает пустую строку и изменяет объект
	}
	//Метод определения размера строки
	size_t String::Size()const
	{
		return strlen(Str);
	}
	/*Геттер для строки, возвращает строку, которую запрашивает
	пользователь*/
	String const String::GetStr()
	{
		return Str;
	}
	/*Проверка строки, пустая она или нет
	В качестве результата возвращает истину или ложь*/
	bool String::isEmpty()
	{
		int L = strlen(this->Str);
		if (L > 0)
			return 0;
		else
			return 1;
	}
	//Проверка пустая ли строка или нет
	String& String::isClear()
	{
		this->length = 0;
		this->Str[0] = '\0';
		return *this;
	}
	/*Функции возвращающие
	начало и конец строки*/
	int String::Begin()
	{
		return 0;
	}
	int String::End()
	{
		return strlen(Str);
	}
	//Метод, который делает все буквы заглавными
	String& String::upper(size_t start, size_t end)
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
	//Метод, который делает все буквы маленькими(строчными)
	String& String::lower(size_t start, size_t end)
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
	//Метод поиска символа, который стоит в определенной позиции
	size_t String::find(char symbol)
	{
		size_t result;
		for (int i = Begin(); i < End(); i++)
		{
			if (Str[i] == symbol)
				return result = i;
			//В качестве резульатат возвращает позицию символа, который требовалось найти
		}
	}
	size_t String::find(char symbol, size_t position)
	{
		size_t result;
		for (int i = position; i < End(); i++)
		{
			if (Str[i] == symbol)
				return result = i;
		}
	}
	//Метод нахождения конкретного фрагмента в строке
	/*Если в строке содержится n одинаковых символов, то функция возвращает исходную позицию самого первого символа
	, который совпадает*/
	size_t String::find(const char* str)
	{
		size_t result = 0, j = 0, q = 0;
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
	// Объединение строк
	String& String::append(const String& other, size_t start)
	{
		String TempStr;
		String resultOther;

		resultOther.Str = new char[start + 1];

		for (int i = 0; i < start; i++)
			resultOther[i] = other[i];

		resultOther[start] = '\0';
		resultOther.length = start;

		TempStr.Str = new char[this->length + 1];

		for (int i = 0; i < length; i++)
			TempStr[i] = this->Str[i];
		TempStr[length] = '\0';
		TempStr = TempStr + resultOther;
		for (int i = 0; i < length; i++)
			TempStr[i] = this->Str[i];
		this->Str = new char[TempStr.Size() + 1];
		for (int i = 0; i < TempStr.Size(); i++)
			this->Str[i] = TempStr[i];
		this->Str[TempStr.length] = '\0';
		return *this;
	}
	//Добавление другой строки к исходной строке
	String& String::append(const char* other, size_t num)
	{
		String TempStr;
		/* Временные строки, которые нужны
						для вычислений*/
		String resultOther;

		resultOther.Str = new char[num + 1];

		for (int i = 0; i < num; i++)
			resultOther[i] = other[i];

		resultOther[num] = '\0';
		resultOther.length = num;

		TempStr.Str = new char[this->length + 1];

		for (int i = 0; i < length; i++)
			TempStr[i] = this->Str[i];
		TempStr[length] = '\0';
		TempStr = TempStr + resultOther;
		for (int i = 0; i < length; i++)
			TempStr[i] = this->Str[i];
		this->Str = new char[TempStr.Size() + 1];
		for (int i = 0; i < TempStr.Size(); i++)
			this->Str[i] = TempStr[i];
		this->Str[TempStr.length] = '\0';
		return *this;
	}
	//Метод который складывает две строки, например
	/*String s1 = "123" String s2 = "456 результатом
	s1.append(s2,0)
	будет 123456*/
	String& String::append(const String& other, size_t start, size_t end)
	{
		String TempStr;
		String resultOther;
		int j = 0;
		resultOther.Str = new char[end + 1];

		for (int i = start; j < end; j++, i++)
			resultOther[j] = other[i];

		resultOther[end] = '\0';
		resultOther.length = end;

		TempStr.Str = new char[this->length + 1];

		for (int i = 0; i < length; i++)
			TempStr[i] = this->Str[i];
		TempStr[length] = '\0';
		TempStr = TempStr + resultOther;
		for (int i = 0; i < length; i++)
			TempStr[i] = this->Str[i];
		this->Str = new char[TempStr.Size() + 1];
		for (int i = 0; i < TempStr.Size(); i++)
			this->Str[i] = TempStr[i];
		this->Str[TempStr.length] = '\0';
		return *this;
	}
	//Вставка символа, строки в любую позицию строки
	String& String::insert(size_t num, const char* str)
	{
		String Result;
		int i = 0, j = 0;
		int size = length + strlen(str);
		Result.Str = new char[length + strlen(str) + 1];
		for (; i < num; i++)
			Result[i] = Str[i];
		for (i; j < strlen(str); j++, i++)
			Result[i] = str[j];
		for (; i < size; num++, i++)
			Result[i] = Str[num];
		Result[size] = '\0';
		delete[]this->Str;
		length = size;
		this->Str = new char[size + 1];
		for (int i = 0; i < size; i++)
			this->Str[i] = Result[i];
		this->Str[size] = '\0';
		return *this;
	}
	String& String::assign(const String& s, size_t st, size_t num)
	{
		if (this->length != 0 || this->Str != nullptr)
			delete[]Str;
		size_t size = num;
		size_t j = 0;
		Str = new char[size + 1];
		for (int i = st; i < num; i++, j++)
			this->Str[j] = s[i];
		Str[size] = '\0';
		return *this;

	}
	String& String::assign(const char* ps, size_t st, size_t num)
	{
		if (this->length != 0 || this->Str != nullptr)
			delete[]Str;
		size_t size = num;
		size_t j = 0;
		Str = new char[size + 1];
		for (int i = st; i < num; i++, j++)
			this->Str[j] = ps[i];
		Str[size] = '\0';
		return *this;
	}
	//Функция меняет содержимое строк
	void String::swap(String& str)
	{
		char* ptemp = this->Str;
		this->Str = str.Str;
		this->length = str.length;
		str.Str = ptemp;
		str.length = strlen(ptemp);
	}
	//Возвращает ссылку на элемент строки
	char& String::at(size_t pos)
	{
		return this->Str[pos];
	}
	//Сравнение строк
	int String::compare(size_t start, size_t num, const String& s) const
	{
		if (num < strlen(s.Str))
			return -1;
		else if (num > strlen(s.Str))
			return 1;
		else if (strcmp(this->Str, s.Str) == 0)
			return 0;
	}
	//Получение ссылки на первый элемент строки
	constexpr char& String::front()
	{
		if (length != 0 && Str != nullptr)
			return this->Str[0];

	}
	//Получение ссылки на последний элемент строки
	constexpr char& String::back()
	{
		if (length != 0 && Str != nullptr)
			return this->Str[length - 1];

	}
	//Формирование строки в стиле Си(char)
	const char* String::c_str() const
	{
		return this->Str;
	}

	//Перегрузка оператора индексирования
	const char& String::operator[](int index) const
	{
		return Str[index];
	}
	char& String::operator[](int index)
	{
		return this->Str[index];
	}
	//Перегрузка ()
	char& String::operator()(int i)
	{
		return (Str[i]);
	}
	//Перегрузка потока cout
	ostream& operator<<(ostream& out, String other)
	{
		other.GetStr();
		for (int i = 0; i < other.Size(); i++)
		{
			cout << other[i];
		}
		return out;
	}
	String& String::operator =(const String& other)
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
	String String::operator+(const String& other)
	{
		String ResStr;
		size_t count = strlen(this->Str) + strlen(other.Str);
		ResStr.Str = new char[count + 1];
		int i = 0;
		for (; i < strlen(this->Str); i++)
		{
			ResStr[i] = this->Str[i];
		}
		for (int j = 0; j < strlen(other.Str); j++, i++)
		{
			ResStr[i] = other.Str[j];
		}
		ResStr.Str[count] = '\0';
		ResStr.length = count;
		return ResStr;
	}
	//Перегруженные операторы сравнения
	const bool String::operator>(const String& other)const 
	{
		return length > other.length;
	}
	const bool String::operator<(const String& other)const
	{
		return length < other.length;
	}
	size_t String::operator>=(const String& other)
	{
		return strcmp(this->Str, other.Str) == 0 || strcmp(this->Str, other.Str) == 1;
	}
	size_t String::operator<=(const String& other)
	{
		return strcmp(this->Str, other.Str) == 0 || strcmp(this->Str, other.Str) == -1;
	}
	const size_t String::operator==(const String& other)const
	{
		return strcmp(this->Str, other.Str) == 0;
	}

	const size_t String::operator!=(const String& other)const
	{
		return strcmp(this->Str, other.Str) < 0 || strcmp(this->Str, other.Str) > 0;
	}
	///
	//Перегрузка бинарных операторов
	String& operator+=(String& left, const String& right)
	{
		left = left + right;
		return left;

	}
	String& operator+=(String& left, const char symbol)
	{
		left.Push_back(symbol);
		return left;
	}
	///
	


int main()
{
	system("chcp 1251 > null");
	 String s1 = "x2323";
	String s2 = "34";
	bool s = s1 == s2;
	cout << s;
	return 0;
}