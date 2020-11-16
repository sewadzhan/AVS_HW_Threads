#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <thread>;

using namespace std;

//Получение количества строк в файле
static int GetNumOfFileLines(string path) {
	ifstream fin;
	fin.open(path);
	string line;
	int length = 0;

	while (getline(fin, line))
		++length;
	return length;
}
//Получение даных с файла
static vector<vector<string>> GetDataFromFile(string path)
{
	ifstream fin;
	fin.open(path);
	vector<vector<string>> result;
	vector<string> lines;
	int numOfLines = GetNumOfFileLines(path);

	if (!fin.is_open())
	{
		throw invalid_argument("Error of opening the file!");
	}
	else
	{

		int k = 0;
		while (!fin.eof())
		{
			string str = "";
			getline(fin, str);
			if (str == "")
			{
				continue;
			}
			if (k == numOfLines / 2)
			{
				result.push_back(lines);
				lines.clear();
				k = 0;
			}
			lines.push_back(str);
			k++;
		}
		result.push_back(lines);
	}
	return result;
}
//Шифровать текст
static string EncodeString(string text) {
	string encoded_text = "";
	for (int i = 0; i < text.length(); i++)
	{
		encoded_text += to_string((int)text[i]);
	}
	return encoded_text;
}
//Расшифровать текст
static string DecryptString(string encoded_text) {
	string decrypted_text = "";
	for (int i = 0; i < encoded_text.length() - 1; i++)
	{
		if (encoded_text[i] == '1')
		{
			char arr[] = { encoded_text[i] , encoded_text[i + 1], encoded_text[i + 2] };
			char c = stoi(arr);
			decrypted_text += c;
			i += 2;
			continue;
		}
		char arr[] = { encoded_text[i] , encoded_text[i + 1] };
		try
		{
			char c = stoi(arr);
			decrypted_text += c;
			i++;
		}
		catch (const std::exception&)
		{
			cout << arr << endl;
		}

	}
	return decrypted_text;
}
//Расшифрование текста из файла
static string GetDecryptedData(vector<string> lines) {
	string result = "";
	for (int i = 0; i < lines.size(); i++)
	{
		string decrypted_text = DecryptString(lines[i]);
		result += decrypted_text + "\n";
	}

	return result;
}
//Получение результатов дешифрования
static void GetResults(vector<vector<string>> packs) {
	string result1;
	string result2;
	if (packs.size() == 2)
	{
		thread th1([&result2, packs]() {result2 = GetDecryptedData(packs[1]); });
		result1 = GetDecryptedData(packs[0]);
		th1.join();

		cout << result1 << endl;
		cout << result2 << endl;
	}
	else
	{
		cout << packs.size() << endl;
		result1 = GetDecryptedData(packs[0]);
		cout << result1 << endl;
		/*string res = "";
		for (size_t i = 0; i < packs[0].size(); i++)
		{
			res += EncodeString(packs[0][i]);
		}

		cout << res << endl;*/
	}
}
int main()
{
	try
	{
		string path = "input.txt";
		vector<vector<string>> packs = GetDataFromFile(path);
		GetResults(packs);
	}
	catch (const invalid_argument& e)
	{
		cout << "input.txt file is not found" << endl;
		return 1;
	}
	catch (const exception& e)
	{
		cout << "Incorrect encoded text" << endl;
		return 1;
	}
}

