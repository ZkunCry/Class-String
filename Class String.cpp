#include <iostream>
#include <string>
#include <cmath>
using namespace std;


class String
{
public:

	char& operator()(int i);

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
	String()
	{
		this->Str = nullptr;
		this->length = 0;
	}
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

	
	~String()
	{

		delete[]this->Str;
		this->length = 0;
	}

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

	String& Resize(int n)
	{
		if (this->Str != nullptr)
		{
			String TempStr;
			int temp = strlen(this->Str);
			TempStr.Str = new char[strlen(this->Str) + 1];
			TempStr.length = this->length;
			for (int i = 0; i <temp ; i++)
			{
				TempStr.Str[i] = this->Str[i];
			}
			delete[]this->Str;
			this->length = n;
			this->Str = new char[n + 1];
			for (int i = 0; i < TempStr.length; i++)
			{
				this->Str[i] = TempStr.Str[i];
			}
			this->Str[length] = '\0';

			return *this;
		}
	}
	String& Resize(int n,char symbol)
	{
		if (this->Str != nullptr)
		{
			String TempStr;
			int size = strlen(this->Str);
			int temp = (strlen(this->Str)+ abs(size - n) + 1);
			int j = 0,count=0;
			TempStr.Str = new char[temp];
			TempStr.length = this->length;
			for (int i = 0; i < temp-1; i++)
			{	if(i == strlen(this->Str))
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
	}
	String& Push_back(char c)
	{
		String TempStr;
		int n = strlen(this->Str)+1;
		TempStr.Str = new char[strlen(this->Str)+2];
		for (int i = 0; i < strlen(this->Str)+1; i++)
		{
			if (i == n - 1)
				TempStr.Str[i] = c;
			else
				TempStr.Str[i] = this->Str[i];
		}
		TempStr.Str[n] = '\0';
		delete[]this->Str;
		this->length = n;
		this->Str = new char[n+2];
		for (int i = 0; TempStr.Str[i]!='\0'; i++)
		{
			this->Str[i] = TempStr.Str[i];
		}
		this->Str[n] = '\0';
		return *this;
	}
	//Геттеры
	int Size()
	{
		return strlen(Str);
	}
	String GetStr()
	{
		return Str;
	}
private:
	char* Str;
	int length;
};

char& String::operator()(int i)
{
	return (Str[i]);
}
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
	String str2("WorldС");
	str2.Resize(7,'+');
	cout << str2;
	return 0;
}