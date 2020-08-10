#include "SerializedObject.h"
#include <fstream>
#include <algorithm>

using Engine::Serialization::SerializedData;
using Engine::Serialization::SerializedObject;
using std::fstream;
using std::string;
using std::vector;

SerializedObject::SerializedObject()
	:
	SerializedObject("")
{

}

SerializedObject::SerializedObject(string identifier)
	:
	identifier(identifier),
	data()
{

}

SerializedObject::~SerializedObject()
{

}

void SerializedObject::WriteSerializedData(vector<SerializedObject> data, string filename, unsigned int mode)
{

	vector<string> lines;

	for (size_t i = 0; i < data.size(); i++)
	{
		string topLine = data[i].identifier;
		lines.push_back(topLine);

		lines.push_back(string("{"));

		for (size_t j = 0; j < data[i].data.size(); j++)
		{
			lines.push_back(string(data[i].data[j].name+" : "+data[i].data[j].value));
		}

		lines.push_back(string("}"));
	}

	fstream stream;

	stream.open(filename.c_str(), mode);

	for (string line : lines)
	{
		stream << line << std::endl;
	}

	stream.close();
}

vector<SerializedObject> SerializedObject::ReadSerializedData(string filename)
{
	vector<SerializedObject> objects;
	vector<string> lines;
	int objectCount = 0;

	fstream stream;

	stream.open(filename.c_str(), fstream::in);

	{
		string line;

		while (std::getline(stream, line))
		{
			lines.push_back(line);
		}
	}
	stream.close();

	bool topLine = true;
	int dataIndex = 0;
	for (string line : lines)
	{

		if (topLine)
		{
			objects.push_back(SerializedObject(line));
			topLine = false;
		}
		else if (line[0] == '}')
		{
			topLine = true;
			dataIndex = 0;
		}
		else if (line[0] != '{')
		{
			std::string::iterator end_pos = std::remove(line.begin(), line.end(), ' ');
			line.erase(end_pos, line.end());
			int colonIndex = line.find(':');

			objects[objects.size() - 1].data.push_back(SerializedData());

			objects[objects.size() - 1].data[dataIndex].name = line.substr(0, colonIndex);
			objects[objects.size() - 1].data[dataIndex].value = line.substr(colonIndex + 1, line.length() - (colonIndex + 1));

			dataIndex++;
		}
	}

	return objects;
}