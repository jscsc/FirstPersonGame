#include<fstream>
#include<sstream>
#include<iostream>

#include "UtilityFunctions.h"

namespace utils
{
	bool convertFileToString(const std::string filePath, std::string& strRef)
	{
		std::ifstream inFileStream;
		inFileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);//enable these type of exceptions
		std::stringstream strStream;

		try
		{
			inFileStream.open(filePath);
			strStream << inFileStream.rdbuf();
			strRef = strStream.str();

			//clean up
			inFileStream.close();
			strStream.str(std::string()); //clear string stream
			strStream.clear(); //clear error states
		}
		catch (std::ifstream::failure e)
		{
			std::cerr << "failed to open file\n" << e.what() << std::endl;
			return false;
		}

		return true;
	}
}